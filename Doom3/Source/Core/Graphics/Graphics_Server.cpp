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
#include "SceneGraphics.h"

#include "Buffer/UniformBufferObjectManager.h"
#include "Buffer/UniformBufferObjectTempBufferUpdater.h"

#include <Rendering/Renderer/Renderer.h>
#include "Material.h"
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

using namespace doom::graphics;


void Graphics_Server::Init()
{
	const int width = ConfigData::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "SCREEN_WIDTH");
	const int height = ConfigData::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "SCREEN_HEIGHT");
	Graphics_Server::MultiSamplingNum = ConfigData::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "MULTI_SAMPLE");

	Graphics_Server::ScreenSize = { width, height };
	Graphics_Server::ScreenRatio = static_cast<float>(width) / static_cast<float>(height);
	
	InitGLFW();

	mCullingSystem = std::make_unique<culling::EveryCulling>(width, height);

	return;
}

void doom::graphics::Graphics_Server::LateInit()
{
#ifdef DEBUG_MODE
	mDebugGraphics.Init();
#endif

	SetRenderingMode(Graphics_Server::eRenderingMode::DeferredRendering);
	mQuadMesh = Mesh::GetQuadMesh();

	//mQueryOcclusionCulling.InitQueryOcclusionCulling();
	//mCullDistance.Initialize();
}

void Graphics_Server::Update()
{		
	//mCullDistance.OnStartDraw();
	DeferredRendering();
	


}

void Graphics_Server::OnEndOfFrame()
{

	auto sceneGraphics = SceneGraphics::GetSingleton();

	sceneGraphics->mUniformBufferObjectManager.OnEndOfFrame_Internal();
	sceneGraphics->mUniformBufferObjectManager.OnEndOfFrame();

	for (unsigned int i = 0; i < MAX_LAYER_COUNT; i++)
	{
		auto rendererComponentPair = RendererComponentStaticIterator::GetAllComponentsWithLayerIndex(i);
		auto components = rendererComponentPair.first;
		size_t length = rendererComponentPair.second;
		for (size_t i = 0; i < length; ++i)
		{
			components[i]->OnEndOfFrame_Component_Internal();
			components[i]->OnEndOfFrame_Component();
		}
	}

#ifdef DEBUG_MODE
	if (userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F3))
	{
		D_DEBUG_LOG(std::to_string(GraphicsAPI::DrawCallCounter), eLogType::D_ALWAYS);
	}
	GraphicsAPI::DrawCallCounter = 0;
#endif
	glfwSwapBuffers(Graphics_Server::Window);
}

int Graphics_Server::GetScreenWidth()
{
	return Graphics_Server::Graphics_Server::ScreenSize.x;
}

int Graphics_Server::GetScreenHeight()
{
	return Graphics_Server::Graphics_Server::ScreenSize.y;
}

bool Graphics_Server::GetIsGLFWInitialized()
{
	return bmIsGLFWInitialized;
}

Graphics_Server::Graphics_Server()
{

}

Graphics_Server::~Graphics_Server()
{

}

math::Vector2 doom::graphics::Graphics_Server::GetScreenSize()
{
	return Graphics_Server::ScreenSize;
}

float doom::graphics::Graphics_Server::GetScreenRatio()
{
	return Graphics_Server::ScreenRatio;
}

