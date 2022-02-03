#pragma once

#include "Macros/GraphicsAPIMacros.h"

#include <cassert>

namespace dooms
{
	namespace graphics
	{
		// DirectX / OpenGL(Vulkan) concepts mapping chart
		// https://computergraphics.stackexchange.com/questions/4422/directx-openglvulkan-concepts-mapping-chart/4432
		// https://anteru.net/blog/2013/porting-from-directx11-to-opengl-4-2-api-mapping/



		class GraphicsAPIInput;
		namespace GraphicsAPI
		{

			inline extern double DEFAULT_MAX_DEPTH_VALUE = 1.0;

			enum class eGraphicsAPIType
			{
				GraphicsAPIType_NONE,
				OpenGL,
				DX11_10
			};

			typedef eGraphicsAPIType(DOOMS_ENGINE_API_ENTRY_P GRAPHICS_FLUSH_CMD_QUEUE)(void);
			extern GRAPHICS_FLUSH_CMD_QUEUE FlushCMDQueue;

			/**
			 * \brief TODO : Make inlined version function of this function for performance
			 */
			typedef eGraphicsAPIType(DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GETCURRENTAPITYPE)(void);
			extern GRAPHICS_GETCURRENTAPITYPE _GetCurrentAPIType;

			enum eGraphisAPIDebugCallbackSeverity : unsigned int
			{
				HIGH,
				MEDIUM,
				LOW,
				NOTIFICATION
			};

			using DEBUG_FUNCTION = void (*)(const char* const debugMessage, const eGraphisAPIDebugCallbackSeverity debugCallbackSeverity);

			// Function pointers isn't used from graphis api dll.
			// In main application, extern is just extern.
			// This is just for easy development

			typedef DEBUG_FUNCTION(DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GETDEBUGFUNCTION)(void);
			extern GRAPHICS_GETDEBUGFUNCTION GetDebugFunction;

			typedef unsigned int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GETDRAWCALL)(void);
			extern GRAPHICS_GETDRAWCALL GetDrawCall;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETDEBUGFUNCTION)(DEBUG_FUNCTION debugFunction);
			extern GRAPHICS_SETDEBUGFUNCTION SetDebugFunction;

			typedef const char* (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GETPLATFORMVERSION)(void);
			extern GRAPHICS_GETPLATFORMVERSION GetPlatformVersion;

			typedef void* (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GETPLATFORMWINDOW)(void);
			extern GRAPHICS_GETPLATFORMWINDOW GetPlatformWindow;

			enum eBufferBitType : unsigned int
			{
				COLOR_BUFFER = 1, // = GL_COLOR_BUFFER_BIT,
				DEPTH_BUFFER = 1 << 1, // = GL_DEPTH_BUFFER_BIT,
				STENCIL_BUFFER = 1 << 2, // = GL_DEPTH_BUFFER_BIT,
				DEPTH_STENCIL_BUFFER = 1 << 3 // = GL_STENCIL_BUFFER_BIT
			};

			enum eBufferType : unsigned int
			{
				COLOR, // = GL_COLOR_BUFFER_BIT,
				DEPTH, // = GL_DEPTH_BUFFER_BIT,
				DEPTH_STENCIL // = GL_STENCIL_BUFFER_BIT
			};

			enum eBufferMode : unsigned int
			{
				BUFFER_MODE_NONE,
				FRONT_LEFT, // = GL_FRONT_LEFT,
				FRONT_RIGHT, // = GL_FRONT_RIGHT,
				BACK_LEFT, // = GL_BACK_LEFT,
				BACK_RIGHT, // = GL_BACK_RIGHT,
				FRONT, // = GL_FRONT,
				BACK, // = GL_BACK,
				LEFT, // = GL_LEFT,
				RIGHT, // = GL_RIGHT,
				COLOR_ATTACHMENT0, // = GL_COLOR_ATTACHMENT0,
				COLOR_ATTACHMENT1, // = GL_COLOR_ATTACHMENT1,
				COLOR_ATTACHMENT2, // = GL_COLOR_ATTACHMENT2,
				COLOR_ATTACHMENT3, // = GL_COLOR_ATTACHMENT3,
				COLOR_ATTACHMENT4, // = GL_COLOR_ATTACHMENT4,
				COLOR_ATTACHMENT5, // = GL_COLOR_ATTACHMENT5,
				COLOR_ATTACHMENT6, // = GL_COLOR_ATTACHMENT6,
				COLOR_ATTACHMENT7, // = GL_COLOR_ATTACHMENT7,
				COLOR_ATTACHMENT8, // = GL_COLOR_ATTACHMENT8,
				COLOR_ATTACHMENT9, // = GL_COLOR_ATTACHMENT9,
				COLOR_ATTACHMENT10, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT11, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT12, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT13, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT14, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT15, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT16, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT17, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT18, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT19, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT20, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT21, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT22, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT23, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT24, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT25, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT26, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT27, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT28, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT29, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT30, // = GL_COLOR_ATTACHMENT10,
				COLOR_ATTACHMENT31, // = GL_COLOR_ATTACHMENT10,
			};
			
			enum ePrimitiveType : unsigned int
			{
				NONE = 0, // Never change underlying value. It's used as indef of jump table
				POINTS = 1, //= GL_POINTS,
				//LINE_STRIP = GL_LINE_STRIP,
				//LINE_LOOP = GL_LINE_LOOP,
				LINES = 2, //= GL_LINES,
				//LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
				//LINES_ADJACENCY = GL_LINES_ADJACENCY,
				//TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
				//TRIANGLE_FAN = GL_TRIANGLE_FAN,
				TRIANGLES = 3, //= GL_TRIANGLES,
				//TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
				//TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
				//PATCHES = GL_PATCHES,

				END,
			};

			enum eBufferTarget : unsigned int
			{
				ARRAY_BUFFER,
				ELEMENT_ARRAY_BUFFER,
				DRAW_INDIRECT_BUFFER,
				TEXTURE_BUFFER,
				UNIFORM_BUFFER,
			};

