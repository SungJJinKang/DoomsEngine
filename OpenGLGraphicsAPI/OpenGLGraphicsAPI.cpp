#include "GraphicsAPI.h"
#include "graphicsAPISetting.h"

#include <cassert>
#include <cstdio>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GraphicsAPI.h"
#include "GraphicsAPI.h"
#include "GraphicsAPI.h"
#include "GraphicsAPI.h"

#define OPENGL_MAJOR_VERSION 4
#define OPENGL_MINOR_VERSION 6

#undef NEVER_HAPPEN
#ifdef _DEBUG
#define NEVER_HAPPEN assert(false)
#else
#define NEVER_HAPPEN __assume(0)
#endif


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

			inline extern unsigned int GetGLTextureInternalFormat(const graphics::GraphicsAPI::eTextureInternalFormat textureInternalFormat)
			{
				switch (textureInternalFormat)
				{

				case GraphicsAPI::eTextureInternalFormat::RGBA16F:
					return GL_RGBA16F;
					
				default:
					NEVER_HAPPEN;

				}
			}

			inline extern unsigned int GetGLBufferTarget(const GraphicsAPI::eBufferTarget bufferTarget)
			{
				switch (bufferTarget)
				{
				case GraphicsAPI::eBufferTarget::ARRAY_BUFFER:
					return GL_ARRAY_BUFFER;

				case GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER:
					return GL_ELEMENT_ARRAY_BUFFER_BINDING;

				case GraphicsAPI::eBufferTarget::TEXTURE_BUFFER:
					return GL_TEXTURE_BUFFER;

				case GraphicsAPI::DRAW_INDIRECT_BUFFER: 
					return GL_DRAW_INDIRECT_BUFFER;

				case GraphicsAPI::UNIFORM_BUFFER:
					return GL_UNIFORM_BUFFER;

				default:
					NEVER_HAPPEN;
				}
			}

			inline extern unsigned int GetGLBufferBitType(const GraphicsAPI::eBufferBitType bufferType)
			{
				switch (bufferType)
				{
				case GraphicsAPI::COLOR_BUFFER: 
					return GL_COLOR_BUFFER_BIT;
				case GraphicsAPI::DEPTH_BUFFER: 
					return GL_DEPTH_BUFFER_BIT;
				case GraphicsAPI::DEPTH_STENCIL_BUFFER: 
					return GL_STENCIL_BUFFER_BIT;
				default:
					NEVER_HAPPEN;
				}
			}

			inline extern unsigned int GetGLBufferBitType(const unsigned int bufferTypeBits)
			{
				unsigned int bufferBitType = 0;
				if(bufferTypeBits & GraphicsAPI::COLOR_BUFFER != 0)
				{
					bufferBitType |= GL_COLOR_BUFFER_BIT;
				}
				if (bufferTypeBits & GraphicsAPI::DEPTH_BUFFER != 0)
				{
					bufferBitType |= GL_DEPTH_BUFFER_BIT;
				}
				if (bufferTypeBits & GraphicsAPI::DEPTH_STENCIL_BUFFER != 0)
				{
					bufferBitType |= GL_STENCIL_BUFFER_BIT;
				}
				return bufferBitType;
			}

			inline extern unsigned int GetGLBufferType(const GraphicsAPI::eBufferType bufferType)
			{
				switch (bufferType)
				{
				case GraphicsAPI::eBufferType::COLOR:
					return GL_COLOR;
				case GraphicsAPI::eBufferType::DEPTH:
					return GL_DEPTH;
				case GraphicsAPI::eBufferType::DEPTH_STENCIL:
					return GL_DEPTH_STENCIL;
				default:
					NEVER_HAPPEN;
				}
			}

			inline extern unsigned int GetGLBufferMode(const GraphicsAPI::eBufferMode bufferMode)
			{
				switch (bufferMode)
				{
				case GraphicsAPI::FRONT_LEFT:
					return GL_FRONT_LEFT;
				case GraphicsAPI::FRONT_RIGHT: 
					return GL_FRONT_RIGHT;
				case GraphicsAPI::BACK_LEFT: 
					return GL_BACK_LEFT;
				case GraphicsAPI::BACK_RIGHT: 
					return GL_BACK_RIGHT;
				case GraphicsAPI::FRONT: 
					return GL_FRONT;
				case GraphicsAPI::BACK: 
					return GL_BACK;
				case GraphicsAPI::LEFT: 
					return GL_LEFT;
				case GraphicsAPI::RIGHT: 
					return GL_RIGHT;
				case GraphicsAPI::COLOR_ATTACHMENT0: 
					return GL_COLOR_ATTACHMENT0;
				case GraphicsAPI::COLOR_ATTACHMENT1:
					return GL_COLOR_ATTACHMENT1;
				case GraphicsAPI::COLOR_ATTACHMENT2:
					return GL_COLOR_ATTACHMENT2;
				case GraphicsAPI::COLOR_ATTACHMENT3: 
					return GL_COLOR_ATTACHMENT3;
				case GraphicsAPI::COLOR_ATTACHMENT4: 
					return GL_COLOR_ATTACHMENT4;
				case GraphicsAPI::COLOR_ATTACHMENT5: 
					return GL_COLOR_ATTACHMENT5;
				case GraphicsAPI::COLOR_ATTACHMENT6: 
					return GL_COLOR_ATTACHMENT6;
				case GraphicsAPI::COLOR_ATTACHMENT7: 
					return GL_COLOR_ATTACHMENT7;
				case GraphicsAPI::COLOR_ATTACHMENT8: 
					return GL_COLOR_ATTACHMENT8;
				case GraphicsAPI::COLOR_ATTACHMENT9: 
					return GL_COLOR_ATTACHMENT9;
				case GraphicsAPI::COLOR_ATTACHMENT10: 
					return GL_COLOR_ATTACHMENT10;
				default:
					NEVER_HAPPEN;
				}
			}

			inline extern unsigned int GetGLShaderType(const GraphicsAPI::eShaderType shaderType)
			{
				switch (shaderType)
				{
				case GraphicsAPI::Vertex:
					return GL_VERTEX_SHADER;
				case GraphicsAPI::Fragment: 
					return GL_FRAGMENT_SHADER;
				case GraphicsAPI::Geometry:
					return GL_GEOMETRY_SHADER;

				default:
					NEVER_HAPPEN;
				}
			}

			inline extern unsigned int GetTextureBindTarget(const GraphicsAPI::eTextureBindTarget textureBindTarget)
			{
				switch (textureBindTarget)
				{
				case GraphicsAPI::TEXTURE_1D:
					return GL_TEXTURE_1D;
				case GraphicsAPI::TEXTURE_2D: 
					return GL_TEXTURE_2D;
				case GraphicsAPI::TEXTURE_3D: 
					return GL_TEXTURE_3D;
				case GraphicsAPI::TEXTURE_1D_ARRAY:
					return GL_TEXTURE_1D_ARRAY;
				case GraphicsAPI::TEXTURE_2D_ARRAY: 
					return GL_TEXTURE_2D_ARRAY;
				case GraphicsAPI::TEXTURE_RECTANGLE:
					return GL_TEXTURE_RECTANGLE;
				case GraphicsAPI::TEXTURE_CUBE_MAP: 
					return GL_TEXTURE_CUBE_MAP;
				case GraphicsAPI::TEXTURE_CUBE_MAP_ARRAY: 
					return GL_TEXTURE_CUBE_MAP_ARRAY;
				case GraphicsAPI::_TEXTURE_BUFFER: 
					return GL_TEXTURE_BUFFER;
				case GraphicsAPI::TEXTURE_2D_MULTISAMPLE:
					return GL_TEXTURE_2D_MULTISAMPLE;
				case GraphicsAPI::TEXTURE_2D_MULTISAMPLE_ARRAY: 
					return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
				default:
					NEVER_HAPPEN;

				}
			}

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