void Graphics_Server::InitGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // 4.5 -> MAJOR 4  MINOR 5 , 3.1 -> MAJOR 3  MINOR 1
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	if (Graphics_Server::MultiSamplingNum > 0)
	{
		glfwWindowHint(GLFW_SAMPLES, Graphics_Server::MultiSamplingNum);
	}

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


	// glfw window creation
	// --------------------
	Window = glfwCreateWindow(Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y, "LearnOpenGL", NULL, NULL);
	if (Window == NULL)
	{
		D_DEBUG_LOG("Failed to create GLFW window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(Window);
	glfwSetFramebufferSizeCallback(Window,
		[](GLFWwindow*, int width, int height) 
		{
			glViewport(0, 0, width, height); 
		}
	);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		D_DEBUG_LOG("Failed to initialize GLAD");
		return;
	}

#ifdef DEBUG_MODE
	std::string vendor{ GraphicsAPI::GetString(GraphicsAPI::GetStringParameter::VENDOR) };
	if (vendor.find("ATI") != std::string::npos)
	{
	D_DEBUG_LOG("Using AMD on board GPU, Maybe This will make driver error", eLogType::D_ERROR);
	}
#endif // 

	D_DEBUG_LOG({ "Current OpenGL version is : ", std::string(GraphicsAPI::GetString(GraphicsAPI::GetStringParameter::VERSION)) });
	D_DEBUG_LOG({ "Vendor is : ", vendor });
	D_DEBUG_LOG({ "Renderer is : ", std::string(GraphicsAPI::GetString(GraphicsAPI::GetStringParameter::RENDERER)) });
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//

	GraphicsAPI::Enable(GraphicsAPI::eCapability::DEPTH_TEST);
	//GraphicsAPI::DepthFunc(GraphicsAPI::eDepthFuncType::LEQUAL);;

	GraphicsAPI::Enable(GraphicsAPI::eCapability::BLEND);
	GraphicsAPI::BlendFunc(GraphicsAPI::eSourceFactor::SRC_ALPHA, GraphicsAPI::eDestinationFactor::ONE_MINUS_SRC_ALPHA);

	GraphicsAPI::Enable(GraphicsAPI::eCapability::CULL_FACE);
	GraphicsAPI::CullFace(GraphicsAPI::eCullFaceMode::BACK);

	GraphicsAPI::FrontFace(GraphicsAPI::eFrontFaceMode::CCW);

	glfwSwapInterval(0); // disable v-sync

#ifdef DEBUG_MODE
	GraphicsAPI::Enable(GraphicsAPI::eCapability::DEBUG_OUTPUT);
	GraphicsAPI::Enable(GraphicsAPI::eCapability::DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(Graphics_Server::OpenGlDebugCallback, NULL);
#endif

	int maxTextureUnitCount{ 0 };
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnitCount);
	D_ASSERT(maxTextureUnitCount != 0);

	bmIsGLFWInitialized = true;
}

void Graphics_Server::DrawPIPs()
{
	for (std::shared_ptr<PicktureInPickture>& pip : mAutoDrawedPIPs)
	{
		GraphicsAPI::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		GraphicsAPI::Clear(GraphicsAPI::eClearMask::COLOR_BUFFER_BIT, GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);
		pip->DrawPictureInPicture();
	}
}

void doom::graphics::Graphics_Server::InitFrameBufferForDeferredRendering()
{
	auto gBufferDrawerShader = doom::assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>("GbufferDrawer.glsl");
	mGbufferDrawerMaterial.SetShaderAsset(gBufferDrawerShader);

	auto gBufferWriterShader = doom::assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>("GbufferWriter.glsl");
	mGbufferWriterMaterial.SetShaderAsset(gBufferWriterShader);

	/*
	mGbufferDrawerMaterial.AddTexture(0, &mFrameBufferForDeferredRendering.GetFrameBufferTexture(GraphicsAPI::eBufferType::COLOR, 0));
	mGbufferDrawerMaterial.AddTexture(1, &mFrameBufferForDeferredRendering.GetFrameBufferTexture(GraphicsAPI::eBufferType::COLOR, 1));
	mGbufferDrawerMaterial.AddTexture(2, &mFrameBufferForDeferredRendering.GetFrameBufferTexture(GraphicsAPI::eBufferType::COLOR, 2));
	*/
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

			//this is really expensive!!
			float worldRadius = renderer->BVH_Sphere_Node_Object::GetWorldColliderCacheByReference()->mRadius;

			const math::Vector3 renderedObjectPos = renderer->GetTransform()->GetPosition();

			entityBlock->mPositions[entityIndex].SetPosition(*reinterpret_cast<const culling::Vector3*>(&renderedObjectPos));
			entityBlock->mPositions[entityIndex].SetBoundingSphereRadius(worldRadius);

#ifdef ENABLE_SCREEN_SAPCE_AABB_CULLING
			
			std::memcpy(
				entityBlock->mWorldAABB + entityIndex,
				const_cast<Renderer*>(renderer)->ColliderUpdater<doom::physics::AABB3D>::GetWorldColliderCacheByReference()->data(),
				sizeof(culling::AABB)
			);
			
#endif

		}
	}
}

