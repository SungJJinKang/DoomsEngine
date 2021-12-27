#include "graphicsAPIManager.h"

#include "Graphics_Server.h"
#include "Graphics_Setting.h"
#include "EngineGUI/PrintText.h"

void dooms::graphics::graphicsAPIManager::Initialize()
{
	glfwInit();
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // 4.5 -> MAJOR 4  MINOR 5 , 3.1 -> MAJOR 3  MINOR 1
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

#ifdef DEBUG_MODE
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

	if (Graphics_Setting::GetMultiSamplingNum() > 0)
	{
		glfwWindowHint(GLFW_SAMPLES, Graphics_Setting::GetMultiSamplingNum());
	}

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif



	// glfw window creation
	// --------------------
	Graphics_Setting::SetWindow(glfwCreateWindow(Graphics_Setting::GetScreenWidth(), Graphics_Setting::GetScreenHeight(), "SUNG JIN KANG", NULL, NULL));
	if (Graphics_Setting::GetWindow() == NULL)
	{
		D_DEBUG_LOG(eLogType::D_ERROR, "Failed to create GLFW window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(Graphics_Setting::GetWindow());
	glfwSetFramebufferSizeCallback(Graphics_Setting::GetWindow(),
		[](GLFWwindow*, INT32 width, INT32 height)
		{
			glViewport(0, 0, width, height);
		}
	);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		D_DEBUG_LOG(eLogType::D_ERROR, "Failed to initialize GLAD");
		return;
	}

#ifdef DEBUG_MODE
	std::string vendor{ GraphicsAPI::GetString(GraphicsAPI::GetStringParameter::VENDOR) };
	if (vendor.find("ATI") != std::string::npos)
	{
		D_DEBUG_LOG(eLogType::D_ERROR, "Using AMD on board GPU, Maybe This will make driver error", eLogType::D_ERROR);
	}
#endif // 

	D_DEBUG_LOG(eLogType::D_LOG, "Current OpenGL version is : %s", GraphicsAPI::GetString(GraphicsAPI::GetStringParameter::VERSION));
	D_DEBUG_LOG(eLogType::D_LOG, "Vendor is : %s", vendor.c_str() );
	D_DEBUG_LOG(eLogType::D_LOG, "Renderer is : %s", GraphicsAPI::GetString(GraphicsAPI::GetStringParameter::VERSION));
	glfwSetInputMode(Graphics_Setting::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//

	GraphicsAPI::Enable(GraphicsAPI::eCapability::DEPTH_TEST);
	GraphicsAPI::DepthFunc(Graphics_Setting::DefualtDepthFuncType);

	GraphicsAPI::Disable(GraphicsAPI::eCapability::SAMPLE_ALPHA_TO_COVERAGE);
	GraphicsAPI::Disable(GraphicsAPI::eCapability::SAMPLE_ALPHA_TO_ONE);

	if (Graphics_Setting::DefaultIsAlphaTestOn == true)
	{
		glEnable(GL_ALPHA_TEST);
	}
	else
	{
		glDisable(GL_ALPHA_TEST);
	}

	if (Graphics_Setting::DefaultIsBlendOn == true)
	{
		GraphicsAPI::Enable(GraphicsAPI::eCapability::BLEND);
	}
	else
	{
		GraphicsAPI::Disable(GraphicsAPI::eCapability::BLEND);
	}

	GraphicsAPI::BlendFunc(Graphics_Setting::DefaultBlendSourceFactor, Graphics_Setting::DefaultBlendDestinationFactor);

	GraphicsAPI::Enable(GraphicsAPI::eCapability::CULL_FACE);
	GraphicsAPI::CullFace(GraphicsAPI::eCullFaceMode::BACK);

	GraphicsAPI::FrontFace(GraphicsAPI::eFrontFaceMode::CCW);

	glfwSwapInterval(0); // disable v-sync

#ifdef DEBUG_MODE
	//GraphicsAPI::Enable(GraphicsAPI::eCapability::DEBUG_OUTPUT);
	//GraphicsAPI::Enable(GraphicsAPI::eCapability::DEBUG_OUTPUT_SYNCHRONOUS);

	//glDebugMessageCallback(graphicsAPIManager::DEBUG_CALLBACK, NULL);
#endif

	INT32 maxTextureUnitCount{ 0 };
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnitCount);
	D_ASSERT(maxTextureUnitCount != 0);

	dooms::ui::engineGUIServer::Initialize(Graphics_Setting::GetWindow(), glsl_version);

}

void dooms::graphics::graphicsAPIManager::DeInitialize()
{
	dooms::ui::engineGUIServer::ShutDown();

	if(Graphics_Setting::GetWindow() != nullptr)
	{
		glfwDestroyWindow(Graphics_Setting::GetWindow());
	}
	glfwTerminate();
}

void dooms::graphics::graphicsAPIManager::DEBUG_CALLBACK(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
	//https://www.khronos.org/registry/OpenGL/extensions/KHR/KHR_debug.txt
	if (type == 0x824C || type == 0x824E)
	{
		D_DEBUG_LOG(eLogType::D_ERROR, msg);

	}
}

void dooms::graphics::graphicsAPIManager::SwapBuffer()
{
	D_ASSERT(Graphics_Setting::GetWindow() != nullptr);
	glfwSwapBuffers(Graphics_Setting::GetWindow());
		
	RESET_DRAWCALL_COUNTER;
}

void dooms::graphics::graphicsAPIManager::SetWindowTitle(const char* const title)
{
	D_ASSERT(Graphics_Setting::GetWindow() != nullptr);
	glfwSetWindowTitle(Graphics_Setting::GetWindow(), title);
}
