#include "Graphics.h"
#include "../Game/GameCore.h"
#include "../API/OpenglAPI.h"
#include "../../Helper/IniParser.h"

using namespace Doom;

GLFWwindow* Graphics::Window{};
int Graphics::SCREEN_WIDTH{};
int Graphics::SCREEN_HEIGHT{};

void Graphics::Init()
{
	Graphics::SCREEN_WIDTH = GameCore::ConfigData.GetValue<int>("Graphics", "SCREEN_WIDHT");
	Graphics::SCREEN_HEIGHT = GameCore::ConfigData.GetValue<int>("Graphics", "SCREEN_HEIGHT");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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
		DEBUG_LOG("Failed to create GLFW window");
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
		DEBUG_LOG("Failed to initialize GLAD");
		return;
	}

	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//

	Graphics::Enable(Graphics::Capability::DEPTH_TEST);

	Graphics::Enable(Graphics::Capability::BLEND);
	Graphics::BlendFunc(Graphics::SourceFactor::SRC_ALPHA, Graphics::DestinationFactor::ONE_MINUS_SRC_ALPHA);

	Graphics::Enable(Graphics::Capability::CULL_FACE);
	Graphics::CullFace(Graphics::CullFaceMode::BACK);
	
	Graphics::FrontFace(Graphics::FrontFaceMode::CCW);

	return;
}