void dooms::graphics::GraphicsAPI::SetGraphicsAPIType(const eGraphicsAPIType graphicsAPIType)
{
	mGraphicsAPIType = graphicsAPIType;
}

dooms::graphics::eGraphicsAPIType dooms::graphics::GraphicsAPI::GetGraphicsAPIType()
{
	return mGraphicsAPIType;
}

unsigned int dooms::graphics::GraphicsAPI::Initialize()
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
		assert(0); // "Failed to create GLFW window"
		glfwTerminate();
		return 1;
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
		assert(0); // Failed to initialize GLAD
		return 1;
	}

#ifdef _DEBUG
	std::string vendor{ reinterpret_cast<const char*>(glGetString(static_cast<const unsigned int>(dooms::graphics::opengl::GetStringParameter::VENDOR))) };
	if (vendor.find("ATI") != std::string::npos)
	{
		std::printf("Using AMD on board GPU, Maybe This will make driver error");
		assert(0);
		return 1;
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

	return 0;
}

unsigned int dooms::graphics::GraphicsAPI::DeInitialize()
{
	if (dooms::graphics::opengl::glfwWindow != nullptr)
	{
		glfwDestroyWindow(dooms::graphics::opengl::glfwWindow);
	}
	glfwTerminate();
	return 0;
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

void dooms::graphics::GraphicsAPI::WriteBuffer(const GraphicsAPI::eBufferMode bufferMode)
{
	glDrawBuffer(opengl::GetGLBufferMode(bufferMode));
}

void dooms::graphics::GraphicsAPI::WriteBuffers
(
	const unsigned count,
	const std::vector<GraphicsAPI::eBufferMode> bufferModes
)
{
	std::vector<unsigned int> glBufferModes;
	glBufferModes.resize(bufferModes.size());
	for(unsigned int i = 0 ; i < bufferModes.size() ; i++)
	{
		glBufferModes[i] = opengl::GetGLBufferMode(bufferModes[i]);
	}
	glDrawBuffers(count, glBufferModes.data());
}

void dooms::graphics::GraphicsAPI::ReadBuffer(const GraphicsAPI::eBufferMode bufferMode)
{
	glReadBuffer(opengl::GetGLBufferMode(bufferMode));
}

void dooms::graphics::GraphicsAPI::ClearColor(const float r, const float g, const float b, const float a)
{
	glClearColor(r, g, b, a);
}

void dooms::graphics::GraphicsAPI::ClearColor(const float* const color)
{
	glClearColor(color[0], color[1], color[2], color[3]);
}

void dooms::graphics::GraphicsAPI::ClearBuffer(const unsigned clearMaskBits)
{
	glClear(opengl::GetGLBufferBitType(clearMaskBits));
}

void dooms::graphics::GraphicsAPI::ClearBuffer(const eBufferBitType clearMask)
{
	glClear(opengl::GetGLBufferBitType(clearMask));
}

void dooms::graphics::GraphicsAPI::ClearBuffer(const eBufferBitType clearMask1, const eBufferBitType clearMask2)
{
	glClear(opengl::GetGLBufferBitType(clearMask1) | opengl::GetGLBufferBitType(clearMask2));
}

void dooms::graphics::GraphicsAPI::ClearBuffer(const eBufferBitType clearMask1, const eBufferBitType clearMask2, const eBufferBitType clearMask3)
{
	glClear(opengl::GetGLBufferBitType(clearMask1) | opengl::GetGLBufferBitType(clearMask2) | opengl::GetGLBufferBitType(clearMask3));
}

void dooms::graphics::GraphicsAPI::ClearSpecificBuffer
(
	const eBufferType bufferType, 
	const unsigned drawBufferIndex,
	const float r, const float g, const float b, const float a
)
{
	const std::vector<float> colors{ r, g, b, a };
	ClearSpecificBuffer(bufferType, drawBufferIndex, colors.data());
}

void dooms::graphics::GraphicsAPI::ClearSpecificBuffer
(
	const eBufferType bufferType, 
	const unsigned int drawBufferIndex,
	const float* const colors
)
{
	glClearBufferfv(opengl::GetGLBufferType(bufferType), drawBufferIndex, colors);
}

std::vector<unsigned int>  dooms::graphics::GraphicsAPI::GenerateBuffer(const unsigned int count)
{
	assert(count > 0);

	std::vector<unsigned int> renderBufferObject;
	renderBufferObject.resize(count);

	glGenBuffers(1, renderBufferObject.data());
	return renderBufferObject;
}

void dooms::graphics::GraphicsAPI::DestroyBuffer(const unsigned bufferID)
{
	glDeleteBuffers(1, &bufferID);
}

std::vector<unsigned int> dooms::graphics::GraphicsAPI::CreateBuffers(const unsigned bufferCount)
{
	std::vector<unsigned int> bufferObject;
	bufferObject.resize(bufferCount);

	glGenVertexArrays(bufferCount, bufferObject.data());
	return bufferObject;
}

void dooms::graphics::GraphicsAPI::DestroyBuffers(const std::vector<unsigned>& buffers)
{
	glDeleteBuffers(buffers.size(), buffers.data());
}

std::vector<unsigned int> dooms::graphics::GraphicsAPI::CreateVertexArrayObject(const unsigned int count)
{
	assert(count > 0);

	std::vector<unsigned int> bufferObject;
	bufferObject.resize(count);

	glGenVertexArrays(count, bufferObject.data());
	return bufferObject;
}

void dooms::graphics::GraphicsAPI::DestroyVertexArrayObject(const std::vector<unsigned>& vertexArrayObjects)
{
	glDeleteVertexArrays(vertexArrayObjects.size(), vertexArrayObjects.data());
}

void dooms::graphics::GraphicsAPI::BindVertexArrayObject(const unsigned vertexArrayObject)
{
	glBindVertexArray(vertexArrayObject);
}

void dooms::graphics::GraphicsAPI::UnBindVertexArrayObject()
{
	glBindVertexArray(0);
}

void dooms::graphics::GraphicsAPI::AllocateBufferMemory
(
	const eBufferTarget bufferTarget, 
	const unsigned int bufferSize,
	const void* const initialData
)
{
	glBufferData(opengl::GetGLBufferTarget(bufferTarget), bufferSize, initialData, GL_STATIC_DRAW);
}

void dooms::graphics::GraphicsAPI::EnableVertexAttributeArrayIndex(const unsigned vertexAttributeIndex)
{
	glEnableVertexAttribArray(vertexAttributeIndex);
}

void dooms::graphics::GraphicsAPI::DefineVertexAttributeLayout
(
	const unsigned vertexAttributeIndex,
	const unsigned componentNumber, 
	const unsigned stride, 
	const unsigned offset
)
{
	glVertexAttribPointer(vertexAttributeIndex, componentNumber, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
}

void dooms::graphics::GraphicsAPI::BindBuffer
(
	const unsigned int bufferObject, 
	const eBufferTarget bindBufferTarget
)
{
	glBindBuffer(opengl::GetGLBufferTarget(bindBufferTarget), bufferObject);
}

void dooms::graphics::GraphicsAPI::UnBindBuffer(const eBufferTarget bindBufferTarget)
{
	glBindBuffer(opengl::GetGLBufferTarget(bindBufferTarget), 0);
}

void dooms::graphics::GraphicsAPI::BindBufferToIndexedBuffer
(
	const eBufferTarget bindBufferTarget,
	const unsigned bindingPoint,
	const unsigned bufferObject
)
{
	glBindBufferBase(opengl::GetGLBufferTarget(bindBufferTarget), bindingPoint, bufferObject);
}

void dooms::graphics::GraphicsAPI::UpdateDataToBuffer
(
	const eBufferTarget bindBufferTarget,
	const unsigned offset, 
	const unsigned dataSize, 
	const void* const data
)
{
	glBufferSubData(opengl::GetGLBufferTarget(bindBufferTarget), offset, dataSize, data);
}

void dooms::graphics::GraphicsAPI::BindFrameBuffer
(
	const unsigned frameBufferObject,
	const eBindFrameBufferTarget bindFrameBufferTarget
)
{
	switch (bindFrameBufferTarget)
	{

		case DRAW_FRAMEBUFFER:
			glBindBuffer(GL_DRAW_FRAMEBUFFER, frameBufferObject);
			break;

		case READ_FRAMEBUFFER:
			glBindBuffer(GL_READ_FRAMEBUFFER, frameBufferObject);
			break;

		case FRAMEBUFFER:
			glBindBuffer(GL_FRAMEBUFFER, frameBufferObject);
			break;

		default:
			NEVER_HAPPEN;
			
			
	}
}

void dooms::graphics::GraphicsAPI::BindRenderBuffer(const unsigned renderBufferObject)
{
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
}

std::vector<unsigned int> dooms::graphics::GraphicsAPI::CreateRenderBufferObject(const unsigned int renderBufferCount)
{
	assert(renderBufferCount > 0);

	std::vector<unsigned int> renderBufferObject;
	renderBufferObject.resize(renderBufferCount);

	glGenRenderbuffers(1, renderBufferObject.data());
	return renderBufferObject;
}

void dooms::graphics::GraphicsAPI::AllocateRenderBufferMemory
(
	const unsigned renderBufferObject,
	const eTextureInternalFormat textureInternalFormat,
	const unsigned width, const unsigned height,
	const unsigned int multiSample
)
{
	if(multiSample == 0)
	{
		glRenderbufferStorage(GL_RENDERBUFFER, opengl::GetGLTextureInternalFormat(eTextureInternalFormat::RGBA16F), width, height);
	}
	else
	{
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, multiSample, opengl::GetGLTextureInternalFormat(eTextureInternalFormat::RGBA16F), width, height);
	}

}

void dooms::graphics::GraphicsAPI::AttachRenderBufferToFrameBuffer
(
	const unsigned renderBufferObject,
	const unsigned frameBufferObject, 
	const eBufferAttachmentType bufferType
)
{
	BindRenderBuffer(renderBufferObject);

	switch (bufferType)
	{

	case ATTACHMENT_COLOR0:
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBufferObject);
		break;

	case ATTACHMENT_COLOR1:
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, renderBufferObject);
		break;

	case ATTACHMENT_COLOR2:
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_RENDERBUFFER, renderBufferObject);
		break;

	case ATTACHMENT_COLOR3:
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_RENDERBUFFER, renderBufferObject);
		break;

	case ATTACHMENT_DEPTH:
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);
		break;

	case ATTACHMENT_DEPTH_STENCIL:
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);
		break;

	default:
		NEVER_HAPPEN;

	}
}



