#include "Graphics_Server.h"

#include <iostream>
#include <string>

#include "../Game/GameCore.h"
#include "../Game/ConfigData.h"
#include "../Scene/Layer.h"
#include "../Game/AssetManager.h"

#include "GraphicsAPI.h"
#include "SceneGraphics.h"

#include "Buffer/UniformBufferObjectManager.h"

#include "Renderer.h"
#include "Material.h"
#include "Iterator/RendererStaticIterator.h"



using namespace doom::graphics;


void Graphics_Server::Init()
{
	int width = ConfigData::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "SCREEN_WIDTH");
	int height = ConfigData::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "SCREEN_HEIGHT");
	Graphics_Server::MultiSamplingNum = ConfigData::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "MULTI_SAMPLE");

	Graphics_Server::ScreenSize = { width, height };
	Graphics_Server::ScreenRatio = static_cast<float>(height) / static_cast<float>(width);
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
		[](GLFWwindow*, int, int) {glViewport(0, 0, Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y); }
	);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		D_DEBUG_LOG("Failed to initialize GLAD");
		return;
	}

	D_DEBUG_LOG({ "Current OpenGL version is : ", std::string(GraphicsAPI::GetString(GraphicsAPI::GetStringParameter::VERSION)) });
	D_DEBUG_LOG({ "Vendor is : ", std::string(GraphicsAPI::GetString(GraphicsAPI::GetStringParameter::VENDOR)) });
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

#ifdef DEBUG_MODE
	GraphicsAPI::Enable(GraphicsAPI::eCapability::DEBUG_OUTPUT);
	GraphicsAPI::Enable(GraphicsAPI::eCapability::DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(Graphics_Server::OpenGlDebugCallback, NULL);
#endif
	return;
}

void doom::graphics::Graphics_Server::LateInit()
{
#ifdef DEBUG_MODE
	this->mDebugGraphics.Init();
#endif

	this->SetRenderingMode(Graphics_Server::eRenderingMode::DeferredRendering);
	this->mQuadMesh = Mesh::GetQuadMesh();

}

void Graphics_Server::Update()
{
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

math::Vector2 doom::graphics::Graphics_Server::GetScreenSize()
{
	return Graphics_Server::ScreenSize;
}

float doom::graphics::Graphics_Server::GetScreenRatio()
{
	return Graphics_Server::ScreenRatio;
}

void doom::graphics::Graphics_Server::InitFrameBufferForDeferredRendering()
{
	if (this->mFrameBufferForDeferredRendering.IsGenerated() == true)
		return;

	auto gBufferDrawerShader = doom::assetimporter::AssetManager::GetAsset<eAssetType::SHADER>("GbufferDrawer.glsl");
	this->mGbufferDrawerMaterial.SetShaderAsset(*gBufferDrawerShader);

	auto gBufferWriterShader = doom::assetimporter::AssetManager::GetAsset<eAssetType::SHADER>("GbufferWriter.glsl");
	this->mGbufferWriterMaterial.SetShaderAsset(*gBufferWriterShader);

	this->mFrameBufferForDeferredRendering.GenerateBuffer(Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y);
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
	this->mFrameBufferForDeferredRendering.BindFrameBuffer();
	GraphicsAPI::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GraphicsAPI::Clear(this->mFrameBufferForDeferredRendering.mClearBit);

	auto sceneGraphics = SceneGraphics::GetSingleton();

	sceneGraphics->mUniformBufferObjectManager.Update_Internal();
	sceneGraphics->mUniformBufferObjectManager.Update();

#ifdef DEBUG_MODE
	this->mDebugGraphics.DrawDebug();
#endif

	for (unsigned int i = 0; i < MAX_LAYER_COUNT; i++)
	{
		auto rendererComponentPair = RendererComponentStaticIterator::GetAllComponentsWithLayerIndex(i);
		doom::Renderer** renderers = rendererComponentPair.first;
		size_t length = rendererComponentPair.second;
		for (size_t i = 0; i < length; ++i)
		{
			renderers[i]->UpdateComponent_Internal();
			renderers[i]->UpdateComponent();
		}
	}
	
	FrameBuffer::UnBindFrameBuffer();

	GraphicsAPI::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GraphicsAPI::Clear(GraphicsAPI::eClearMask::COLOR_BUFFER_BIT, GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);

	this->mFrameBufferForDeferredRendering.BlitBufferTo(0, 0, 0, this->mFrameBufferForDeferredRendering.mDefaultWidth, this->mFrameBufferForDeferredRendering.mDefaultHeight, 0, 0, Graphics_Server::ScreenSize.x, Graphics_Server::ScreenSize.y, GraphicsAPI::eBufferType::DEPTH, FrameBuffer::eImageInterpolation::NEAREST);
	


	//TO DO : Draw Quad
	this->mGbufferDrawerMaterial.UseProgram();
	this->mQuadMesh->Draw();
	


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





void Graphics_Server::OpenGlDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
	//https://www.khronos.org/registry/OpenGL/extensions/KHR/KHR_debug.txt
	if (type == 0x824C || type == 0x824E)
	{
		D_DEBUG_LOG(msg, eLogType::D_ERROR);
		
	}
}