void Graphics_Server::DoCullJob()
{
	const std::vector<doom::Camera*>& spawnedCameraList = StaticContainer<doom::Camera>::GetAllStaticComponents();

	unsigned int CullJobAvailiableCameraCount = 0;
	for (doom::Camera* camera : spawnedCameraList)
	{
		if ((camera->mCameraFlag & doom::eCameraFlag::IS_CULLED) != 0)
		{
			camera->CameraIndexInCullingSystem = CullJobAvailiableCameraCount;

			D_START_PROFILING(SequenceStringGenerator::GetLiteralString("UpdateFrustumPlane Camera Num: ", CullJobAvailiableCameraCount), doom::profiler::eProfileLayers::Rendering);

			mCullingSystem->SetViewProjectionMatrix(CullJobAvailiableCameraCount, *reinterpret_cast<const culling::Matrix4X4*>(&(camera->GetViewProjectionMatrix())));

			D_END_PROFILING(SequenceStringGenerator::GetLiteralString("UpdateFrustumPlane Camera Num: ", CullJobAvailiableCameraCount));

			CullJobAvailiableCameraCount++;
		}
	
	}

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

void doom::graphics::Graphics_Server::DeferredRendering()
{
	DoCullJob(); // do this first
	//TODO : Think where put this, as early as good

	const std::vector<doom::Camera*>& spawnedCameraList = StaticContainer<doom::Camera>::GetAllStaticComponents();

	D_START_PROFILING("Update Uniform Buffer", doom::profiler::eProfileLayers::Rendering);
	SceneGraphics::GetSingleton()->mUniformBufferObjectManager.Update_Internal();
	SceneGraphics::GetSingleton()->mUniformBufferObjectManager.Update();
	D_END_PROFILING("Update Uniform Buffer");

	FrameBuffer::UnBindFrameBuffer();

	//Clear MainBuffer
	GraphicsAPI::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GraphicsAPI::Clear(GraphicsAPI::eClearMask::COLOR_BUFFER_BIT, GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);

	for (doom::Camera* camera : spawnedCameraList)
	{
		camera->mDefferedRenderingFrameBuffer.BindFrameBuffer();

		GraphicsAPI::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		GraphicsAPI::Clear(camera->mDefferedRenderingFrameBuffer.mClearBit);

#ifdef DEBUG_MODE

		//if (userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F5) == true)
		//{
		mDebugGraphics.DrawDebug();
		//}

#endif

		D_START_PROFILING("Draw Objects", doom::profiler::eProfileLayers::Rendering);

		RenderObject(camera);

		camera->mDefferedRenderingFrameBuffer.UnBindFrameBuffer();

		D_END_PROFILING("Draw Objects");

		//Blit DepthBuffer To ScreenBuffer
		camera->mDefferedRenderingFrameBuffer.BlitBufferTo(0, 0, 0, camera->mDefferedRenderingFrameBuffer.mDefaultWidth, camera->mDefferedRenderingFrameBuffer.mDefaultHeight, 0, 0, Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y, GraphicsAPI::eBufferType::DEPTH, FrameBuffer::eImageInterpolation::NEAREST);

		camera->mDefferedRenderingFrameBuffer.BindGBufferTextures();
		mGbufferDrawerMaterial.UseProgram();
		mQuadMesh->Draw();
	}



	//D_START_PROFILING("DrawPIPs", doom::profiler::eProfileLayers::Rendering);
	//DrawPIPs(); // drawing pip before gbuffer will increase performance ( early depth testing )
	//D_END_PROFILING("DrawPIPs");
	
	
	

}

void doom::graphics::Graphics_Server::RenderObject(doom::Camera* const camera)
{
	camera->UpdateUniformBufferObjectTempBuffer();

	SceneGraphics::GetSingleton()->mUniformBufferObjectManager.BufferDateOfUniformBufferObjects();

	if ( (camera->mCameraFlag & eCameraFlag::IS_CULLED) == 0)
	{
		for (unsigned int layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
		{
			std::pair<Renderer**, size_t> renderersInLayer = RendererComponentStaticIterator::GetAllComponentsWithLayerIndex(layerIndex);
			for (size_t rendererIndex = 0; rendererIndex < renderersInLayer.second; rendererIndex++)
			{
				renderersInLayer.first[rendererIndex]->Draw();
			}
		}
	}
	else
	{
		D_START_PROFILING("Wait Cull Job", doom::profiler::eProfileLayers::Rendering);
		mCullingSystem->WaitToFinishCullJobs(); // Waiting time is almost zero
		//resource::JobSystem::GetSingleton()->SetMemoryBarrierOnAllSubThreads();
		D_END_PROFILING("Wait Cull Job");

		const std::vector<culling::EntityBlock*>& activeEntityBlockList = mCullingSystem->GetActiveEntityBlockList();
		for (const culling::EntityBlock* entityBlock : activeEntityBlockList)
		{
			const unsigned int currentEntityCount = entityBlock->mCurrentEntityCount;

			static constexpr size_t SIMD_VISIBLE_TEST_LANE = 16 / sizeof(decltype(*(entityBlock->mIsVisibleBitflag)));

			for (size_t simdEntityIndex = 0; simdEntityIndex < currentEntityCount; simdEntityIndex += SIMD_VISIBLE_TEST_LANE)
			{
				//Test mIsVisibleBitflag using SIMD!!!
				//Choose _m
				if (_mm_test_all_zeros(*reinterpret_cast<const M128I*>(entityBlock->mIsVisibleBitflag + simdEntityIndex), _mm_set1_epi8(1 << camera->CameraIndexInCullingSystem)) == 1)
				{
					continue;
				}

				const size_t targetEntityIndex = math::Min(simdEntityIndex + SIMD_VISIBLE_TEST_LANE, currentEntityCount);
				for (size_t entityIndex = simdEntityIndex; entityIndex < targetEntityIndex; entityIndex++)
				{

					/*const culling::QueryObject* const queryObject = entityBlock->mQueryObjects[entityIndex];

					if (queryObject != nullptr)
					{
						culling::QueryOcclusionCulling::StartConditionalRender(queryObject->mQueryID);
					}*/

					Renderer* const renderer = reinterpret_cast<::doom::Renderer*>(entityBlock->mRenderer[entityIndex]);
					if (renderer->GetIsCulled(camera->CameraIndexInCullingSystem) == false)
					{
						renderer->Draw();
					}

					/*if (queryObject != nullptr)
					{
						culling::QueryOcclusionCulling::StopConditionalRender();
					}*/

				}
			}
		}
	}
	
}

void doom::graphics::Graphics_Server::RenderObjects()
{
	const std::vector<doom::Camera*>& cameraList = StaticContainer<doom::Camera>::GetAllStaticComponents();
	
	for (doom::Camera* camera : cameraList)
	{
		RenderObject(camera);
	}
}






void doom::graphics::Graphics_Server::SetRenderingMode(eRenderingMode renderingMode)
{
	mCurrentRenderingMode = renderingMode;
	if (mCurrentRenderingMode == eRenderingMode::DeferredRendering)
	{
		InitFrameBufferForDeferredRendering();
	}
}


void Graphics_Server::AddAutoDrawedPIPs(const std::shared_ptr<PicktureInPickture>& pip)
{
	mAutoDrawedPIPs.push_back(pip);
}

void Graphics_Server::OpenGlDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
	//https://www.khronos.org/registry/OpenGL/extensions/KHR/KHR_debug.txt
	if (type == 0x824C || type == 0x824E)
	{
		D_DEBUG_LOG(msg, eLogType::D_ERROR);
		
	}
}
