#include "GraphicsAPI.h"
#include "graphicsAPISetting.h"

#include <cassert>
#include <cstdio>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 6

namespace dooms
{
	namespace graphics
	{
		namespace opengl
		{
			enum class GetStringParameter
			{
				VENDOR = GL_VENDOR,
				RENDERER = GL_VENDOR,
				VERSION = GL_VENDOR,
				SHADING_LANGUAGE_VERSION = GL_VENDOR,
			};

			extern GLFWwindow* glfwWindow = nullptr;

			extern void DEBUG_CALLBACK
			(
				GLenum source, 
				GLenum type, 
				GLuint id, 
				GLenum severity, 
				GLsizei length, 
				const GLchar* msg, 
				const void* data
			)
			{
				//https://www.khronos.org/registry/OpenGL/extensions/KHR/KHR_debug.txt
				if (type == 0x824C || type == 0x824E)
				{
					(*dooms::graphics::GraphicsAPI::mDEBUG_FUNCTION)(msg);
				}
			}
		}
	}
}

void dooms::graphics::GraphicsAPI::Initialize()
{
	glfwInit();
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION); // 4.5 -> MAJOR 4  MINOR 5 , 3.1 -> MAJOR 3  MINOR 1
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);

#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

	if (graphicsAPISetting::GetMultiSamplingNum() > 0)
	{
		glfwWindowHint(GLFW_SAMPLES, graphicsAPISetting::GetMultiSamplingNum());
	}

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif



	// glfw window creation
	// --------------------
	dooms::graphics::opengl::glfwWindow = glfwCreateWindow(graphicsAPISetting::GetScreenWidth(), graphicsAPISetting::GetScreenHeight(), "SUNG JIN KANG", NULL, NULL);
	if (dooms::graphics::opengl::glfwWindow == NULL)
	{
		assert(false); // "Failed to create GLFW window"
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(dooms::graphics::opengl::glfwWindow);
	glfwSetFramebufferSizeCallback(dooms::graphics::opengl::glfwWindow,
		[](GLFWwindow*, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		assert(false); // Failed to initialize GLAD
		return;
	}

#ifdef _DEBUG
	std::string vendor{ reinterpret_cast<const char*>(glGetString(static_cast<const unsigned int>(dooms::graphics::opengl::GetStringParameter::VENDOR))) };
	if (vendor.find("ATI") != std::string::npos)
	{
		std::printf("Using AMD on board GPU, Maybe This will make driver error");
		assert(false);
	}

	std::printf("Current OpenGL version is : %s", glGetString(static_cast<const unsigned int>(dooms::graphics::opengl::GetStringParameter::VERSION)));
	std::printf("Vendor is : %s", vendor.c_str());
	std::printf("Renderer is : %s", glGetString(static_cast<const unsigned int>(dooms::graphics::opengl::GetStringParameter::VERSION)));
#endif // 

	glfwSetInputMode(dooms::graphics::opengl::glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glDisable(GL_SAMPLE_ALPHA_TO_ONE);
	
	if (dooms::graphics::graphicsAPISetting::DefaultIsAlphaTestOn == true)
	{
		glEnable(GL_ALPHA_TEST);
	}
	else
	{
		glDisable(GL_ALPHA_TEST);
	}

	if (dooms::graphics::graphicsAPISetting::DefaultIsBlendOn == true)
	{
		glEnable(GL_BLEND);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glFrontFace(GL_CCW);

	glfwSwapInterval(0); // disable v-sync

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(dooms::graphics::opengl::DEBUG_CALLBACK, NULL);
#endif

	int maxTextureUnitCount{ 0 };
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnitCount);
	assert(maxTextureUnitCount != 0);

	// TODO : move this 
	//dooms::ui::engineGUIServer::Initialize(dooms::graphics::opengl::glfwWindow, glsl_version);

}

void dooms::graphics::GraphicsAPI::DeInitialize()
{
	if (dooms::graphics::opengl::glfwWindow != nullptr)
	{
		glfwDestroyWindow(dooms::graphics::opengl::glfwWindow);
	}
	glfwTerminate();
}

void dooms::graphics::GraphicsAPI::SwapBuffer()
{
	assert(dooms::graphics::opengl::glfwWindow != nullptr);
	glfwSwapBuffers(dooms::graphics::opengl::glfwWindow);
}



void dooms::graphics::GraphicsAPI::SetVSync(const bool isEnabled)
{
	glfwSwapInterval(isEnabled == true ? 1 : 0);
}