void dooms::graphics::GraphicsAPI::Draw
(
	const ePrimitiveType primitiveType, 
	const unsigned vertexCount,
	const unsigned int startVertexLocation
)
{
	switch (primitiveType)
	{
	case POINTS:
		glDrawArrays(GL_POINTS, startVertexLocation, vertexCount);
		break;

	case LINES:
		glDrawArrays(GL_LINES, startVertexLocation, vertexCount);
		break;

	case TRIANGLES:
		glDrawArrays(GL_TRIANGLES, startVertexLocation, vertexCount);
		break;

	default:
		NEVER_HAPPEN;
	}

	
}


void dooms::graphics::GraphicsAPI::DrawIndexed
(
	const ePrimitiveType primitiveType, 
	const unsigned indiceCount,
	const void* const indices
)
{
	switch (primitiveType)
	{
	case POINTS:
		glDrawElements(GL_POINTS, indiceCount, GL_UNSIGNED_INT, indices);
		break;

	case LINES:
		glDrawElements(GL_LINES, indiceCount, GL_UNSIGNED_INT, indices);
		break;

	case TRIANGLES:
		glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, indices);
		break;

	default:
		NEVER_HAPPEN;
	}
}

unsigned dooms::graphics::GraphicsAPI::CreateMaterial()
{
	unsigned int materialObject = glCreateProgram();
	assert(materialObject != 0);
	return materialObject;
}

