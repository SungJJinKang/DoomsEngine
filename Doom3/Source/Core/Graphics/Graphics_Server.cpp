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

#include <Rendering/Renderer/Renderer.h>
#include "Material.h"
#include "Texture/Texture.h"
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
	mCullDistance.Initialize();
}

void Graphics_Server::Update()
{		
	mCullDistance.OnStartDraw();
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
	for (auto& pip : mAutoDrawedPIPs)
	{
		GraphicsAPI::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		GraphicsAPI::Clear(GraphicsAPI::eClearMask::COLOR_BUFFER_BIT, GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);
		pip.get().DrawPictureInPicture();
	}
}

void doom::graphics::Graphics_Server::InitFrameBufferForDeferredRendering()
{
	if (mFrameBufferForDeferredRendering.IsGenerated() == true)
		return;

	auto gBufferDrawerShader = doom::assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>("GbufferDrawer.glsl");
	mGbufferDrawerMaterial.SetShaderAsset(gBufferDrawerShader);

	auto gBufferWriterShader = doom::assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>("GbufferWriter.glsl");
	mGbufferWriterMaterial.SetShaderAsset(gBufferWriterShader);

	mFrameBufferForDeferredRendering.GenerateBuffer(Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y);

	//with renderbuffer, can't do post-processing
	mFrameBufferForDeferredRendering.AttachTextureBuffer(GraphicsAPI::eBufferType::COLOR, Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y);
	mFrameBufferForDeferredRendering.AttachTextureBuffer(GraphicsAPI::eBufferType::COLOR, Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y);
	mFrameBufferForDeferredRendering.AttachTextureBuffer(GraphicsAPI::eBufferType::COLOR, Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y);
	mFrameBufferForDeferredRendering.AttachTextureBuffer(GraphicsAPI::eBufferType::DEPTH, Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y);

	mGbufferDrawerMaterial.AddTexture(0, &mFrameBufferForDeferredRendering.GetFrameBufferTexture(GraphicsAPI::eBufferType::COLOR, 0));
	mGbufferDrawerMaterial.AddTexture(1, &mFrameBufferForDeferredRendering.GetFrameBufferTexture(GraphicsAPI::eBufferType::COLOR, 1));
	mGbufferDrawerMaterial.AddTexture(2, &mFrameBufferForDeferredRendering.GetFrameBufferTexture(GraphicsAPI::eBufferType::COLOR, 2));

}

void Graphics_Server::PreUpdateEntityBlocks()
{
	auto activeEntityBlockList = mCullingSystem->GetActiveEntityBlockList();
	for (auto entityBlock : activeEntityBlockList)
	{
		unsigned int entityCount = entityBlock->mCurrentEntityCount;
		for (unsigned int entityIndex = 0; entityIndex < entityCount; entityIndex++)
		{
			const ::doom::Renderer* renderer = reinterpret_cast<::doom::Renderer*>(entityBlock->mRenderer[entityIndex]);

			//this is really expensive!!
			float worldRadius = const_cast<Renderer*>(renderer)->BVH_Sphere_Node_Object::GetWorldColliderCacheByReference()->mRadius;

			entityBlock->mPositions[entityIndex] = *reinterpret_cast<const culling::Vector4*>( &(renderer->GetTransform()->GetPosition()) );
			entityBlock->mPositions[entityIndex].values[3] = -(worldRadius + BOUNDING_SPHRE_RADIUS_MARGIN);

#ifdef ENABLE_SCREEN_SAPCE_AABB_CULLING
			
			std::memcpy(
				&(entityBlock->mWorldAABB[entityIndex]),
				const_cast<Renderer*>(renderer)->ColliderUpdater<doom::physics::AABB3D>::GetWorldColliderCacheByReference()->data(),
				sizeof(culling::AABB)
			);
			
#endif
		}
	}
}