			typedef unsigned int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_INITIALIZEGRAPHICSAPI)(const int screenWidth, const int screenHeight, const unsigned int multiSamplingNum);
			extern GRAPHICS_INITIALIZEGRAPHICSAPI InitializeGraphicsAPI;

			typedef unsigned int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_DEINITIALIZEGRAPHICSAPI)();
			extern GRAPHICS_DEINITIALIZEGRAPHICSAPI DeinitializeGraphicsAPI;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SWAPBUFFER)(void);
			extern GRAPHICS_SWAPBUFFER SwapBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETVSYNC)(const bool isEnabled);
			extern GRAPHICS_SETVSYNC SetVSync;

			enum eTestFuncType : unsigned int
			{
				ALWAYS, // = GL_ALWAYS,
				NEVER, // = GL_NEVER,
				LESS, // = GL_LESS,
				EQUAL, // = GL_EQUAL,
				LEQUAL, // = GL_LEQUAL,
				GREATER, // = GL_GREATER,
				NOTEQUAL, // = GL_NOTEQUAL,
				GEQUAL // = GL_GEQUAL
			};

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETISDEPTHTESTENABLED)(const bool isEnabled);
			extern GRAPHICS_SETISDEPTHTESTENABLED SetIsDepthTestEnabled;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETISSTENCILTESTENABLED)(const bool isEnabled);
			extern GRAPHICS_SETISSTENCILTESTENABLED SetIsStencilTestEnabled;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETISSTENCILFUNC)(const eTestFuncType testFuncType, const int ref, const unsigned int mask);
			extern GRAPHICS_SETISSTENCILFUNC SetIsStencilFunc;

			enum eStencilOption : unsigned int
			{
				KEEP,
				STENCIL_OPTION_ZERO,
				REPLACE,
				INCR,
				INCR_WRAP,
				DECR,
				DECR_WRAP,
				INVERT
			};

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETISSTENCILOP)(const eStencilOption stencilFailOption, const eStencilOption actionWhenStencilTestPassAnd_DepthTestFail, const eStencilOption actionWhenStencilTestPassAnd_DepthTestPass);
			extern GRAPHICS_SETISSTENCILOP SetIsStencilOp;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETDEPTHFUNC)(const eTestFuncType depthFuncType);
			extern GRAPHICS_SETDEPTHFUNC SetDepthFunc;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETDEPTHMASK)(const bool isWriteDepthBuffer);
			extern GRAPHICS_SETDEPTHMASK SetDepthMask;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETISALPHATESTENABLED)(const bool isEnabled);
			extern GRAPHICS_SETISALPHATESTENABLED SetIsAlphaTestEnabled;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETISBLENDENABLED)(const bool isEnabled);
			extern GRAPHICS_SETISBLENDENABLED SetIsBlendEnabled;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETVIEWPORT)(const unsigned int index, const int startX, const int startY, const unsigned int width, const unsigned int height);
			extern GRAPHICS_SETVIEWPORT SetViewport;

			typedef bool(DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GETVIEWPORT)(const unsigned int index, int* const startX, int* const startY, int* const width, int* const height);
			extern GRAPHICS_GETVIEWPORT GetViewPort;

			enum eBlendFactor : unsigned int
			{
				ZERO,
				ONE,
				SRC_COLOR,
				ONE_MINUS_SRC_COLOR,
				DST_COLOR,
				ONE_MINUS_DST_COLOR,
				SRC_ALPHA,
				ONE_MINUS_SRC_ALPHA,
				DST_ALPHA,
				ONE_MINUS_DST_ALPHA,
				CONSTANT_COLOR,
				ONE_MINUS_CONSTANT_COLOR,
				CONSTANT_ALPHA,
				ONE_MINUS_CONSTANT_ALPHA
			};
			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETBLENDFACTOR)(const eBlendFactor sourceBlendFactor, const eBlendFactor destinationBlendFactor);
			extern GRAPHICS_SETBLENDFACTOR SetBlendFactor;

			enum eCullFace : unsigned int
			{
				CULLFACE_FRONT,
				CULLFACE_BACK,
				CULLFACE_FRONT_AND_BACK
			};

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETCULLFACE)(const eCullFace cullFace);
			extern GRAPHICS_SETCULLFACE SetCullFace;

			enum eWinding : unsigned int
			{
				CW,
				CCW
			};

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETFRONTFACEWINDING)(const eWinding winding);
			extern GRAPHICS_SETFRONTFACEWINDING SetFrontFaceWinding;

			/*
			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETDRAWBUFFER)(const GraphicsAPI::eBufferMode bufferMode);
			extern GRAPHICS_SETDRAWBUFFER SetDrawBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETDRAWBUFFERS)(const unsigned int count, const GraphicsAPI::eBufferMode* bufferModes);
			extern GRAPHICS_SETDRAWBUFFERS SetDrawBuffers;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETREADBUFFER)(const GraphicsAPI::eBufferMode bufferMode);
			extern GRAPHICS_SETREADBUFFER SetReadBuffer;
			*/

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CLEARBACKFRAMEBUFFERCOLORBUFFER)(const float r, const float g, const float b, const float a);
			extern GRAPHICS_CLEARBACKFRAMEBUFFERCOLORBUFFER ClearBackFrameBufferColorBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CLEARBACKFRAMEBUFFERDEPTHBUFFER)(const double depthValue);
			extern GRAPHICS_CLEARBACKFRAMEBUFFERDEPTHBUFFER ClearBackFrameBufferDepthBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CLEARBACKFRAMEBUFFERSTENCILBUFFER)(const int stencilValue);
			extern GRAPHICS_CLEARBACKFRAMEBUFFERSTENCILBUFFER ClearBackFrameBufferStencilBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CLEARBACKFRAMEBUFFERDEPTHSTENCILBUFFER)(const double depthValue, const int stencilValue);
			extern GRAPHICS_CLEARBACKFRAMEBUFFERDEPTHSTENCILBUFFER ClearBackFrameBufferDepthStencilBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CLEARFRAMEBUFFERCOLORBUFFER)(unsigned long long bufferObject, const unsigned int colorTextureIndex, const float r, const float g, const float b, const float a);
			extern GRAPHICS_CLEARFRAMEBUFFERCOLORBUFFER ClearFrameBufferColorBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CLEARFRAMEBUFFERDEPTHBUFFER)(unsigned long long bufferObject, const double depthValue);
			extern GRAPHICS_CLEARFRAMEBUFFERDEPTHBUFFER ClearFrameBufferDepthBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CLEARFRAMEBUFFERSTENCILBUFFER)(unsigned long long bufferObject, const double depthValue);
			extern GRAPHICS_CLEARFRAMEBUFFERSTENCILBUFFER ClearFrameBufferStencilBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CLEARFRAMEBUFFERDEPTHSTENCILBUFFER)(unsigned long long bufferObject, const double depthValue, const int stencilValue);
			extern GRAPHICS_CLEARFRAMEBUFFERDEPTHSTENCILBUFFER ClearFrameBufferDepthStencilBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CLEARSPECIFICBUFFER)(const eBufferType bufferType, const unsigned int drawBufferIndex, const float r, const float g, const float b, const float a);
			extern GRAPHICS_CLEARSPECIFICBUFFER ClearSpecificBuffer;

			/*
			enum eTextureType : unsigned int
			{
				TextureType_NONE, // = 0,
				DIFFUSE, // = 1,
				SPECULAR, // = 2,
				AMBIENT, // = 3,
				EMISSIVE, // = 4,
				HEIGHT, // = 5,
				NORMALS, // = 6,
				SHININESS, // = 7,
				OPACITY, // = 8,
				DISPLACEMENT, // = 9,
				LIGHTMAP, // = 10,
				REFLECTION, // = 11,
				BASE_COLOR, // = 12,
				NORMAL_CAMERA, // = 13,
				EMISSION_COLOR, // = 14,
				METALNESS, // = 15,
				DIFFUSE_ROUGHNESS, // = 16,
				AMBIENT_OCCLUSION, // = 17,
				UNKNOWN //= 18,
			};
			*/

			enum eTextureBindTarget : unsigned int
			{
				TextureBindTarget_NONE, // = 0,
				TEXTURE_1D, // = GL_TEXTURE_1D,
				TEXTURE_2D, // = GL_TEXTURE_2D,
				TEXTURE_3D, // = GL_TEXTURE_3D,
				TEXTURE_1D_ARRAY, // = GL_TEXTURE_1D_ARRAY,
				TEXTURE_2D_ARRAY, // = GL_TEXTURE_2D_ARRAY,
				TEXTURE_RECTANGLE, // = GL_TEXTURE_RECTANGLE,
				TEXTURE_CUBE_MAP, // = GL_TEXTURE_CUBE_MAP,
				_TEXTURE_BUFFER, // = ,
				TEXTURE_CUBE_MAP_ARRAY, // = GL_TEXTURE_CUBE_MAP_ARRAY,
				TEXTURE_2D_MULTISAMPLE, // = GL_TEXTURE_2D_MULTISAMPLE,
				TEXTURE_2D_MULTISAMPLE_ARRAY, // = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
			};

			enum eTargetTexture : unsigned int
			{
				TARGET_TEXTURE_TEXTURE_1D, //= GL_TEXTURE_1D,
				TARGET_TEXTURE_PROXY_TEXTURE_1D, // = GL_PROXY_TEXTURE_1D,
				TARGET_TEXTURE_TEXTURE_2D, // = GL_TEXTURE_2D,
				TARGET_TEXTURE_PROXY_TEXTURE_2D, // = GL_PROXY_TEXTURE_2D,
				TARGET_TEXTURE_TEXTURE_1D_ARRAY, // = GL_TEXTURE_1D_ARRAY,
				TARGET_TEXTURE_PROXY_TEXTURE_1D_ARRAY, // = GL_PROXY_TEXTURE_1D_ARRAY,
				TARGET_TEXTURE_TEXTURE_RECTANGLE, // = GL_TEXTURE_RECTANGLE,
				TARGET_TEXTURE_PROXY_TEXTURE_RECTANGLE, // = GL_PROXY_TEXTURE_RECTANGLE,
				TARGET_TEXTURE_TEXTURE_CUBE_MAP_POSITIVE_X, // = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				TARGET_TEXTURE_TEXTURE_CUBE_MAP_NEGATIVE_X, // = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
				TARGET_TEXTURE_TEXTURE_CUBE_MAP_POSITIVE_Y, // = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
				TARGET_TEXTURE_TEXTURE_CUBE_MAP_NEGATIVE_Y, // = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
				TARGET_TEXTURE_TEXTURE_CUBE_MAP_POSITIVE_Z, // = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
				TARGET_TEXTURE_TEXTURE_CUBE_MAP_NEGATIVE_Z, // = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
				TARGET_TEXTURE_PROXY_TEXTURE_CUBE_MAP, // = GL_PROXY_TEXTURE_CUBE_MAP,
				TARGET_TEXTURE_TEXTURE_3D // = GL_TEXTURE_3D
			};


			enum eDataType : unsigned int
			{
				UNSIGNED_BYTE, // = GL_UNSIGNED_BYTE,
				BYTE, // = GL_BYTE,
				UNSIGNED_SHORT, // = GL_UNSIGNED_SHORT,
				SHORT, // = GL_SHORT,
				UNSIGNED_INT, // = GL_UNSIGNED_INT,
				INT, // = GL_INT,
				HALF_FLOAT, // = GL_HALF_FLOAT,
				FLOAT, // = GL_FLOAT,
				UNSIGNED_BYTE_3_3_2, // = GL_UNSIGNED_BYTE_3_3_2,
				UNSIGNED_BYTE_2_3_3_REV, // = GL_UNSIGNED_BYTE_2_3_3_REV,
				UNSIGNED_SHORT_5_6_5, // = GL_UNSIGNED_SHORT_5_6_5,
				UNSIGNED_SHORT_5_6_5_REV, // = GL_UNSIGNED_SHORT_5_6_5_REV,
				UNSIGNED_SHORT_4_4_4_4, // = GL_UNSIGNED_SHORT_4_4_4_4,
				UNSIGNED_SHORT_4_4_4_4_REV, // = GL_UNSIGNED_SHORT_4_4_4_4_REV,
				UNSIGNED_SHORT_5_5_5_1, // = GL_UNSIGNED_SHORT_5_5_5_1,
				UNSIGNED_SHORT_1_5_5_5_REV, // = GL_UNSIGNED_SHORT_1_5_5_5_REV,
				UNSIGNED_INT_8_8_8_8, // = GL_UNSIGNED_INT_8_8_8_8,
				UNSIGNED_INT_8_8_8_8_REV, // = GL_UNSIGNED_INT_8_8_8_8_REV,
				UNSIGNED_INT_10_10_10_2, // = GL_UNSIGNED_INT_10_10_10_2,
				UNSIGNED_INT_2_10_10_10_REV, // = GL_UNSIGNED_INT_2_10_10_10_REV,
				UNSIGNED_INT_24_8, // = GL_UNSIGNED_INT_24_8,
				FLOAT_32_UNSIGNED_INT_24_8_REV // = GL_FLOAT_32_UNSIGNED_INT_24_8_REV
			};

			enum eTextureComponentFormat : unsigned int
			{
				TEXTURE_COMPONENT_FORMAT_NONE, //0,
				TEXTURE_COMPONENT_RED, //GL_RED,
				TEXTURE_COMPONENT_RG, //GL_RG,
				TEXTURE_COMPONENT_RGB, //GL_RGB,
				TEXTURE_COMPONENT_BGR, //GL_BGR,
				TEXTURE_COMPONENT_RGBA, //GL_RGBA,
				TEXTURE_COMPONENT_BGRA, //GL_BGRA,
				TEXTURE_COMPONENT_RED_INTEGER, //GL_RED_INTEGER,
				TEXTURE_COMPONENT_RG_INTEGER, //GL_RG_INTEGER,
				TEXTURE_COMPONENT_RGB_INTEGER, //GL_RGB_INTEGER,
				TEXTURE_COMPONENT_BGR_INTEGER, //GL_BGR_INTEGER,
				TEXTURE_COMPONENT_RGBA_INTEGER, //GL_RGBA_INTEGER,
				TEXTURE_COMPONENT_BGRA_INTEGER, //GL_BGRA_INTEGER,
				TEXTURE_COMPONENT_STENCIL_INDEX, //GL_STENCIL_INDEX,
				TEXTURE_COMPONENT_DEPTH_COMPONENT, //GL_DEPTH_COMPONENT,
				TEXTURE_COMPONENT_DEPTH_STENCIL //GL_DEPTH_STENCIL
			};

			enum eTextureInternalFormat : unsigned int
			{
				TEXTURE_INTERNAL_FORMAT_NONE, //0,
				TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT16, //GL_DEPTH_COMPONENT16,
				TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT24, //GL_DEPTH_COMPONENT24,
				TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT32, //GL_DEPTH_COMPONENT32,
				TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT32F, //GL_DEPTH_COMPONENT32F,
				TEXTURE_INTERNAL_FORMAT_DEPTH24_STENCIL8, //GL_DEPTH24_STENCIL8,
				TEXTURE_INTERNAL_FORMAT_DEPTH32F_STENCIL8, //GL_DEPTH32F_STENCIL8,
				TEXTURE_INTERNAL_FORMAT_STENCIL_INDEX, //GL_STENCIL_INDEX,
				TEXTURE_INTERNAL_FORMAT_STENCIL_INDEX8, //GL_STENCIL_INDEX8,
				TEXTURE_INTERNAL_FORMAT_RED, //GL_RED,
				TEXTURE_INTERNAL_FORMAT_RG, //GL_RG,
				TEXTURE_INTERNAL_FORMAT_RGB, //GL_RGB,
				TEXTURE_INTERNAL_FORMAT_RGBA, //GL_RGBA,
				TEXTURE_INTERNAL_FORMAT_R8, //GL_R8,
				TEXTURE_INTERNAL_FORMAT_R8_SNORM, //GL_R8_SNORM,
				TEXTURE_INTERNAL_FORMAT_R16, //GL_R16,
				TEXTURE_INTERNAL_FORMAT_R16_SNORM, //GL_R16_SNORM,
				TEXTURE_INTERNAL_FORMAT_RG8, //GL_RG8,
				TEXTURE_INTERNAL_FORMAT_RG8_SNORM, //GL_RG8_SNORM,
				TEXTURE_INTERNAL_FORMAT_RG16, //GL_RG16,
				TEXTURE_INTERNAL_FORMAT_RG16_SNORM, //GL_RG16_SNORM,
				TEXTURE_INTERNAL_FORMAT_R3_G3_B2, //GL_R3_G3_B2,
				TEXTURE_INTERNAL_FORMAT_RGB4, //GL_RGB4,
				TEXTURE_INTERNAL_FORMAT_RGB5, //GL_RGB5,
				TEXTURE_INTERNAL_FORMAT_RGB8, //GL_RGB8,
				TEXTURE_INTERNAL_FORMAT_RGB8_SNORM, //GL_RGB8_SNORM,
				TEXTURE_INTERNAL_FORMAT_RGB10, //GL_RGB10,
				TEXTURE_INTERNAL_FORMAT_RGB12, //GL_RGB12,
				TEXTURE_INTERNAL_FORMAT_RGB16_SNORM, //GL_RGB16_SNORM,
				TEXTURE_INTERNAL_FORMAT_RGBA2, //GL_RGBA2,
				TEXTURE_INTERNAL_FORMAT_RGBA4, //GL_RGBA4,
				TEXTURE_INTERNAL_FORMAT_RGB5_A1, //GL_RGB5_A1,
				TEXTURE_INTERNAL_FORMAT_RGBA8, //GL_RGBA8,
				TEXTURE_INTERNAL_FORMAT_RGBA8_SNORM, //GL_RGBA8_SNORM,
				TEXTURE_INTERNAL_FORMAT_RGB10_A2, //GL_RGB10_A2,
				TEXTURE_INTERNAL_FORMAT_RGB10_A2UI, //GL_RGB10_A2UI,
				TEXTURE_INTERNAL_FORMAT_RGBA12, //GL_RGBA12,
				TEXTURE_INTERNAL_FORMAT_RGBA16, //GL_RGBA16,
				TEXTURE_INTERNAL_FORMAT_SRGB8, //GL_SRGB8,
				TEXTURE_INTERNAL_FORMAT_SRGB8_ALPHA8, //GL_SRGB8_ALPHA8,
				TEXTURE_INTERNAL_FORMAT_R16F, //GL_R16F,
				TEXTURE_INTERNAL_FORMAT_RG16F, //GL_RG16F,
				TEXTURE_INTERNAL_FORMAT_RGB16F, //GL_RGB16F,
				TEXTURE_INTERNAL_FORMAT_RGBA16F, //GL_RGBA16F,
				TEXTURE_INTERNAL_FORMAT_R32F, //GL_R32F,
				TEXTURE_INTERNAL_FORMAT_RG32F, //GL_RG32F,
				TEXTURE_INTERNAL_FORMAT_RGB32F, //GL_RGB32F,
				TEXTURE_INTERNAL_FORMAT_RGBA32F, //GL_RGBA32F,
				TEXTURE_INTERNAL_FORMAT_R11F_G11F_B10F, //GL_R11F_G11F_B10F,
				TEXTURE_INTERNAL_FORMAT_RGB9_E5, //GL_RGB9_E5,
				TEXTURE_INTERNAL_FORMAT_R8I, //GL_R8I,
				TEXTURE_INTERNAL_FORMAT_R8UI, //GL_R8UI,
				TEXTURE_INTERNAL_FORMAT_R16I, //GL_R16I,
				TEXTURE_INTERNAL_FORMAT_R16UI, //GL_R16UI,
				TEXTURE_INTERNAL_FORMAT_R32I, //GL_R32I,
				TEXTURE_INTERNAL_FORMAT_R32UI, //GL_R32UI,
				TEXTURE_INTERNAL_FORMAT_RG8I, //GL_RG8I,
				TEXTURE_INTERNAL_FORMAT_RG8UI, //GL_RG8UI,
				TEXTURE_INTERNAL_FORMAT_RG16I, //GL_RG16I,
				TEXTURE_INTERNAL_FORMAT_RG16UI, //GL_RG16UI,
				TEXTURE_INTERNAL_FORMAT_RG32I, //GL_RG32I,
				TEXTURE_INTERNAL_FORMAT_RG32UI, //GL_RG32UI,
				TEXTURE_INTERNAL_FORMAT_RGB8I, //GL_RGB8I,
				TEXTURE_INTERNAL_FORMAT_RGB8UI, //GL_RGB8UI,
				TEXTURE_INTERNAL_FORMAT_RGB16I, //GL_RGB16I,
				TEXTURE_INTERNAL_FORMAT_RGB16UI, //GL_RGB16UI,
				TEXTURE_INTERNAL_FORMAT_RGB32I, //GL_RGB32I,
				TEXTURE_INTERNAL_FORMAT_RGB32UI, //GL_RGB32UI,
				TEXTURE_INTERNAL_FORMAT_RGBA8I, //GL_RGBA8I,
				TEXTURE_INTERNAL_FORMAT_RGBA8UI, //GL_RGBA8UI,
				TEXTURE_INTERNAL_FORMAT_RGBA16I, //GL_RGBA16I,
				TEXTURE_INTERNAL_FORMAT_RGBA16UI, //GL_RGBA16UI,
				TEXTURE_INTERNAL_FORMAT_RGBA32I, //GL_RGBA32I,
				TEXTURE_INTERNAL_FORMAT_RGBA32UI, //GL_RGBA32UI,
				TEXTURE_INTERNAL_FORMAT_COMPRESSED_RED, //GL_COMPRESSED_RED,
				TEXTURE_INTERNAL_FORMAT_COMPRESSED_RG, //GL_COMPRESSED_RG,
				TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGB, //GL_COMPRESSED_RGB,
				TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGBA, //GL_COMPRESSED_RGBA,
				TEXTURE_INTERNAL_FORMAT_COMPRESSED_SRGB, //GL_COMPRESSED_SRGB,
				TEXTURE_INTERNAL_FORMAT_COMPRESSED_SRGB_ALPHA, //GL_COMPRESSED_SRGB_ALPHA,
				TEXTURE_INTERNAL_FORMAT_COMPRESSED_RED_RGTC1, //GL_COMPRESSED_RED_RGTC1,
				TEXTURE_INTERNAL_FORMAT_COMPRESSED_SIGNED_RED_RGTC1, //GL_COMPRESSED_SIGNED_RED_RGTC1,
				TEXTURE_INTERNAL_FORMAT_COMPRESSED_RG_RGTC2, //GL_COMPRESSED_RG_RGTC2,
				TEXTURE_INTERNAL_FORMAT_COMPRESSED_SIGNED_RG_RGTC2, //GL_COMPRESSED_SIGNED_RG_RGTC2,
				TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGBA_BPTC_UNORM, //GL_COMPRESSED_RGBA_BPTC_UNORM,
				TEXTURE_INTERNAL_FORMAT_COMPRESSED_SRGB_ALPHA_BPTC_UNORM, //GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
				TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGB_BPTC_SIGNED_FLOAT, //GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
				TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT //GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT,

			};

			enum eTextureCompressedInternalFormat : unsigned int
			{
				TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE, //0,
				COMPRESSED_RGB8_ETC2, //GL_COMPRESSED_RGB8_ETC2,
				COMPRESSED_SRGB8_ETC2, //GL_COMPRESSED_SRGB8_ETC2,
				COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2, //GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,
				COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2, //GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2,
				COMPRESSED_RGBA8_ETC2_EAC, //GL_COMPRESSED_RGBA8_ETC2_EAC,
				COMPRESSED_SRGB8_ALPHA8_ETC2_EAC, //GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,
				COMPRESSED_R11_EAC, //GL_COMPRESSED_R11_EAC,
				COMPRESSED_SIGNED_R11_EAC, //GL_COMPRESSED_SIGNED_R11_EAC,
				COMPRESSED_RG11_EAC, //GL_COMPRESSED_RG11_EAC,
				COMPRESSED_SIGNED_RG11_EAC, //GL_COMPRESSED_SIGNED_RG11_EAC,
				COMPRESSED_RGB_S3TC_DXT1_EXT, //GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
				COMPRESSED_RGBA_S3TC_DXT1_EXT, //GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
				COMPRESSED_RGBA_S3TC_DXT3_EXT, //GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
				COMPRESSED_RGBA_S3TC_DXT5_EXT, //GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
				COMPRESSED_RED_GREEN_RGTC2_EXT, //GL_COMPRESSED_RED_GREEN_RGTC2_EXT,
				COMPRESSED_RED_RGTC1_EXT, //GL_COMPRESSED_RED_RGTC1_EXT,
				COMPRESSED_SRGB_S3TC_DXT1_EXT, //GL_COMPRESSED_SRGB_S3TC_DXT1_EXT,
				COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT, //GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT,
				COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT, //GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT,
				COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT, //GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT

			};
			
			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_DESTROYBUFFER)(unsigned long long bufferID);
			extern GRAPHICS_DESTROYBUFFER DestroyBuffer;

			typedef unsigned long long(DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CREATEVERTEXARRAYOBJECT)();
			extern GRAPHICS_CREATEVERTEXARRAYOBJECT CreateVertexArrayObject;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_DESTROYVERTEXARRAYOBJECT)(unsigned long long vertexArrayObject);
			extern GRAPHICS_DESTROYVERTEXARRAYOBJECT DestroyVertexArrayObject;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_BINDVERTEXARRAYOBJECT)(const unsigned long long vertexArrayObject);
			extern GRAPHICS_BINDVERTEXARRAYOBJECT BindVertexArrayObject;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_BINDINDEXBUFFEROBJECT)(const unsigned long long indexBufferObject/*, const unsigned long long offset*/);
			extern GRAPHICS_BINDINDEXBUFFEROBJECT BindIndexBufferObject;
			
			typedef unsigned long long (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_ALLOCATEBUFFERMEMORY)
			(
				const eBufferTarget bufferTarget,
				const unsigned long long bufferSize, // in bytes
				const void* const initialData
			);
			extern GRAPHICS_ALLOCATEBUFFERMEMORY CreateBufferObject;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_ENABLEVERTEXATTRIBUTEARRAYINDEX)
				(
					const unsigned int vertexAttributeIndex
					);
			extern GRAPHICS_ENABLEVERTEXATTRIBUTEARRAYINDEX EnableVertexAttributeArrayIndex;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_DEFINEVERTEXATTRIBUTELAYOUT)
			(
				const unsigned long long vertexBufferObject,
				const unsigned int vertexAttributeIndex,
				const unsigned int componentNumber,
				const unsigned int stride,
				const unsigned int offset
			);
			extern GRAPHICS_DEFINEVERTEXATTRIBUTELAYOUT DefineVertexAttributeLayout;

			typedef unsigned long long (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CREATEINPUTLAYOUTFORD3D)
			(
				const void* const inputElementDesces,
				const unsigned int inputElementCount,
				unsigned long long vertexShaderBlobObject
			);
			extern GRAPHICS_CREATEINPUTLAYOUTFORD3D CreateInputLayoutForD3D;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_BINDINPUTLAYOUTFORD3D)
			(
				const unsigned long long inputLayoutObject
			);
			extern GRAPHICS_BINDINPUTLAYOUTFORD3D BindInputLayoutForD3D;


			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_DESTORYINPUTLAYOUTFORD3D)
			(
				unsigned long long inputLayoutObject
			);
			extern GRAPHICS_DESTORYINPUTLAYOUTFORD3D DestoryInputLayoutForD3D;

			enum eGraphicsPipeLineStage : unsigned long
			{
				VERTEX_SHADER = 0,
				PIXEL_SHADER = 1,
				COMPUTE_SHADER = 2,
				GEOMETRY_SHADER = 3,
				DOMAIN_SHADER = 4,
				HULL_SHADER = 5,
				DUMMY
			};


			#define GRAPHICS_PIPELINE_STAGE_COUNT 3
			inline extern const char* const eGraphicsPipeLineStageString[GRAPHICS_PIPELINE_STAGE_COUNT]
			{
				"VERTEX_SHADER",
				"PIXEL_SHADER",
				"COMPUTE_SHADER"
				//"GEOMETRY_SHADER",
				//"DOMAIN_SHADER",
				//"HULL_SHADER",
			};

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_BINDVERTEXDATABUFFER)
			(
				const unsigned long long bufferObject,
				const unsigned int bindingPosition,
				const unsigned int stride,
				const unsigned int offset
			);
			extern GRAPHICS_BINDVERTEXDATABUFFER BindVertexDataBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_BINDBUFFER)
			(
				const unsigned long long bufferObject,
				const unsigned int bindingPosition,
				const eBufferTarget bindBufferTarget,
				const GraphicsAPI::eGraphicsPipeLineStage targetPipeLienStage
			);
			extern GRAPHICS_BINDBUFFER BindBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_UNBINDBUFFER)
				(
					const eBufferTarget bindBufferTarget
					);
			extern GRAPHICS_UNBINDBUFFER UnBindBuffer;

			

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_BINDCONSTANTBUFFER)
				(
					const unsigned long long bufferObject,
					const unsigned int bindingPoint,
					const eGraphicsPipeLineStage pipeLineStage
				);
			extern GRAPHICS_BINDCONSTANTBUFFER BindConstantBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_UPDATEDATATOBUFFER)
			(
				const unsigned long long bufferObject,
				const GraphicsAPI::eBufferTarget bindBufferTarget,
				const unsigned long long offset,
				const unsigned long long dataSize,
				const void* const data
			);
			/**
			 * \brief Update data to buffer
			 */
			extern GRAPHICS_UPDATEDATATOBUFFER UpdateDataToBuffer;

			typedef unsigned long long (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GENERATEFRAMEBUFFER)();
			extern GRAPHICS_GENERATEFRAMEBUFFER GenerateFrameBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_DESTROYFRAMEBUFFER)(unsigned long long frameBufferObject);
			extern GRAPHICS_DESTROYFRAMEBUFFER DestroyFrameBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_BINDFRAMEBUFFER)
			(
				const unsigned int renderTargetCount,
				unsigned long long* const renderTargetViewObject,
				const unsigned int coloreTextureCount,
				unsigned long long depthStencilViewObject
			);
			extern GRAPHICS_BINDFRAMEBUFFER BindFrameBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_BINDBACKBUFFER)
			(
			);
			extern GRAPHICS_BINDBACKBUFFER BindBackBuffer;

			typedef unsigned int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CHECKFRAMEBUFFERISSUCCESFULLYCREATED)(void);
			extern GRAPHICS_CHECKFRAMEBUFFERISSUCCESFULLYCREATED CheckFrameBufferIsSuccesfullyCreated;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_BINDRENDERBUFFER)(const unsigned long long renderBufferObject);
			extern GRAPHICS_BINDRENDERBUFFER BindRenderBuffer;


			enum eFrameBufferAttachmentPoint : unsigned int
			{
				FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT0,
				FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT1,
				FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT2,
				FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT3,
				FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT4,
				FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT5,
				FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT6,
				FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT7,
				FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT8,
				FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT9,
				FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT10,
				FRAMEBUFFER_ATTACHMENT_POINT_DEPTH_ATTACHMENT,
				FRAMEBUFFER_ATTACHMENT_POINT_STENCIL_ATTACHMENT,
				FRAMEBUFFER_ATTACHMENT_POINT_DEPTH_STENCIL_ATTACHMENT
			};

			typedef unsigned long long (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_ATTACH2DCOLORTEXTURETOFRAMEBUFFER)
			(
				const unsigned long long frameBufferObject,
				const GraphicsAPI::eFrameBufferAttachmentPoint frameBufferAttachmentPoint,
				const GraphicsAPI::eTextureBindTarget textureBindTarget,
				const unsigned long long textureBufferObject,
				const unsigned int lodLevel
			);
			extern GRAPHICS_ATTACH2DCOLORTEXTURETOFRAMEBUFFER Attach2DColorTextureToFrameBuffer;


			typedef unsigned long long (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_ATTACH2DDEPTHSTENCILTEXTURETOFRAMEBUFFER)
				(
					const unsigned long long frameBufferObject,
					const GraphicsAPI::eFrameBufferAttachmentPoint frameBufferAttachmentPoint,
					const GraphicsAPI::eTextureBindTarget textureBindTarget,
					const unsigned long long textureBufferObject,
					const unsigned int lodLevel
					);
			extern GRAPHICS_ATTACH2DDEPTHSTENCILTEXTURETOFRAMEBUFFER Attach2DDepthStencilTextureToFrameBuffer;

			typedef unsigned long long (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_COPYRENDERTARGETVIEW)(const unsigned long long renderTargetView);
			extern GRAPHICS_COPYRENDERTARGETVIEW CopyRenderTargetView;

			typedef unsigned long long (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CREATERENDERBUFFEROBJECT)();
			extern GRAPHICS_CREATERENDERBUFFEROBJECT CreateRenderBufferObject;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_ALLOCATERENDERBUFFERMEMORY)
				(
					const unsigned long long renderBufferObject,
					const eTextureInternalFormat textureInternalFormat,
					const unsigned int width, const unsigned int height,
					const unsigned int multiSample
					);
			extern GRAPHICS_ALLOCATERENDERBUFFERMEMORY AllocateRenderBufferMemory;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_ATTACHRENDERBUFFERTOFRAMEBUFFER)
				(
					const unsigned long long renderBufferObject,
					const unsigned long long frameBufferObject,
					const eFrameBufferAttachmentPoint frameBufferAttachmentPoint
					);
			extern GRAPHICS_ATTACHRENDERBUFFERTOFRAMEBUFFER AttachRenderBufferToFrameBuffer;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_DESTROYRENDERBUFFER)(unsigned long long renderBuffer);
			extern GRAPHICS_DESTROYRENDERBUFFER DestroyRenderBuffer;

			typedef int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GETFRAMEBUFFERWIDTH)(const unsigned long long frameBuffer);
			extern GRAPHICS_GETFRAMEBUFFERWIDTH GetFrameBufferWidth;

			typedef int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GETFRAMEBUFFERHEIGHT)(const unsigned long long frameBuffer);
			extern GRAPHICS_GETFRAMEBUFFERHEIGHT GetFrameBufferHeight;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_DRAW)
				(
					const ePrimitiveType primitiveType,
					const unsigned long long vertexCount,
					const unsigned long long startVertexLocation
					);
			extern GRAPHICS_DRAW Draw;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_DRAWINDEXED)
				(
					const ePrimitiveType primitiveType,
					const unsigned long long indiceCount
					);
			extern GRAPHICS_DRAWINDEXED DrawIndexed;

			typedef unsigned long long (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CREATEMATERIAL)();
			extern GRAPHICS_CREATEMATERIAL CreateMaterial;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_DESTROYMATERIAL)(unsigned long long materialObject);
			extern GRAPHICS_DESTROYMATERIAL DestroyMaterial;
			/**
			 * \brief
			 * \param materialObject
			 * \return If success, return true
			 */
			typedef bool (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_LINKMATERIAL)(const unsigned long long materialObject);
			extern GRAPHICS_LINKMATERIAL LinkMaterial;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_BINDMATERIAL)(const unsigned long long materialObject, const eGraphicsPipeLineStage shaderType);
			extern GRAPHICS_BINDMATERIAL BindShader;
			
			typedef unsigned long long (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CREATESHADEROBJECT)(const eGraphicsPipeLineStage shaderType);
			extern GRAPHICS_CREATESHADEROBJECT CreateShaderObject;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_DESTROYSHADEROBJECT)(unsigned long long shaderObject);
			extern GRAPHICS_DESTROYSHADEROBJECT DestroyShaderObject;


			typedef bool (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_COMPILESHADER)
			(
				unsigned long long& shaderObject, 
				const eGraphicsPipeLineStage shaderType, 
				const char* const shaderText,
				const unsigned long long shaderTextSize
				);
			/**
			 * \brief return true if compiling shader success
			 */
			extern GRAPHICS_COMPILESHADER CompileShader;

			/**
			 * \brief return true if success
			 */
			typedef bool (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_ATTACHSHADERTOMATERIAL)
			(
				unsigned long long& shaderView, // Only used for DirectX
				const unsigned long long materialObject, // Only used for OPENGL
				const unsigned long long shaderObject,
				const eGraphicsPipeLineStage targetGraphicsPipeLineStage // only used in dx11
			);
			extern GRAPHICS_ATTACHSHADERTOMATERIAL AttachShaderToMaterial;

			typedef bool (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_DETACHSHADERFROMMATERIAL)
			(
				unsigned long long shaderView,
				const unsigned long long materialObject,
				const unsigned long long shaderObject
			);
			extern GRAPHICS_DETACHSHADERFROMMATERIAL DetachShaderFromMaterial;
			
			enum eMapBufferAccessOption : unsigned int
			{
				READ_ONLY,
				WRITE_ONLY,
				READ_WRITE
			};

			typedef void* (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_MAPBUFFEROBJECTTOCLIENTADDRESS)
				(
					const unsigned long long bufferID,
					const eBufferTarget bindBufferTarget,
					const eMapBufferAccessOption mapBufferAccessOption
					);
			extern GRAPHICS_MAPBUFFEROBJECTTOCLIENTADDRESS MapBufferObjectToClientAddress;

			typedef void* (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_RANGEDMAPBUFFEROBJECTTOCLIENTADDRESS)
				(
					const unsigned long long bufferID,
					const unsigned long long offset,
					const unsigned long long length,
					const eBufferTarget bindBufferTarget,
					const eMapBufferAccessOption mapBufferAccessOption
					);
			extern GRAPHICS_RANGEDMAPBUFFEROBJECTTOCLIENTADDRESS RangedMapBufferObjectToClientAddress;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_UNMAPBUFFEROBJECMAPPEDTTOCLIENTADDRESS)
				(
					const unsigned long long bufferID,
					const eBufferTarget bindBufferTarget
					);
			extern GRAPHICS_UNMAPBUFFEROBJECMAPPEDTTOCLIENTADDRESS UnMapBufferObjectMappedToClientAddress;


			typedef unsigned long long (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CREATEXTUREOBJECT)();
			extern GRAPHICS_CREATEXTUREOBJECT CreateTextureObject;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_DESTROYTEXTUREOBJECT)(unsigned long long textureObject);
			extern GRAPHICS_DESTROYTEXTUREOBJECT DestroyTextureObject;


			typedef unsigned long long (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_CREATETEXTUREVIEWOBJECT)(const unsigned long long textureObject);
			extern GRAPHICS_CREATETEXTUREVIEWOBJECT CreateTextureViewObject;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_DESTROYTEXTUREVIEWOBJECT)(unsigned long long textureViewObject);
			extern GRAPHICS_DESTROYTEXTUREVIEWOBJECT DestroyTextureViewObject;


			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_BINDTEXTUREOBJECT)
			(
				const unsigned long long textureObject, 
				const eTextureBindTarget textureBindTarget,
				const unsigned int bindingLocation,
				const eGraphicsPipeLineStage targetPipeLineStage
			);
			extern GRAPHICS_BINDTEXTUREOBJECT BindTextureObject;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_ACTIVATETEXTUREUNIT)(const unsigned int unitIndex);
			extern GRAPHICS_ACTIVATETEXTUREUNIT ActivateTextureUnit;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_BINDTEXTUREOBJECTANDACTIVATETEXTUREUNIT)
				(
					const unsigned long long textureObject,
					const unsigned int unitIndex
					);
			extern GRAPHICS_BINDTEXTUREOBJECTANDACTIVATETEXTUREUNIT BindTextureObjectAndActivateTextureUnit;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_UNBINDTEXTUREOBJECT)(const eTextureBindTarget textureBindTarget);
			extern GRAPHICS_UNBINDTEXTUREOBJECT UnBindTextureObject;


			enum eImageInterpolation : unsigned int
			{
				IMAGE_INTERPOLATION_NEAREST, // = GL_NEAREST,
				IMAGE_INTERPOLATION_LINEAR // = GL_LINEAR
			};

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_BLITFRAMEBUFFER)
			(
				const unsigned long long ReadFrameBufferObject,
				const unsigned int ReadBindingPoint,
				const unsigned long long DrawFrameBufferObject,
				const unsigned int DrawBindingPoint,
				const int srcX0, const int srcY0, const int srcX1, const int srcY1,
				const int dstX0, const int dstY0, const int dstX1, const int dstY1,
				const GraphicsAPI::eBufferBitType mask,
				const GraphicsAPI::eImageInterpolation filter
			);
			extern GRAPHICS_BLITFRAMEBUFFER BlitFrameBuffer;


			enum eTextureMetaDataType : unsigned int
			{
				TEXTURE_WIDTH, // = GL_TEXTURE_WIDTH,
				TEXTURE_HEIGHT, // = GL_TEXTURE_HEIGHT,
				TEXTURE_DEPTH, // = GL_TEXTURE_DEPTH,
				TEXTURE_INTERNAL_FORMAT, // = GL_TEXTURE_INTERNAL_FORMAT,
				TEXTURE_RED_SIZE, // = GL_TEXTURE_RED_SIZE,
				TEXTURE_GREEN_SIZE, // = GL_TEXTURE_GREEN_SIZE,
				TEXTURE_BLUE_SIZE, // = GL_TEXTURE_BLUE_SIZE,
				TEXTURE_ALPHA_SIZE, // = GL_TEXTURE_ALPHA_SIZE,
				TEXTURE_DEPTH_SIZE, // = GL_TEXTURE_DEPTH_SIZE,
				TEXTURE_COMPRESSED, // = GL_TEXTURE_COMPRESSED,
				TEXTURE_COMPRESSED_IMAGE_SIZE, // = GL_TEXTURE_COMPRESSED_IMAGE_SIZE,
				TEXTURE_BUFFER_OFFSET, // = GL_TEXTURE_BUFFER_OFFSET, // available only if the GL version is 4.3 or greater.
				TEXTURE_BUFFER_SIZE, // = GL_TEXTURE_BUFFER_SIZE // available only if the GL version is 4.3 or greater.
			};

			typedef float (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GETTEXTUREMETADATAFLOAT)
				(
					const unsigned long long textureObject,
					const eTextureBindTarget textureBindTarget,
					const unsigned int lodLevel,
					const eTextureMetaDataType textureMetaDataType
					);
			extern GRAPHICS_GETTEXTUREMETADATAFLOAT GetTextureMetaDataFloat;


			typedef int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GETTEXTUREMETADATAINT)
				(
					const unsigned long long textureObject,
					const eTextureBindTarget textureBindTarget,
					const unsigned int lodLevel,
					const eTextureMetaDataType textureMetaDataType
					);
			extern GRAPHICS_GETTEXTUREMETADATAINT GetTextureMetaDataInt;


			enum eTextureParameterType : unsigned int
			{
				DEPTH_STENCIL_TEXTURE_MODE, // = GL_DEPTH_STENCIL_TEXTURE_MODE,
				TEXTURE_BASE_LEVEL, // = GL_TEXTURE_BASE_LEVEL,
				TEXTURE_COMPARE_FUNC, // = GL_TEXTURE_COMPARE_FUNC,
				TEXTURE_COMPARE_MODE, // = GL_TEXTURE_COMPARE_MODE,
				TEXTURE_LOD_BIAS, // = GL_TEXTURE_LOD_BIAS,
				TEXTURE_MIN_FILTER, // = GL_TEXTURE_MIN_FILTER,
				TEXTURE_MAG_FILTER, // = GL_TEXTURE_MAG_FILTER,
				TEXTURE_MIN_LOD, // = GL_TEXTURE_MIN_LOD,
				TEXTURE_MAX_LOD, // = GL_TEXTURE_MAX_LOD,
				TEXTURE_MAX_LEVEL, // = GL_TEXTURE_MAX_LEVEL,
				TEXTURE_SWIZZLE_R, // = GL_TEXTURE_SWIZZLE_R,
				TEXTURE_SWIZZLE_G, // = GL_TEXTURE_SWIZZLE_G,
				TEXTURE_SWIZZLE_B, // = GL_TEXTURE_SWIZZLE_B,
				TEXTURE_SWIZZLE_A, // = GL_TEXTURE_SWIZZLE_A,
				TEXTURE_WRAP_S, // = GL_TEXTURE_WRAP_S,
				TEXTURE_WRAP_T, // = GL_TEXTURE_WRAP_T,
				TEXTURE_WRAP_R // = GL_TEXTURE_WRAP_R
			};

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETTEXTUREPARAMETERFLOAT)(const eTextureBindTarget textureBindTarget, const eTextureParameterType textureParameterType, const float parameter);
			extern GRAPHICS_SETTEXTUREPARAMETERFLOAT SetTextureParameterFloat;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETTEXTUREPARAMETERINT)(const eTextureBindTarget textureBindTarget, const eTextureParameterType textureParameterType, const int parameter);
			extern GRAPHICS_SETTEXTUREPARAMETERINT SetTextureParameterInt;


			enum eTextureParameterValue : unsigned int
			{
				NEAREST, // GL_NEAREST,
				LINEAR, // GL_LINEAR,
				NEAREST_MIPMAP_NEAREST, // GL_NEAREST_MIPMAP_NEAREST,
				LINEAR_MIPMAP_NEAREST, // GL_LINEAR_MIPMAP_NEAREST,
				NEAREST_MIPMAP_LINEAR, // GL_NEAREST_MIPMAP_LINEAR,
				LINEAR_MIPMAP_LINEAR, // GL_LINEAR_MIPMAP_LINEAR,
				CLAMP_TO_EDGE, // GL_CLAMP_TO_EDGE,
				CLAMP_TO_BORDER, // GL_CLAMP_TO_BORDER,
				MIRRORED_REPEAT, // GL_MIRRORED_REPEAT,
				REPEAT, // GL_REPEAT,
				MIRROR_CLAMP_TO_EDGE // GL_MIRROR_CLAMP_TO_EDGE,
			};

			enum eWrapMode : unsigned int
			{
				WRAP_MODE_CLAMP_TO_EDGE, // GL_CLAMP_TO_EDGE,
				WRAP_MODE_CLAMP_TO_BORDER, // GL_CLAMP_TO_BORDER,
				WRAP_MODE_MIRRORED_REPEAT, // GL_MIRRORED_REPEAT,
				WRAP_MODE_REPEAT, // GL_REPEAT,
				WRAP_MODE_MIRROR_CLAMP_TO_EDGE // GL_MIRROR_CLAMP_TO_EDGE,
			};

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETTEXTUREWRAPMODES)(const eTextureBindTarget textureBindTarget, const eWrapMode wrapMode);
			extern GRAPHICS_SETTEXTUREWRAPMODES SetTextureWrapMode_S;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETTEXTUREWRAPMODET)(const eTextureBindTarget textureBindTarget, const eWrapMode wrapMode);
			extern GRAPHICS_SETTEXTUREWRAPMODET SetTextureWrapMode_T;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETTEXTUREWRAPMODER)(const eTextureBindTarget textureBindTarget, const eWrapMode wrapMode);
			extern GRAPHICS_SETTEXTUREWRAPMODER SetTextureWrapMode_R;



			enum eFilterMode : unsigned int
			{
				FILTER_MODE_NEAREST, // GL_NEAREST,
				FILTER_MODE_LINEAR, // GL_LINEAR,
				FILTER_MODE_NEAREST_MIPMAP_NEAREST, // GL_NEAREST_MIPMAP_NEAREST,
				FILTER_MODE_LINEAR_MIPMAP_NEAREST, // GL_LINEAR_MIPMAP_NEAREST,
				FILTER_MODE_NEAREST_MIPMAP_LINEAR, // GL_NEAREST_MIPMAP_LINEAR,
				FILTER_MODE_LINEAR_MIPMAP_LINEAR // GL_LINEAR_MIPMAP_LINEAR,
			};

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETMINFILTER)(const eTextureBindTarget textureBindTarget, const eFilterMode filterMode);
			extern GRAPHICS_SETMINFILTER SetMinFilter;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETMAGFILTER)(const eTextureBindTarget textureBindTarget, const eFilterMode filterMode);
			extern GRAPHICS_SETMAGFILTER SetMagFilter;


			enum ePixelFormat : unsigned int
			{
				PIXEL_FORMAT_STENCIL_INDEX, //GL_STENCIL_INDEX,
				PIXEL_FORMAT_DEPTH_COMPONENT, //GL_DEPTH_COMPONENT,
				PIXEL_FORMAT_DEPTH_STENCIL, //GL_DEPTH_STENCIL,
				PIXEL_FORMAT_RED, //GL_RED,
				PIXEL_FORMAT_GREEN, //GL_GREEN,
				PIXEL_FORMAT_BLUE, //GL_BLUE,
				PIXEL_FORMAT_RG, //GL_RG,
				PIXEL_FORMAT_RGB, //GL_RGB,
				PIXEL_FORMAT_RGBA, //GL_RGBA,
				PIXEL_FORMAT_BGR, //GL_BGR,
				PIXEL_FORMAT_BGRA, //GL_BGRA,
				PIXEL_FORMAT_RED_INTEGER, //GL_RED_INTEGER,
				PIXEL_FORMAT_GREEN_INTEGER, //GL_GREEN_INTEGER,
				PIXEL_FORMAT_BLUE_INTEGER, //GL_BLUE_INTEGER,
				PIXEL_FORMAT_RG_INTEGER, //GL_RG_INTEGER,
				PIXEL_FORMAT_RGB_INTEGER, //GL_RGB_INTEGER,
				PIXEL_FORMAT_RGBA_INTEGER, //GL_RGBA_INTEGER,
				PIXEL_FORMAT_STENCILBGR_INTEGER_INDEX, //GL_BGR_INTEGER,
				PIXEL_FORMAT_BGRA_INTEGER, //GL_BGRA_INTEGER
			};

			typedef unsigned char* (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_FETCHTEXTUREPIXELS)
				(
					const eTextureBindTarget textureBindTarget,
					const int lodLevel,
					const eTextureComponentFormat textureComponentFormat,
					const eDataType datatType,
					const unsigned long long bufferSize
					);
			extern GRAPHICS_FETCHTEXTUREPIXELS FetchTexturePixels;


			typedef unsigned char* (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_READPIXELS)
			(
				const unsigned long long bufferObject,
				const eBufferMode bufferMode,
				const unsigned long long bufferSize,
				const int startX,
				const int startY,
				const int width,
				const int height,
				const dooms::graphics::GraphicsAPI::eTextureComponentFormat pixelFormat,
				const dooms::graphics::GraphicsAPI::eDataType dataType
			);
			extern GRAPHICS_READPIXELS ReadPixels;

			enum eBindFlag : unsigned long
			{
				BIND_VERTEX_BUFFER = 0x1L,
				BIND_INDEX_BUFFER = 0x2L,
				BIND_CONSTANT_BUFFER = 0x4L,
				BIND_SHADER_RESOURCE = 0x8L,
				BIND_STREAM_OUTPUT = 0x10L,
				BIND_RENDER_TARGET = 0x20L,
				BIND_DEPTH_STENCIL = 0x40L,
				BIND_UNORDERED_ACCESS = 0x80L,
				BIND_DECODER = 0x200L,
				BIND_VIDEO_ENCODER = 0x400L
			};
		
			
			typedef unsigned long long (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_ALLOCATE2DTEXTUREOBJECT)
				(
					const eTextureBindTarget textureBindTarget,
					const unsigned int lodCount,
					const eTextureInternalFormat textureInternalFormat,
					const eTextureCompressedInternalFormat textureCompressedInternalFormat,
					const unsigned long long width,
					const unsigned long long height,
					const eBindFlag bindFlag
				);
			extern GRAPHICS_ALLOCATE2DTEXTUREOBJECT Allocate2DTextureObject;
			
			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_UPDATEPIXELSTO2DTEXTURE)
				(
					const unsigned long long textureObject,
					const eTextureBindTarget textureBindTarget,
					const eTargetTexture targetTexture,
					const unsigned int lodLevel,
					const unsigned int xOffset,
					const unsigned int yOffset,
					const unsigned long long width,
					const unsigned long long height,
					const GraphicsAPI::eTextureComponentFormat textureComponentFormat,
					const GraphicsAPI::eDataType dataType,
					const eTextureInternalFormat textureInternalFormat,
					const eTextureCompressedInternalFormat textureCompressedInternalFormat,
					const void* const pixelDatas,
					const size_t rowByteSize,
					const size_t totalDataSize
					);
			extern GRAPHICS_UPDATEPIXELSTO2DTEXTURE UploadPixelsTo2DTexture;
			
			typedef int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GETCONSTANTBUFFERBINDINGPOINT)
				(
					const unsigned long long constantBufferObject,
					const unsigned int blockIndex
					);
			extern GRAPHICS_GETCONSTANTBUFFERBINDINGPOINT GetConstantBufferBindingPoint;


			typedef int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GETCONSTANTBUFFERDATASIZE)
				(
					const unsigned long long constantBufferObject,
					const unsigned int blockIndex
					);
			extern GRAPHICS_GETCONSTANTBUFFERDATASIZE GetConstantBufferDataSize;


			typedef int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GETCONSTANTBUFFERBLOCKCOUNT)
				(
					const unsigned long long constantBufferObject
					);
			extern GRAPHICS_GETCONSTANTBUFFERBLOCKCOUNT GetConstantBufferBlockCount;


			typedef int (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_GETCONSTANTBUFFERUNIFORMLOCATION)(const unsigned long long constantBufferObject, const char* const uniformStr);
			extern GRAPHICS_GETCONSTANTBUFFERUNIFORMLOCATION GetConstantBufferUniformLocation;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETWINDOWTITLE)(const char* const title);
			extern GRAPHICS_SETWINDOWTITLE SetWindowTitle;

			typedef void (DOOMS_ENGINE_API_ENTRY_P GRAPHICS_SETWINDOWTITLEW)(const wchar_t* const title);
			extern GRAPHICS_SETWINDOWTITLEW SetWindowTitleW;

		}
	}
}