void dooms::graphics::GraphicsAPI::DestroyMaterial(const unsigned materialObject)
{
	glDeleteProgram(materialObject);
}

bool dooms::graphics::GraphicsAPI::LinkMaterial(const unsigned materialObject)
{
	glLinkProgram(materialObject);

	int isSuccess = 0;
	glGetProgramiv(materialObject, GL_LINK_STATUS, &isSuccess);
#ifdef _DEBUG
	if (isSuccess == 0)
	{
		char infoLog[512];
		glGetProgramInfoLog(materialObject, 512, NULL, infoLog);
		std::printf("SHADER::PROGRAM::LINKING_FAILED ( Material ID : %d ) : ( %s ) ", materialObject, infoLog);
	}
#endif

	return isSuccess != 0;
}

void dooms::graphics::GraphicsAPI::BindMaterial(const unsigned materialObject)
{
	glUseProgram(materialObject);
}

unsigned dooms::graphics::GraphicsAPI::CreateShaderObject(const eShaderType shaderType)
{
	assert(shaderType != eShaderType::ShaderType_None);

	unsigned int shaderObject = glCreateShader(opengl::GetGLShaderType(shaderType));
	assert(shaderObject != 0);
	return shaderObject;
}

void dooms::graphics::GraphicsAPI::DestroyShaderObject(const unsigned shaderObject)
{
	glDeleteShader(shaderObject);
}