void Graphics_Server::SolveLinearDataCulling()
{
	auto spawnedCameraList = StaticContainer<Camera>::GetAllStaticComponents();
	for (unsigned int i = 0; i < spawnedCameraList.size(); i++)
	{
		D_START_PROFILING(SequenceStringGenerator::GetLiteralString("UpdateFrustumPlane Camera Num: ", i), doom::profiler::eProfileLayers::Rendering);
		mCullingSystem->mViewFrustumCulling.UpdateFrustumPlane(i, *reinterpret_cast<const culling::Matrix4X4*>( &(spawnedCameraList[i]->GetViewProjectionMatrix()) ) );
#ifdef ENABLE_SCREEN_SAPCE_AABB_CULLING
		mCullingSystem->SetViewProjectionMatrix(reinterpret_cast<const culling::Matrix4X4&>(spawnedCameraList[i]->GetViewProjectionMatrix()));
#endif
		D_END_PROFILING(SequenceStringGenerator::GetLiteralString("UpdateFrustumPlane Camera Num: ", i));
	}

	mCullingSystem->SetViewProjectionMatrix(reinterpret_cast<const culling::Matrix4X4&>(Camera::GetMainCamera()->GetViewProjectionMatrix()));
	mCullingSystem->SetCameraCount(static_cast<unsigned int>(spawnedCameraList.size()));
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
	SolveLinearDataCulling(); // do this first
	//TODO : Think where put this, as early as good

	mFrameBufferForDeferredRendering.BindFrameBuffer();
	GraphicsAPI::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GraphicsAPI::Clear(mFrameBufferForDeferredRendering.mClearBit);

	auto sceneGraphics = SceneGraphics::GetSingleton();

	D_START_PROFILING("Update Uniform Buffer", doom::profiler::eProfileLayers::Rendering);
	sceneGraphics->mUniformBufferObjectManager.Update_Internal();
	sceneGraphics->mUniformBufferObjectManager.Update();
	D_END_PROFILING("Update Uniform Buffer");

#ifdef DEBUG_MODE

	//if (userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F5) == true)
	//{
		mDebugGraphics.DrawDebug();
	//}

#endif

	D_START_PROFILING("Draw Objects", doom::profiler::eProfileLayers::Rendering);
	
	//mCullDistance.PreComputeCulling();
	//mViewFrustumCulling.PreComputeCulling();

	D_START_PROFILING("Wait Cull Job", doom::profiler::eProfileLayers::Rendering);
	mCullingSystem->WaitToFinishCullJobs(); // Waiting time is almost zero
	//resource::JobSystem::GetSingleton()->SetMemoryBarrierOnAllSubThreads();
	D_END_PROFILING("Wait Cull Job");

	const unsigned int CameraCount = mCullingSystem->GetCameraCount();


	for (unsigned int cameraIndex = 0; cameraIndex < CameraCount; cameraIndex++)
	{
		D_START_PROFILING("Bind VisibleFunction", doom::profiler::eProfileLayers::Rendering);
	
		auto activeEntityBlockList = mCullingSystem->GetActiveEntityBlockList();
		for (auto entityBlock : activeEntityBlockList)
		{
			const unsigned int currentEntityCount = entityBlock->mCurrentEntityCount;

			static constexpr size_t SIMD_VISIBLE_TEST_LANE = 16 / sizeof( decltype(*(entityBlock->mIsVisibleBitflag) ));

			for (size_t simdEntityIndex = 0; simdEntityIndex < currentEntityCount; simdEntityIndex += SIMD_VISIBLE_TEST_LANE)
			{
				//Test mIsVisibleBitflag using SIMD!!!
				//Choose _m
				if (_mm_test_all_zeros(*reinterpret_cast<M128I*>(entityBlock->mIsVisibleBitflag + simdEntityIndex), _mm_set1_epi8(1 << cameraIndex)) == 1)
				{
					continue;
				}
				
				const size_t targetEntityIndex = math::Min(simdEntityIndex + SIMD_VISIBLE_TEST_LANE, currentEntityCount);
				for (size_t entityIndex = simdEntityIndex; entityIndex < targetEntityIndex; entityIndex++)
				{
					if ((entityBlock->mIsVisibleBitflag[entityIndex] & (1 << cameraIndex)) > 0)
					{
						const culling::QueryObject* const queryObject = entityBlock->mQueryObjects[entityIndex];

						if (queryObject != nullptr)
						{
							culling::QueryOcclusionCulling::StartConditionalRender(queryObject->mQueryID);
						}
						Renderer* const renderer = reinterpret_cast<::doom::Renderer*>(entityBlock->mRenderer[entityIndex]);
						renderer->Draw();
						if (queryObject != nullptr)
						{
							culling::QueryOcclusionCulling::StopConditionalRender();
						}
					}
				}
			}
		}
	}
	
	D_END_PROFILING("Draw Objects");

	FrameBuffer::UnBindFrameBuffer();

	GraphicsAPI::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GraphicsAPI::Clear(GraphicsAPI::eClearMask::COLOR_BUFFER_BIT, GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);

	mFrameBufferForDeferredRendering.BlitBufferTo(0, 0, 0, mFrameBufferForDeferredRendering.mDefaultWidth, mFrameBufferForDeferredRendering.mDefaultHeight, 0, 0, Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y, GraphicsAPI::eBufferType::DEPTH, FrameBuffer::eImageInterpolation::NEAREST);
	
	
	D_START_PROFILING("DrawPIPs", doom::profiler::eProfileLayers::Rendering);
	DrawPIPs(); // drawing pip before gbuffer will increase performance ( early depth testing )
	D_END_PROFILING("DrawPIPs");

	mGbufferDrawerMaterial.UseProgram();
	mQuadMesh->Draw();
	
	

}





const doom::graphics::FrameBuffer& Graphics_Server::GetGBuffer() const
{
	return mFrameBufferForDeferredRendering;
}

doom::graphics::FrameBuffer& Graphics_Server::GetGBuffer()
{
	return mFrameBufferForDeferredRendering;
}

void doom::graphics::Graphics_Server::SetRenderingMode(eRenderingMode renderingMode)
{
	mCurrentRenderingMode = renderingMode;
	if (mCurrentRenderingMode == eRenderingMode::DeferredRendering && mFrameBufferForDeferredRendering.IsGenerated() == false)
	{
		InitFrameBufferForDeferredRendering();
	}
}


void Graphics_Server::AddAutoDrawedPIPs(PicktureInPickture& pip)
{
	mAutoDrawedPIPs.push_back(std::ref(pip));
}

void Graphics_Server::OpenGlDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
	//https://www.khronos.org/registry/OpenGL/extensions/KHR/KHR_debug.txt
	if (type == 0x824C || type == 0x824E)
	{
		D_DEBUG_LOG(msg, eLogType::D_ERROR);
		
	}
}
