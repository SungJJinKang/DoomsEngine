#include "DefaultGraphcisPipeLine.h"

#include <Graphics/graphicsSetting.h>
#include <Rendering/Renderer/RendererStaticIterator.h>
#include <Rendering/Acceleration/FrontToBackSorting/SortFrontToBackSolver.h>
#include <Rendering/Camera.h>
#include <ResourceManagement/Thread/JobPool.h>
#include <Rendering/Renderer/Renderer.h>
#include <EngineGUI/engineGUIServer.h>
#include <Rendering/Graphics_Server.h>
#include <Rendering/Renderer/RendererStaticIterator.h>
#include <Rendering/Batch/BatchRenderingManager.h>

#include "Asset/AssetManager/AssetManager.h"
#include "Graphics/GraphicsAPI/graphicsAPISetting.h"

void dooms::graphics::DefaultGraphcisPipeLine::PreRenderRenderer()
{
	const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetSingleton()->GetSortedRendererInLayer();
	for (Renderer* renderer : renderersInLayer)
	{
		renderer->PreRender();
	}
}


dooms::graphics::DefaultGraphcisPipeLine::DefaultGraphcisPipeLine(dooms::graphics::Graphics_Server& graphicsServer)
	:
	GraphicsPipeLine(graphicsServer),
	mRenderingCullingManager(),
	mRenderingDebugger()
{
}

void dooms::graphics::DefaultGraphcisPipeLine::Initialize()
{
	GraphicsPipeLine::Initialize();

	mRenderingCullingManager.Initialize();
	mRenderingDebugger.Initialize();

	auto DepthOnlyShader = assetImporter::AssetManager::GetSingleton()->GetAsset<asset::eAssetType::SHADER>("DepthOnlyShader.glsl");
	DepthOnlyMaterial = dooms::CreateDObject<graphics::Material>(DepthOnlyShader);
}

void dooms::graphics::DefaultGraphcisPipeLine::LateInitialize()
{
	GraphicsPipeLine::LateInitialize();

	mRenderingDebugger.LateInitialize();
}

void dooms::graphics::DefaultGraphcisPipeLine::PreRender()
{
	D_START_PROFILING(PreRenderRenderer, dooms::profiler::eProfileLayers::Rendering);
	PreRenderRenderer();
	D_END_PROFILING(PreRenderRenderer);

	D_START_PROFILING(engineGUIServer_PreRender, dooms::profiler::eProfileLayers::Rendering);
	dooms::ui::EngineGUIServer::GetSingleton()->PreRender();
	D_END_PROFILING(engineGUIServer_PreRender);

	mRenderingDebugger.PreRender();


	if (Camera::GetMainCamera()->GetIsCullJobEnabled() == true)
	{
		D_START_PROFILING(PreCullJob, dooms::profiler::eProfileLayers::Rendering);
		mRenderingCullingManager.PreCullJob();
		D_END_PROFILING(PreCullJob);
	}
}

void dooms::graphics::DefaultGraphcisPipeLine::Render()
{
	D_START_PROFILING(Update_Uniform_Buffer, dooms::profiler::eProfileLayers::Rendering);
	mGraphicsServer.mUniformBufferObjectManager.UpdateUniformObjects();
	D_END_PROFILING(Update_Uniform_Buffer);

	const std::vector<dooms::Camera*>& spawnedCameraList = StaticContainer<dooms::Camera>::GetAllStaticComponents();

	for (size_t cameraIndex = 0; cameraIndex < spawnedCameraList.size(); cameraIndex++)
	{
		dooms::Camera* const targetCamera = spawnedCameraList[cameraIndex];
		CameraRender(targetCamera, cameraIndex);
	}

	RendererComponentStaticIterator::GetSingleton()->ChangeWorkingIndexRenderers();
}

void dooms::graphics::DefaultGraphcisPipeLine::PostRender()
{
	D_START_PROFILING(engineGUIServer_Render, dooms::profiler::eProfileLayers::Rendering);
	dooms::ui::EngineGUIServer::GetSingleton()->Render();
	D_END_PROFILING(engineGUIServer_Render);

	D_START_PROFILING(engineGUIServer_PostRender, dooms::profiler::eProfileLayers::Rendering);
	dooms::ui::EngineGUIServer::GetSingleton()->PostRender();
	D_END_PROFILING(engineGUIServer_PostRender);

	mRenderingDebugger.PostRender();

	D_START_PROFILING(SwapBuffer, dooms::profiler::eProfileLayers::Rendering);
	graphics::GraphicsAPI::SwapBuffer();
	D_END_PROFILING(SwapBuffer);

}


void dooms::graphics::DefaultGraphcisPipeLine::PushFrontToBackSortJobToJobSystem
(
	dooms::Camera* const targetCamera, const UINT32 cameraIndex, std::atomic<bool>* bIsFinihsed
)
{
	math::Vector3 cameraPos = targetCamera->GetTransform()->GetPosition();
	auto FrontToBackSortJob = [cameraPos, cameraIndex, bIsFinihsed]()
	{
		FrontToBackSort(cameraPos, cameraIndex);

		if (bIsFinihsed != nullptr)
		{
			*bIsFinihsed = true;
		}
	};

	std::move(thread::ParallelForWithReturn(FrontToBackSortJob, 1)[0]);
}

