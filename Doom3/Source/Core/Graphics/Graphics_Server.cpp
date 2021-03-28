#include "Graphics_Server.h"

#include <iostream>
#include <string>

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

#include "Physics/Collider/Plane.h"

using namespace doom::graphics;


void Graphics_Server::Init()
{
	int width = ConfigData::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "SCREEN_WIDTH");
	int height = ConfigData::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "SCREEN_HEIGHT");
	Graphics_Server::MultiSamplingNum = ConfigData::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "MULTI_SAMPLE");

	Graphics_Server::ScreenSize = { width, height };
	Graphics_Server::ScreenRatio = static_cast<float>(width) / static_cast<float>(height);
	
	this->InitGLFW();


	return;
}

void doom::graphics::Graphics_Server::LateInit()
{
#ifdef DEBUG_MODE
	this->mDebugGraphics.Init();
#endif

	this->SetRenderingMode(Graphics_Server::eRenderingMode::DeferredRendering);
	this->mQuadMesh = Mesh::GetQuadMesh();

	//this->mQueryOcclusionCulling.InitHWOcclusionCulling();
	this->mCullDistance.Initialize();
}

void Graphics_Server::Update()
{
	this->mCullDistance.OnStartDraw();
	this->DeferredRendering();
	


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
	return this->bmIsGLFWInitialized;
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
	Texture::InitTextureUnitTag(maxTextureUnitCount);

	bmIsGLFWInitialized = true;
}

void Graphics_Server::DrawPIPs()
{
	for (auto& pip : this->mAutoDrawedPIPs)
	{
		GraphicsAPI::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		GraphicsAPI::Clear(GraphicsAPI::eClearMask::COLOR_BUFFER_BIT, GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);
		pip.get().DrawPictureInPicture();
	}
}

void doom::graphics::Graphics_Server::InitFrameBufferForDeferredRendering()
{
	if (this->mFrameBufferForDeferredRendering.IsGenerated() == true)
		return;

	auto gBufferDrawerShader = doom::assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>("GbufferDrawer.glsl");
	this->mGbufferDrawerMaterial.SetShaderAsset(gBufferDrawerShader);

	auto gBufferWriterShader = doom::assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>("GbufferWriter.glsl");
	this->mGbufferWriterMaterial.SetShaderAsset(gBufferWriterShader);

	this->mFrameBufferForDeferredRendering.GenerateBuffer(Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y);

	//with renderbuffer, can't do post-processing
	this->mFrameBufferForDeferredRendering.AttachTextureBuffer(GraphicsAPI::eBufferType::COLOR, Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y);
	this->mFrameBufferForDeferredRendering.AttachTextureBuffer(GraphicsAPI::eBufferType::COLOR, Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y);
	this->mFrameBufferForDeferredRendering.AttachTextureBuffer(GraphicsAPI::eBufferType::COLOR, Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y);
	this->mFrameBufferForDeferredRendering.AttachTextureBuffer(GraphicsAPI::eBufferType::DEPTH, Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y);

	this->mGbufferDrawerMaterial.AddTexture(0, &this->mFrameBufferForDeferredRendering.GetFrameBufferTexture(GraphicsAPI::eBufferType::COLOR, 0));
	this->mGbufferDrawerMaterial.AddTexture(1, &this->mFrameBufferForDeferredRendering.GetFrameBufferTexture(GraphicsAPI::eBufferType::COLOR, 1));
	this->mGbufferDrawerMaterial.AddTexture(2, &this->mFrameBufferForDeferredRendering.GetFrameBufferTexture(GraphicsAPI::eBufferType::COLOR, 2));

}

void doom::graphics::Graphics_Server::DeferredRendering()
{
	SolveLinearDataCulling(); // do this first
	//TODO : Think where put this, as early as good

	this->mFrameBufferForDeferredRendering.BindFrameBuffer();
	GraphicsAPI::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GraphicsAPI::Clear(this->mFrameBufferForDeferredRendering.mClearBit);

	auto sceneGraphics = SceneGraphics::GetSingleton();

	D_START_PROFILING("Update Uniform Buffer", doom::profiler::eProfileLayers::Rendering);
	sceneGraphics->mUniformBufferObjectManager.Update_Internal();
	sceneGraphics->mUniformBufferObjectManager.Update();
	D_END_PROFILING("Update Uniform Buffer");

#ifdef DEBUG_MODE

	auto simdplane = this->mLinearTransformDataCulling.GetSIMDPlanes()->mFrustumPlanes;
	physics::Plane plane1{ simdplane[3][0], math::Vector3{simdplane[0][0], simdplane[1][0], simdplane[2][0]} };
	plane1.DrawPhysicsDebugColor(eColor::Black, false);

	physics::Plane plane2{ simdplane[3][1], math::Vector3{simdplane[0][1], simdplane[1][1], simdplane[2][1]} };
	plane2.DrawPhysicsDebugColor(eColor::Blue, false);

	physics::Plane plane3{ simdplane[3][2], math::Vector3{simdplane[0][2], simdplane[1][2], simdplane[2][2]} };
	plane3.DrawPhysicsDebugColor(eColor::Green, false);

	physics::Plane plane4{ simdplane[3][3], math::Vector3{simdplane[0][3], simdplane[1][3], simdplane[2][3]} };
	plane4.DrawPhysicsDebugColor(eColor::Red, false);

	physics::Plane plane5{ simdplane[7][0], math::Vector3{simdplane[4][0], simdplane[5][0], simdplane[6][0]} };
	plane5.DrawPhysicsDebugColor(eColor::White, false);

	physics::Plane plane6{ simdplane[7][1], math::Vector3{simdplane[4][1], simdplane[5][1], simdplane[6][1]} };
	plane6.DrawPhysicsDebugColor(eColor::Black, false);




	if (userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F5) == true)
	{
		this->mDebugGraphics.DrawDebug();
	}


