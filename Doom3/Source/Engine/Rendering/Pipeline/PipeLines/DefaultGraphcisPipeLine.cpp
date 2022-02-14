#include "DefaultGraphcisPipeLine.h"

#include <Graphics/graphicsSetting.h>
#include <Rendering/Renderer/RendererStaticIterator.h>
#include <Rendering/Acceleration/FrontToBackSorting/SortFrontToBackSolver.h>
#include <Rendering/Camera.h>
#include <ResourceManagement/JobSystem_cpp/JobSystem.h>
#include <Rendering/Renderer/Renderer.h>
#include <EngineGUI/engineGUIServer.h>
#include <Graphics/Graphics_Server.h>
#include <Rendering/Renderer/RendererStaticIterator.h>

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


std::future<void> dooms::graphics::DefaultGraphcisPipeLine::PushFrontToBackSortJobToJobSystem
(
	dooms::Camera* const targetCamera, const UINT32 cameraIndex
)
{
	std::future<void> future{};

	if (graphicsSetting::IsSortObjectFrontToBack == true)
	{
		math::Vector3 cameraPos = targetCamera->GetTransform()->GetPosition();
		std::function<void()> FrontToBackSortJob = [cameraPos, cameraIndex]()
		{
			std::vector<Renderer*>& renderers = dooms::RendererComponentStaticIterator::GetSingleton()->GetSortingRendererInLayer();

			const size_t startRendererIndex = 0;
			const size_t rendererCount = renderers.size();

			for
				(
					size_t rendererIndex = startRendererIndex;
					rendererIndex < rendererCount;
					rendererIndex++
					)
			{
				D_ASSERT(IsValid(renderers[rendererIndex]));
				renderers[rendererIndex]->CacheDistanceToCamera(cameraIndex, cameraPos);
			}

			dooms::graphics::SortFrontToBackSolver::SortRenderer(cameraIndex);
		};

		future = resource::JobSystem::GetSingleton()->PushBackJobToPriorityQueue(FrontToBackSortJob);
	}

	return future;
}


void dooms::graphics::DefaultGraphcisPipeLine::DrawRenderers(dooms::Camera* const targetCamera, const size_t cameraIndex)
{
	D_ASSERT(IsValid(targetCamera) == true);

	targetCamera->UpdateUniformBufferObject();

	D_START_PROFILING(DrawLoop, dooms::profiler::eProfileLayers::Rendering);
	const bool targetCamera_IS_CULLED_flag_on = targetCamera->GetCameraFlag(dooms::eCameraFlag::IS_CULLED);

	const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetSingleton()->GetSortedRendererInLayer();
	for (Renderer* renderer : renderersInLayer)
	{
		if
			(
				IsValid(renderer) == true &&
				//renderer->GetOwnerEntityLayerIndex() == layerIndex && 
				renderer->GetIsComponentEnabled() == true
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