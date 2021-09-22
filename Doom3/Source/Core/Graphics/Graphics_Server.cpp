#include "Graphics_Server.h"

#include <iostream>
#include <string>
#include <functional>

#include <Utility.h>

#include "../Game/GameCore.h"
#include "../Game/ConfigData.h"
#include "../Scene/Layer.h"
#include "../Game/AssetManager/AssetManager.h"

#include "GraphicsAPI.h"

#include "Buffer/UniformBufferObjectManager.h"
#include "Buffer/UniformBufferObjectUpdater.h"

#include <Rendering/Renderer/Renderer.h>
#include "Material/Material.h"
#include "Texture/Texture.h"
#include "FrameBuffer/DefferedRenderingFrameBuffer.h"
#include <Rendering/Renderer/RendererStaticIterator.h>

#include "Rendering/Camera.h"

#include "Physics/Collider/AABB.h"

#include "Acceleration/LinearData_ViewFrustumCulling/EveryCulling.h"

#ifdef DEBUG_MODE
#include "Physics/Collider/Plane.h"
#include <SequenceStringGenerator/SequenceStringGenerator.h>
#endif
#include "Buffer/Mesh.h"

#include "GraphicsAPIManager.h"
#include "Graphics_Setting.h"

using namespace doom::graphics;


void Graphics_Server::Init()
{
	Graphics_Setting::LoadData();
	GraphicsAPIManager::Initialize();

	mCullingSystem = std::make_unique<culling::EveryCulling>(Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight());

	return;
}

void doom::graphics::Graphics_Server::LateInit()
{
#ifdef DEBUG_MODE
	mDebugGraphics.Init();
#endif 

	SetRenderingMode(Graphics_Server::eRenderingMode::DeferredRendering);


	//mQueryOcclusionCulling.InitQueryOcclusionCulling();
	//mCullDistance.Initialize();
}

void Graphics_Server::Update()
{		
#ifdef DEBUG_MODE
	mDebugGraphics.Update();
	mRenderingDebugger.DrawRenderingBoundingBox();
#endif

	Renderder_UpdateComponent();

#ifdef DEBUG_MODE
	mRenderingDebugger.UpdateInputForPrintDrawCallCounter();
#endif

	DeferredRendering();
	
}

void Graphics_Server::OnEndOfFrame()
{
	Renderder_OnEndOfFrameComponent();

#ifdef DEBUG_MODE
	mDebugGraphics.Reset();
#endif

	GraphicsAPIManager::SwapBuffer();
}