#endif

	D_START_PROFILING("Draw Objects", doom::profiler::eProfileLayers::Rendering);
	
	//this->mCullDistance.PreComputeCulling();
	//this->mViewFrustumCulling.PreComputeCulling();

	D_START_PROFILING("Wait Cull Job", doom::profiler::eProfileLayers::Rendering);
	this->mLinearTransformDataCulling.WaitToFinishCullJobs();
	D_END_PROFILING("Wait Cull Job");

	for (unsigned int i = 0; i < MAX_LAYER_COUNT; i++)
	{
		auto rendererComponentPair = RendererComponentStaticIterator::GetAllComponentsWithLayerIndex(i);
		doom::Renderer** renderers = rendererComponentPair.first;
		size_t length = rendererComponentPair.second;
	
		for (size_t i = 0; i < length; ++i)
		{
			if (renderers[i]->GetIsVisible(0) == true) // HEAVY
			{
				renderers[i]->UpdateComponent_Internal();
				renderers[i]->UpdateComponent();
				renderers[i]->Draw(); // HEAVY
			}
		}
	}
	D_END_PROFILING("Draw Objects");

	FrameBuffer::UnBindFrameBuffer();

	GraphicsAPI::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GraphicsAPI::Clear(GraphicsAPI::eClearMask::COLOR_BUFFER_BIT, GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);

	this->mFrameBufferForDeferredRendering.BlitBufferTo(0, 0, 0, this->mFrameBufferForDeferredRendering.mDefaultWidth, this->mFrameBufferForDeferredRendering.mDefaultHeight, 0, 0, Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y, GraphicsAPI::eBufferType::DEPTH, FrameBuffer::eImageInterpolation::NEAREST);
	

	//TO DO : Draw Quad
	this->DrawPIPs(); // drawing pip before gbuffer will increase performance ( early depth testing )
	
	this->mGbufferDrawerMaterial.UseProgram();
	this->mQuadMesh->Draw();
	
	

}


void Graphics_Server::SolveLinearDataCulling()
{
	auto spawnedCameraList = StaticContainer<Camera>::GetAllStaticComponents();
	for (unsigned int i = 0; i < spawnedCameraList.size(); i++)
	{
		//TODO : When camera is desroied, Shoud Update all cameras
// 		if (spawnedCameraList[i]->bmIsFrustumPlaneMatrixDirty.GetIsDirty(true) == true)
// 		{
// 			this->mLinearTransformDataCulling.UpdateFrustumPlane(i, spawnedCameraList[i]->GetViewProjectionMatrix());
// 		}

		// TODO : should use dirty
		// Don't update frustumplane always
		//
		// for testing, update always
		
		D_DEBUG_LOG(this->mLinearTransformDataCulling.GetSIMDPlanes()->mFrustumPlanes[0].toString(), eLogType::D_ALWAYS);
		this->mLinearTransformDataCulling.UpdateFrustumPlane(i, spawnedCameraList[i]->GetModelViewProjectionMatrix());
	}

	
	
	

	this->mLinearTransformDataCulling.SetCameraCount(spawnedCameraList.size());
	this->mLinearTransformDataCulling.ResetCullJobState();
	// TODO : 이렇게 매 프레임마다 std::vector<std::function<void()>> 생성하는 건 매우 큰 overhead이다.
	auto CullingBlockJobs = this->mLinearTransformDataCulling.GetCullBlockEnityJobs();
	resource::JobSystem::GetSingleton()->PushBackJobChunkToPriorityQueue(std::move(CullingBlockJobs));
	
}

const doom::graphics::FrameBuffer& Graphics_Server::GetGBuffer() const
{
	return this->mFrameBufferForDeferredRendering;
}

doom::graphics::FrameBuffer& Graphics_Server::GetGBuffer()
{
	return this->mFrameBufferForDeferredRendering;
}

void doom::graphics::Graphics_Server::SetRenderingMode(eRenderingMode renderingMode)
{
	this->mCurrentRenderingMode = renderingMode;
	if (this->mCurrentRenderingMode == eRenderingMode::DeferredRendering && this->mFrameBufferForDeferredRendering.IsGenerated() == false)
	{
		this->InitFrameBufferForDeferredRendering();
	}
}


void Graphics_Server::AddAutoDrawedPIPs(PicktureInPickture& pip)
{
	this->mAutoDrawedPIPs.push_back(std::ref(pip));
}

void Graphics_Server::OpenGlDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
	//https://www.khronos.org/registry/OpenGL/extensions/KHR/KHR_debug.txt
	if (type == 0x824C || type == 0x824E)
	{
		D_DEBUG_LOG(msg, eLogType::D_ERROR);
		
	}
}
