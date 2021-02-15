#include "Graphics_Server.h"

#include "Buffer/UniformBufferObjectManager.h"
#include "GraphicsAPI.h"
#include "SceneGraphics.h"
#include "Iterator/RendererStaticIterator.h"
#include "../Scene/Layer.h"
#include "../Game/GameCore.h"
#include "Renderer.h"
#include "../Game/AssetManager.h"
#include "Material.h"
#include <iostream>

using namespace doom::graphics;


void Graphics_Server::Init()
{
	int width = GameCore::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "SCREEN_WIDHT");
	int height = GameCore::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "SCREEN_HEIGHT");

	Graphics_Server::ScreenSize = { width, height };

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	glfwWindowHint(GLFW_SAMPLES, 4);
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

	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//

	GraphicsAPI::Enable(GraphicsAPI::eCapability::DEPTH_TEST);

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
	auto& debugShader = doom::assetimporter::AssetManager::GetAsset<eAssetType::SHADER>(Graphics_Server::DEBUG_SHADER).value().get();
	this->mDebugMaterial = new Material{ debugShader };

}

void Graphics_Server::Update()
{
	GraphicsAPI::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	GraphicsAPI::Clear(GraphicsAPI::eClearMask::COLOR_BUFFER_BIT, GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);

	auto sceneGraphics = SceneGraphics::GetSingleton();

	sceneGraphics->mUniformBufferObjectManager.Update_Internal();
	sceneGraphics->mUniformBufferObjectManager.Update();

	this->mDebugMaterial->UseProgram();
	for (unsigned int i = 0; i < this->mDebugMeshCount; i++)
	{
		this->mDebugMaterial->SetVector4(0, this->mDebugMeshes[i].mColor); // set color ( see defulat line debug shader )
		this->mDebugMeshes[i].mMesh.Draw();
		
	}


	for (unsigned int i = 0; i < MAX_LAYER_COUNT; i++)
	{
		auto rendererComponentPair = RendererComponentStaticIterator::GetAllComponentsWithLayerIndex(i);
		auto components = rendererComponentPair.first;
		size_t length = rendererComponentPair.second;
		for (size_t i = 0; i < length; ++i)
		{
			components[i]->UpdateComponent_Internal();
			components[i]->UpdateComponent();
		}
	}


	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------



}

void Graphics_Server::OnEndOfFrame()
{
	this->mDebugMeshCount = 0;

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

const math::Vector2& doom::graphics::Graphics_Server::GetScreenSize_const()
{
	return Graphics_Server::ScreenSize;
}

void doom::graphics::Graphics_Server::DebugDrawLine(const math::Vector3& startWorldPos, const math::Vector3& endWorldPos, const math::Vector4& color)
{
	//Don't Remove, ReCreate Mesh
	//Use previous frame's Mesh

	++this->mDebugMeshCount;
	while (this->mDebugMeshes.size() < this->mDebugMeshCount)
	{
		this->mDebugMeshes.emplace_back();
	}

	float vertex[6]{ startWorldPos.x,startWorldPos.y, startWorldPos.z, endWorldPos.x, endWorldPos.y, endWorldPos.z };
	this->mDebugMeshes[this->mDebugMeshCount - 1].mColor = color;
	this->mDebugMeshes[this->mDebugMeshCount - 1].mMesh.BufferData(6, vertex, ePrimitiveType::LINE, Mesh::eVertexArrayFlag::Vertex);
}

void doom::graphics::Graphics_Server::DebugDrawSphere(const math::Vector3& centerWorldPos, float radius, const math::Vector4& color)
{
}

void Graphics_Server::OpenGlDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
	//https://www.khronos.org/registry/OpenGL/extensions/KHR/KHR_debug.txt
	if (type == 0x824C || type == 0x824E)
	{
		std::cout << msg << std::endl;
		D_DEBUG_LOG(msg, eLogType::D_ERROR);
	}
	
}
