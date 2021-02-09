#include "GraphicsManager.h"

#include "../Game/GameCore.h"
#include "../API/OpenglAPI.h"
#include "GraphicsAPI.h"
#include "../../Helper/SimpleIniParser.h"
#include "Buffer/UniformBufferObjectManager.h"

using namespace doom::graphics;


void GraphicsManager::Init()
{
	GraphicsManager::SCREEN_WIDTH = GameCore::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "SCREEN_WIDHT");
	GraphicsManager::SCREEN_HEIGHT = GameCore::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "SCREEN_HEIGHT");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	//glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


	// glfw window creation
	// --------------------
	Window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (Window == NULL)
	{
		D_DEBUG_LOG("Failed to create GLFW window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(Window);
	glfwSetFramebufferSizeCallback(Window,
		[](GLFWwindow*, int, int) {glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); }
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

	return;
}

void GraphicsManager::Update()
{
	graphics::GraphicsAPI::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	graphics::GraphicsAPI::Clear(graphics::GraphicsAPI::eClearMask::COLOR_BUFFER_BIT, graphics::GraphicsAPI::eClearMask::DEPTH_BUFFER_BIT);

	auto sceneGraphics = SceneGraphics::GetSingleton();
	sceneGraphics->mUniformBufferObjectManager.Update_Internal();
	sceneGraphics->mUniformBufferObjectManager.Update();

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(graphics::GraphicsManager::Window);
	glfwPollEvents();

}

void doom::graphics::GraphicsManager::OnEndOfFrame()
{
	auto sceneGraphics = SceneGraphics::GetSingleton();
	sceneGraphics->mUniformBufferObjectManager.OnEndOfFrame_Internal();
	sceneGraphics->mUniformBufferObjectManager.OnEndOfFrame();
}