void dooms::graphics::DefaultGraphcisPipeLine::FrontToBackSort(const math::Vector3& CameraPos, const UINT32 cameraIndex)
{
	std::vector<Renderer*>& renderers = dooms::RendererComponentStaticIterator::GetSingleton()->GetSortingRendererInLayer();

	const size_t startRendererIndex = 0;
	const size_t rendererCount = renderers.size();

	for(
		size_t rendererIndex = startRendererIndex;
		rendererIndex < rendererCount;
		rendererIndex++
	)
	{
		D_ASSERT(IsValid(renderers[rendererIndex]));
		renderers[rendererIndex]->CacheDistanceToCamera(cameraIndex, CameraPos);
	}

	dooms::graphics::SortFrontToBackSolver::SortRenderer(cameraIndex);
}

void dooms::graphics::DefaultGraphcisPipeLine::DrawRenderersWithDepthOnly
(
	dooms::Camera* const targetCamera,
	const size_t cameraIndex
) const
{
	if
	(
		dooms::graphics::graphicsAPISetting::DepthPrePassType == dooms::graphics::eDepthPrePassType::AllOpaque //||
		//dooms::graphics::graphicsAPISetting::DepthPrePassType == dooms::graphics::eDepthPrePassType::ConsiderBound 
	)
	{
		D_START_PROFILING(RenderObject_DepthPrePass, dooms::profiler::eProfileLayers::Rendering);

		dooms::graphics::FixedMaterial::GetSingleton()->SetFixedMaterial(GetDepthOnlyMaterial());
		GraphicsAPI::SetIsDepthTestEnabled(true);
		GraphicsAPI::SetDepthMask(true);
		GraphicsAPI::SetDepthFunc(GraphicsAPI::eTestFuncType::LESS);

		if(dooms::graphics::graphicsAPISetting::DepthPrePassType == dooms::graphics::eDepthPrePassType::AllOpaque)
		{
			DrawRenderers(targetCamera, cameraIndex);
		}
		/*
		else if(dooms::graphics::graphicsAPISetting::DepthPrePassType == dooms::graphics::eDepthPrePassType::ConsiderBound)
		{
			ConditionalDrawRenderers
			(
				targetCamera,
				cameraIndex,
				[](const dooms::Renderer* const Renderer) -> bool
				{
					bool bIsDrawable = false;

					D_ASSERT(Renderer->CheckIsWorldColliderCacheDirty() == false);
					if(const dooms::physics::AABB3D* const AABB = Renderer->GetWorldColliderWithoutUpdate())
					{
						AABB->
					}
				}
			);
		}
		*/

		dooms::graphics::FixedMaterial::GetSingleton()->SetFixedMaterial(nullptr);

		D_END_PROFILING(RenderObject_DepthPrePass);
	}
}


void dooms::graphics::DefaultGraphcisPipeLine::DrawRenderers(dooms::Camera* const targetCamera, const size_t cameraIndex) const
{
	ConditionalDrawRenderers(targetCamera, cameraIndex, nullptr);	
}

void dooms::graphics::DefaultGraphcisPipeLine::ConditionalDrawRenderers
(
	dooms::Camera* const targetCamera,
	const size_t cameraIndex,
	const std::function<bool(const dooms::Renderer* const)> ConditionFunc
) const
{
	D_ASSERT(IsValid(targetCamera) == true);

	{
		D_START_PROFILING(DrawLoop, dooms::profiler::eProfileLayers::Rendering);
		const bool targetCamera_IS_CULLED_flag_on = targetCamera->GetCameraFlag(dooms::eCameraFlag::IS_CULLED);

		const bool IsExistCondtionFunc = static_cast<bool>(ConditionFunc);

		const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetSingleton()->GetSortedRendererInLayer();
		for (Renderer* renderer : renderersInLayer)
		{
			if
			(
				IsValid(renderer) == true &&
				renderer->GetIsComponentEnabled() == true &&
				renderer->GetIsBatched() == false &&
				(IsExistCondtionFunc ? ConditionFunc(renderer) : true)
			)
			{
				if
				(
					targetCamera_IS_CULLED_flag_on == false ||
					renderer->GetIsCulled(targetCamera->CameraIndexInCullingSystem) == false
				)
				{
					renderer->Draw();
				}
			}
		}
		D_END_PROFILING(DrawLoop);
	}
}

void dooms::graphics::DefaultGraphcisPipeLine::DrawBatchedRenderers() const
{
	D_START_PROFILING(DrawBatchedRenderers, dooms::profiler::eProfileLayers::Rendering);
	D_ASSERT(IsValid(BatchRenderingManager::GetSingleton()));
	BatchRenderingManager::GetSingleton()->DrawAllBatchedRendererContainers();
	D_END_PROFILING(DrawBatchedRenderers);
}

dooms::graphics::Material* dooms::graphics::DefaultGraphcisPipeLine::GetDepthOnlyMaterial() const
{
	D_ASSERT(IsValid(DepthOnlyMaterial));
	return DepthOnlyMaterial;
}