void dooms::graphics::GraphicsAPI::CompileShaders
(
	const unsigned shaderObject, 
	const unsigned int shaderCount,
	const char* const* const shaderTexts
)
{
	glShaderSource(shaderObject, shaderCount, shaderTexts, NULL);
	glCompileShader(shaderObject);
}

void dooms::graphics::GraphicsAPI::AttachShaderToMaterial(const unsigned materialObject, const unsigned shaderObject)
{
	glAttachShader(materialObject, shaderObject);
}



void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_bool1
(
	const int constantBufferID, 
	const bool value1
)
{
	glUniform1i(constantBufferID, static_cast<int>(value1));
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_bool2
(
	const int constantBufferID, 
	const bool value1,
	const bool value2
)
{
	glUniform2i(constantBufferID, static_cast<int>(value1), static_cast<int>(value2));
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_bool3
(
	const int constantBufferID, 
	const bool value1,
	const bool value2, 
	const bool value3
)
{
	glUniform3i(constantBufferID, static_cast<int>(value1), static_cast<int>(value2), static_cast<int>(value3));
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_bool4
(
	const int constantBufferID, 
	const bool value1,
	const bool value2, 
	const bool value3, 
	const bool value4
)
{
	glUniform4i(constantBufferID, static_cast<int>(value1), static_cast<int>(value2), static_cast<int>(value3), static_cast<int>(value4));
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_int1
(
	const int constantBufferID, 
	const int value1
)
{
	glUniform1i(constantBufferID, value1);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_int2
(
	const int constantBufferID, 
	const int value1,
	const int value2
)
{
	glUniform2i(constantBufferID, value1, value2);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_int3
(
	const int constantBufferID, 
	const int value1,
	const int value2, 
	const int value3
)
{
	glUniform3i(constantBufferID, value1, value2, value3);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_int4
(
	const int constantBufferID, 
	const int value1,
	const int value2, 
	const int value3, 
	const int value4
)
{
	glUniform4i(constantBufferID, value1, value2, value3, value4);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_float1
(
	const int constantBufferID,
	const float value1
)
{
	glUniform1f(constantBufferID, value1);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_float2
(
	const int constantBufferID,
	const float value1,
	const float value2
)
{
	glUniform2f(constantBufferID, value1, value2);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_float3
(
	const int constantBufferID,
	const float value1,
	const float value2, 
	const float value3
)
{
	glUniform3f(constantBufferID, value1, value2, value3);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_float4
(
	const int constantBufferID,
	const float value1,
	const float value2, 
	const float value3, 
	const float value4
)
{
	glUniform4f(constantBufferID, value1, value2, value3, value4);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_mat2x2f(const int constantBufferID, const float* const matrix)
{
	glUniformMatrix2fv(constantBufferID, 1, GL_FALSE, matrix);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_mat3x3f(const int constantBufferID, const float* const matrix)
{
	glUniformMatrix3fv(constantBufferID, 1, GL_FALSE, matrix);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_mat4x4f(const int constantBufferID, const float* const matrix)
{
	glUniformMatrix3fv(constantBufferID, 1, GL_FALSE, matrix);
}

void dooms::graphics::GraphicsAPI::CompileShader
(
	const unsigned shaderObject, 
	const char* const shaderText
)
{
	glShaderSource(shaderObject, 1, &shaderText, NULL);
	glCompileShader(shaderObject);
}

