#include "Graphics.h"
#include "../Game/GameCore.h"
#include "../API/OpenglAPI.h"
#include "../../Helper/SimpleIniParser.h"
#include "Buffer/UniformBufferObjectManager.h"

using namespace doom::graphics;


void Graphics::Init() 
{
	Graphics::SCREEN_WIDTH = GameCore::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "SCREEN_WIDHT");
	Graphics::SCREEN_HEIGHT = GameCore::GetSingleton()->GetConfigData().GetValue<int>("Graphics", "SCREEN_HEIGHT");

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

	Graphics::Enable(Graphics::eCapability::DEPTH_TEST);

	Graphics::Enable(Graphics::eCapability::BLEND);
	Graphics::BlendFunc(Graphics::eSourceFactor::SRC_ALPHA, Graphics::eDestinationFactor::ONE_MINUS_SRC_ALPHA);

	Graphics::Enable(Graphics::eCapability::CULL_FACE);
	Graphics::CullFace(Graphics::eCullFaceMode::BACK);
	
	Graphics::FrontFace(Graphics::eFrontFaceMode::CCW);

	return;
}

void Graphics::Update()
{
	graphics::Graphics::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	graphics::Graphics::Clear(graphics::Graphics::eClearMask::COLOR_BUFFER_BIT, graphics::Graphics::eClearMask::DEPTH_BUFFER_BIT);

	this->mUniformBufferObjectManager.Update();

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(graphics::Graphics::Window);
	glfwPollEvents();

}