void doom::graphics::Graphics_Server::Renderder_InitComponent()
{
	for (unsigned int layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
	{
		const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetRendererInLayer(layerIndex);
		for (size_t rendererIndex = 0; rendererIndex < renderersInLayer.size(); rendererIndex++)
		{
			//renderersInLayer[rendererIndex]->InitComponent_Internal();
			renderersInLayer[rendererIndex]->InitComponent();
		}
	}
}

void doom::graphics::Graphics_Server::Renderder_UpdateComponent()
{
	for (unsigned int layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
	{
		const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetRendererInLayer(layerIndex);
		for (size_t rendererIndex = 0; rendererIndex < renderersInLayer.size(); rendererIndex++)
		{
			renderersInLayer[rendererIndex]->UpdateComponent_Internal();
			renderersInLayer[rendererIndex]->UpdateComponent();
		}
	}
}

void doom::graphics::Graphics_Server::Renderder_OnEndOfFrameComponent()
{
	for (unsigned int layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
	{
		const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetRendererInLayer(layerIndex);
		for (size_t rendererIndex = 0; rendererIndex < renderersInLayer.size(); rendererIndex++)
		{
			renderersInLayer[rendererIndex]->OnEndOfFrame_Component_Internal();
			renderersInLayer[rendererIndex]->OnEndOfFrame_Component();
		}
	}
}



Graphics_Server::Graphics_Server()
{

}

Graphics_Server::~Graphics_Server()
{

}



void Graphics_Server::PreUpdateEntityBlocks()
{
	const std::vector<culling::EntityBlock*>& activeEntityBlockList = mCullingSystem->GetActiveEntityBlockList();
	for (culling::EntityBlock* entityBlock : activeEntityBlockList)
	{
		const unsigned int entityCount = entityBlock->mCurrentEntityCount;
		for (unsigned int entityIndex = 0; entityIndex < entityCount; entityIndex++)
		{
			::doom::Renderer* const renderer = reinterpret_cast<::doom::Renderer*>(entityBlock->mRenderer[entityIndex]);

			if (renderer != nullptr)
			{
				//this is really expensive!!
				const float worldRadius = renderer->BVH_Sphere_Node_Object::GetWorldCollider()->mRadius;

				const math::Vector3 renderedObjectPos = renderer->GetTransform()->GetPosition();

				entityBlock->mPositions[entityIndex].SetPosition(*reinterpret_cast<const culling::Vector3*>(&renderedObjectPos));
				entityBlock->mPositions[entityIndex].SetBoundingSphereRadius(worldRadius);

#ifdef ENABLE_SCREEN_SAPCE_AABB_CULLING

				std::memcpy(
					entityBlock->mWorldAABB + entityIndex,
					const_cast<Renderer*>(renderer)->ColliderUpdater<doom::physics::AABB3D>::GetWorldCollider()Cache()->data(),
					sizeof(culling::AABB)
				);

#endif
			}
		}
	}
}

void Graphics_Server::DoCullJob()
{
	const std::vector<doom::Camera*>& spawnedCameraList = StaticContainer<doom::Camera>::GetAllStaticComponents();

	unsigned int CullJobAvailiableCameraCount = 0;
	for (doom::Camera* camera : spawnedCameraList)
	{
		if (
			camera->GetCameraFlag(doom::eCameraFlag::IS_CULLED) == true &&
			camera->GetCameraFlag(doom::eCameraFlag::PAUSE_CULL_JOB) == false
		)
		{
			camera->CameraIndexInCullingSystem = CullJobAvailiableCameraCount;

			D_START_PROFILING(SequenceStringGenerator::GetLiteralString("UpdateFrustumPlane Camera Num: ", CullJobAvailiableCameraCount), doom::profiler::eProfileLayers::Rendering);

			mCullingSystem->SetViewProjectionMatrix(CullJobAvailiableCameraCount, *reinterpret_cast<const culling::Matrix4X4*>(&(camera->GetViewProjectionMatrix())));

			D_END_PROFILING(SequenceStringGenerator::GetLiteralString("UpdateFrustumPlane Camera Num: ", CullJobAvailiableCameraCount));

			CullJobAvailiableCameraCount++;
		}
	
	}

	if (CullJobAvailiableCameraCount > 0)
	{
		mCullingSystem->SetCameraCount(CullJobAvailiableCameraCount);

		D_START_PROFILING("mFrotbiteCullingSystem.ResetCullJobStat", doom::profiler::eProfileLayers::Rendering);
		mCullingSystem->ResetCullJobState();
		D_END_PROFILING("mFrotbiteCullingSystem.ResetCullJobStat");

		D_START_PROFILING("PreUpdateEntityBlocks", doom::profiler::eProfileLayers::Rendering);
		PreUpdateEntityBlocks();
		D_END_PROFILING("PreUpdateEntityBlocks");

		D_START_PROFILING("Push Culling Job To Linera Culling System", doom::profiler::eProfileLayers::Rendering);
		resource::JobSystem::GetSingleton()->PushBackJobToAllThreadWithNoSTDFuture(mCullingSystem->GetCullJob());
		D_END_PROFILING("Push Culling Job To Linera Culling System");
	}
	
}

void doom::graphics::Graphics_Server::DeferredRendering()
{
	DoCullJob(); // do this first
	//TODO : Think where put this, as early as good


	const std::vector<doom::Camera*>& spawnedCameraList = StaticContainer<doom::Camera>::GetAllStaticComponents();

	D_START_PROFILING("Update Uniform Buffer", doom::profiler::eProfileLayers::Rendering);
	mUniformBufferObjectManager.UpdateUniformObjects();
	D_END_PROFILING("Update Uniform Buffer");

	FrameBuffer::UnBindFrameBuffer();
	//Clear ScreenBuffer
	GraphicsAPI::ClearColor(Graphics_Setting::ClearColor);
	GraphicsAPI::Clear(GraphicsAPI::eClearMask::COLOR_BUFFER_BIT, GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);

	if (doom::time::MainTimer::GetFrameStep(2))
	{
		RendererComponentStaticIterator::CacheDistanceFromRenderersToCamera(spawnedCameraList);
	}

	for (size_t cameraIndex = 0 ; cameraIndex < spawnedCameraList.size() ; cameraIndex++)
	{
		doom::Camera* const targetCamera = spawnedCameraList[cameraIndex];
		targetCamera->UpdateUniformBufferObject();

		targetCamera->mDefferedRenderingFrameBuffer.ClearFrameBuffer();
		targetCamera->mDefferedRenderingFrameBuffer.BindFrameBuffer();
		
		D_START_PROFILING("RenderObject", doom::profiler::eProfileLayers::Rendering);
		//GraphicsAPI::Enable(GraphicsAPI::eCapability::DEPTH_TEST);
		RenderObject(targetCamera, cameraIndex);
		D_END_PROFILING("RenderObject");

		targetCamera->mDefferedRenderingFrameBuffer.UnBindFrameBuffer();
	
		// 
		//Blit DepthBuffer To ScreenBuffer

		if (targetCamera->IsMainCamera() == true)
		{
			//Only Main Camera can draw to screen buffer

#ifdef DEBUG_MODE
			mRenderingDebugger.mOverDrawVisualization.ShowOverDrawVisualizationPIP(Graphics_Setting::bmIsOverDrawVisualizationEnabled);
			if (Graphics_Setting::bmIsOverDrawVisualizationEnabled == true)
			{
				mRenderingDebugger.mOverDrawVisualization.SetOverDrawVisualizationRenderingState(true);
				RenderObject(targetCamera, cameraIndex);
				mRenderingDebugger.mOverDrawVisualization.SetOverDrawVisualizationRenderingState(false);
			}
#endif
		
			
			targetCamera->mDefferedRenderingFrameBuffer.BlitDepthBufferToScreenBuffer();

			targetCamera->mDefferedRenderingFrameBuffer.BindGBufferTextures();
			
			mDeferredRenderingDrawer.DrawDeferredRenderingQuadDrawer();

#ifdef DEBUG_MODE
			//이거 느려도 상관없다. 그냥 여기다 두자.
			mDebugGraphics.BufferVertexDataToGPU();
			mDebugGraphics.Draw();
#endif
		}
		
	}

#ifdef DEBUG_MODE
	mDebugGraphics.SetIsVertexDataSendToGPUAtCurrentFrame(false);
#endif


	if (mPIPManager.GetPIPCount() != 0)
	{
		//Why do this ? : because deffered rendering's quad have 0 depth value
		GraphicsAPI::Disable(GraphicsAPI::eCapability::DEPTH_TEST);

		D_START_PROFILING("DrawPIPs", doom::profiler::eProfileLayers::Rendering);
		mPIPManager.DrawPIPs(); // drawing pip before gbuffer will increase performance ( early depth testing )
		D_END_PROFILING("DrawPIPs");

		GraphicsAPI::Enable(GraphicsAPI::eCapability::DEPTH_TEST);
	}
	
	
}

void doom::graphics::Graphics_Server::RenderObject(doom::Camera* const targetCamera, const size_t cameraIndex)
{
	targetCamera->UpdateUniformBufferObject();


	if (doom::time::MainTimer::GetFrameStep(2))
	{
		RendererComponentStaticIterator::SortByDistanceToCamera(targetCamera, cameraIndex);
	}


	const bool targetCamera_IS_CULLED_flag_on = targetCamera->GetCameraFlag(doom::eCameraFlag::IS_CULLED);

	if (
		targetCamera_IS_CULLED_flag_on == true &&
		targetCamera->GetCameraFlag(doom::eCameraFlag::PAUSE_CULL_JOB) == false
		)
	{
		D_START_PROFILING("Wait Cull Job", doom::profiler::eProfileLayers::Rendering);
		mCullingSystem->WaitToFinishCullJob(targetCamera->CameraIndexInCullingSystem); // Waiting time is almost zero
		//resource::JobSystem::GetSingleton()->SetMemoryBarrierOnAllSubThreads();
		D_END_PROFILING("Wait Cull Job");
	}



	for (unsigned int layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
	{
		const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetRendererInLayer(layerIndex);
		for (Renderer* renderer : renderersInLayer)
		{
			if (
				targetCamera_IS_CULLED_flag_on == false ||
				renderer->GetIsCulled(targetCamera->CameraIndexInCullingSystem) == false
				)
			{
				//renderer->ColliderUpdater<doom::physics::AABB3D>::GetWorldCollider()->DrawPhysicsDebugColor(eColor::Blue);
				renderer->Draw();
			}
		}
	}
	
}








void doom::graphics::Graphics_Server::SetRenderingMode(eRenderingMode renderingMode)
{
	mCurrentRenderingMode = renderingMode;
	if (mCurrentRenderingMode == eRenderingMode::DeferredRendering)
	{
		mDeferredRenderingDrawer.Initialize();
	}
}



