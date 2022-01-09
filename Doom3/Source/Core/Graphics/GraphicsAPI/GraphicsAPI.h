#pragma once

#include <vector>
#include <array>
#include <string>

#include "../../Macros/DllMarcos.h"

namespace dooms
{
	namespace graphics
	{
		// DirectX / OpenGL(Vulkan) concepts mapping chart
		// https://computergraphics.stackexchange.com/questions/4422/directx-openglvulkan-concepts-mapping-chart/4432
		// https://anteru.net/blog/2013/porting-from-directx11-to-opengl-4-2-api-mapping/

		enum class eGraphicsAPIType
		{
			GraphicsAPIType_NONE,
			OpenGL,
			DX11
			
		};

		class GraphicsAPIInput;
		class DOOMS_ENGINE GraphicsAPI
		{
		private:

			static GraphicsAPIInput* mGraphicsAPIInputManager;
			inline static eGraphicsAPIType mGraphicsAPIType = eGraphicsAPIType::GraphicsAPIType_NONE;

			inline static std::string PlatformVersion{};

		public:

			using DEBUG_FUNCTION = void (*)(const char* const debugMessage);
			inline static DEBUG_FUNCTION* mDEBUG_FUNCTION = nullptr;

			inline static std::string GetPlatformVersion()
			{
				return PlatformVersion;
			}

			static void* GetPlatformWindow();

			static void SetGraphicsAPIType(const eGraphicsAPIType graphicsAPIType);
			inline static eGraphicsAPIType GetGraphicsAPIType() noexcept
			{
				return mGraphicsAPIType;
			}
			static double GetTime();

			enum eBufferBitType : unsigned int
			{
				COLOR_BUFFER, // = GL_COLOR_BUFFER_BIT,
				DEPTH_BUFFER, // = GL_DEPTH_BUFFER_BIT,
				DEPTH_STENCIL_BUFFER // = GL_STENCIL_BUFFER_BIT
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

			enum eBufferAttachmentType : unsigned int
			{
				ATTACHMENT_COLOR0, // = GL_COLOR_BUFFER_BIT,
				ATTACHMENT_COLOR1, // = GL_COLOR_BUFFER_BIT,
				ATTACHMENT_COLOR2, // = GL_COLOR_BUFFER_BIT,
				ATTACHMENT_COLOR3, // = GL_COLOR_BUFFER_BIT,
				ATTACHMENT_DEPTH, // = GL_DEPTH_BUFFER_BIT,
				ATTACHMENT_DEPTH_STENCIL //= GL_STENCIL_BUFFER_BIT
			};

			enum eBindFrameBufferTarget : unsigned int
			{
				DRAW_FRAMEBUFFER,
				READ_FRAMEBUFFER,
				FRAMEBUFFER
			};

			enum ePrimitiveType : unsigned int
			{
				POINTS, //= GL_POINTS,
				//LINE_STRIP = GL_LINE_STRIP,
				//LINE_LOOP = GL_LINE_LOOP,
				LINES, //= GL_LINES,
				//LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
				//LINES_ADJACENCY = GL_LINES_ADJACENCY,
				//TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
				//TRIANGLE_FAN = GL_TRIANGLE_FAN,
				TRIANGLES, //= GL_TRIANGLES,
				//TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
				//TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
				//PATCHES = GL_PATCHES,
				NONE = 0XFFFF
			};

			enum eBufferTarget : unsigned int
			{
				ARRAY_BUFFER,
				ELEMENT_ARRAY_BUFFER,
				DRAW_INDIRECT_BUFFER,
				TEXTURE_BUFFER,
				UNIFORM_BUFFER,
			};

			static unsigned int Initialize();
			static unsigned int DeInitialize();
			static void SwapBuffer() noexcept;

			static void SetVSync(const bool isEnabled) noexcept;

			enum eDepthFuncType : unsigned int
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

			static void SetIsDepthTestEnabled(const bool isEnabled) noexcept;
			static void SetDepthFunc(const eDepthFuncType depthFuncType) noexcept;
			static void SetDepthMask(const bool isWriteDepthBuffer) noexcept;

			static void SetIsAlphaTestEnabled(const bool isEnabled) noexcept;
			static void SetIsBlendEnabled(const bool isEnabled) noexcept;

			static void SetViewport(const int startX, const int startY, const unsigned int width, const unsigned int height) noexcept;
			static std::array<int, 4> GetViewPort();

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
			static void SetBlendFactor(const eBlendFactor sourceBlendFactor, const eBlendFactor destinationBlendFactor) noexcept;

			enum eCullFace : unsigned int
			{
				CULLFACE_FRONT,
				CULLFACE_BACK,
				CULLFACE_FRONT_AND_BACK
			};

			static void SetCullFace(const eCullFace cullFace) noexcept;

			enum eWinding : unsigned int
			{
				CW,
				CCW
			};

			static void SetFrontFaceWinding(const eWinding winding) noexcept;

			static void SetDrawBuffer(const GraphicsAPI::eBufferMode bufferMode) noexcept;
			static void SetDrawBuffers(const unsigned int count, const std::vector<GraphicsAPI::eBufferMode> bufferModes) noexcept;
			static void SetReadBuffer(const GraphicsAPI::eBufferMode bufferMode) noexcept;

			static void ClearColor(const float r, const float g, const float b, const float a) noexcept;
			static void ClearColor(const float* const colors) noexcept;
			static void ClearBuffer(const unsigned int clearMaskBits) noexcept;
			static void ClearBuffer(const eBufferBitType clearMask) noexcept;
			static void ClearBuffer(const eBufferBitType clearMask1, const eBufferBitType clearMask2) noexcept;
			static void ClearBuffer(const eBufferBitType clearMask1, const eBufferBitType clearMask2, const eBufferBitType clearMask3) noexcept;
			static void ClearSpecificBuffer(const eBufferType bufferType, const unsigned int drawBufferIndex, const float r, const float g, const float b, const float a) noexcept;
			static void ClearSpecificBuffer(const eBufferType bufferType, const unsigned int drawBufferIndex, const float* const colors) noexcept;

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
				TEXTURE_CUBE_MAP_ARRAY, // = GL_TEXTURE_CUBE_MAP_ARRAY,
				_TEXTURE_BUFFER, // = GL_TEXTURE_BUFFER,
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
				TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT, //GL_DEPTH_COMPONENT,
				TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT16, //GL_DEPTH_COMPONENT16,
				TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT24, //GL_DEPTH_COMPONENT24,
				TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT32, //GL_DEPTH_COMPONENT32,
				TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT32F, //GL_DEPTH_COMPONENT32F,
				TEXTURE_INTERNAL_FORMAT_DEPTH_STENCIL, //GL_DEPTH_STENCIL,
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

			static std::vector<unsigned int> GenerateBuffer(const unsigned int count) noexcept;
			static void DestroyBuffer(const unsigned int bufferID) noexcept;
			static std::vector<unsigned int> CreateBuffers(const unsigned int bufferCount) noexcept;
			static void DestroyBuffers(const std::vector<unsigned int>& buffers) noexcept;
			static std::vector<unsigned int> CreateVertexArrayObject(const unsigned int count) noexcept;
			static void DestroyVertexArrayObject(const std::vector<unsigned int>& vertexArrayObjects) noexcept;
			static void BindVertexArrayObject(const unsigned int vertexArrayObject) noexcept;
			static void UnBindVertexArrayObject() noexcept;
			static void AllocateBufferMemory
			(
				const eBufferTarget bufferTarget,
				const unsigned int bufferSize, // in bytes
				const void* const initialData
			) noexcept;
			static void EnableVertexAttributeArrayIndex
			(
				const unsigned int vertexAttributeIndex
			) noexcept;
			static void DefineVertexAttributeLayout
			(
				const unsigned int vertexAttributeIndex,
				const unsigned int componentNumber,
				const unsigned int stride,
				const unsigned int offset
			) noexcept;

			static void BindBuffer
			(
				const unsigned int bufferObject,
				const eBufferTarget bindBufferTarget
			) noexcept;
			static void UnBindBuffer
			(
				const eBufferTarget bindBufferTarget
			) noexcept;
			static void BindBufferToIndexedBuffer
			(
				const eBufferTarget bindBufferTarget,
				const unsigned int bindingPoint,
				const unsigned int bufferObject
			) noexcept;

			static void UpdateDataToBuffer
			(
				const eBufferTarget bindFrameBufferTarget,
				const unsigned int offset,
				const unsigned int dataSize,
				const void* const data
			) noexcept;

			static unsigned int GenerateFrameBuffer() noexcept;
			static void DestroyFrameBuffer(const unsigned int frameBufferObject) noexcept;
			static void BindFrameBuffer
			(
				const unsigned int frameBufferObject,
				const eBindFrameBufferTarget bindFrameBufferTarget
			) noexcept;

			static unsigned int CheckFrameBufferIsSuccesfullyCreated();

			static void BindRenderBuffer(const unsigned int renderBufferObject) noexcept;


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

			static void Attach2DTextureToFrameBuffer
			(
				const eBindFrameBufferTarget bindFrameBufferTarget,
				const eFrameBufferAttachmentPoint frameBufferAttachmentPoint,
				const eTextureBindTarget textureBindTarget,
				const unsigned int textureBufferObject,
				const int lodLevel
			);

			static std::vector<unsigned int> CreateRenderBufferObject(const unsigned int renderBufferCount) noexcept;
			static void AllocateRenderBufferMemory
			(
				const unsigned int renderBufferObject,
				const eTextureInternalFormat textureInternalFormat,
				const unsigned int width, const unsigned int height,
				const unsigned int multiSample
			) noexcept;
			static void AttachRenderBufferToFrameBuffer
			(
				const unsigned int renderBufferObject,
				const unsigned int frameBufferObject,
				const eBufferAttachmentType bufferType
			) noexcept;
			static void DestroyRenderBuffer(const unsigned int renderBuffer) noexcept;

			static int GetFrameBufferWidth(const unsigned int frameBuffer);
			static int GetFrameBufferHeight(const unsigned int frameBuffer);

			static void Draw
			(
				const ePrimitiveType primitiveType,
				const unsigned int vertexCount,
				const unsigned int startVertexLocation = 0
			) noexcept;
			static void DrawIndexed
			(
				const ePrimitiveType primitiveType,
				const unsigned int indiceCount,
				const void* const indices = 0
			) noexcept;

			static unsigned int CreateMaterial() noexcept;
			static void DestroyMaterial(const unsigned int materialObject) noexcept;
			/**
			 * \brief
			 * \param materialObject
			 * \return If success, return true
			 */
			static bool LinkMaterial(const unsigned int materialObject) noexcept;
			static void BindMaterial(const unsigned int materialObject) noexcept;

			enum eShaderType : unsigned int
			{
				ShaderType_None,
				Vertex,
				Fragment,
				Geometry
			};

			static unsigned int CreateShaderObject(const eShaderType shaderType) noexcept;
			static void DestroyShaderObject(const unsigned int shaderObject) noexcept;
			static void CompileShader(const unsigned int shaderObject, const char* const shaderText) noexcept;
			static void CompileShaders(const unsigned int shaderObject, const unsigned int shaderCount, const char* const* const shaderTexts) noexcept;

			static void AttachShaderToMaterial(const unsigned int materialObject, const unsigned int shaderObject) noexcept;

			static void UpdateConstantBuffer_bool1(const int constantBufferID, const bool value1) noexcept;
			static void UpdateConstantBuffer_bool2(const int constantBufferID, const bool value1, const bool value2) noexcept;
			static void UpdateConstantBuffer_bool3(const int constantBufferID, const bool value1, const bool value2, const bool value3) noexcept;
			static void UpdateConstantBuffer_bool4(const int constantBufferID, const bool value1, const bool value2, const bool value3, const bool value4) noexcept;

			static void UpdateConstantBuffer_int1(const int constantBufferID, const int value1) noexcept;
			static void UpdateConstantBuffer_int2(const int constantBufferID, const int value1, const int value2) noexcept;
			static void UpdateConstantBuffer_int3(const int constantBufferID, const int value1, const int value2, const int value3) noexcept;
			static void UpdateConstantBuffer_int4(const int constantBufferID, const int value1, const int value2, const int value3, const int value4) noexcept;

			static void UpdateConstantBuffer_float1(const int constantBufferID, const float value1) noexcept;
			static void UpdateConstantBuffer_float2(const int constantBufferID, const float value1, const float value2) noexcept;
			static void UpdateConstantBuffer_float3(const int constantBufferID, const float value1, const float value2, const float value3) noexcept;
			static void UpdateConstantBuffer_float4(const int constantBufferID, const float value1, const float value2, const float value3, const float value4) noexcept;

			static void UpdateConstantBuffer_mat2x2f(const int constantBufferID, const float* const matrix) noexcept;
			static void UpdateConstantBuffer_mat3x3f(const int constantBufferID, const float* const matrix) noexcept;
			static void UpdateConstantBuffer_mat4x4f(const int constantBufferID, const float* const matrix) noexcept;

			enum eMapBufferAccessOption : unsigned int
			{
				READ_ONLY,
				WRITE_ONLY,
				READ_WRITE
			};

			static void* MapBufferObjectToClientAddress
			(
				const unsigned int bufferID,
				const unsigned long long offset,
				const unsigned long long length,
				const eBufferTarget bindBufferTarget,
				const eMapBufferAccessOption mapBufferAccessOption
			) noexcept;



			static unsigned int CreateTextureObject() noexcept;
			static void DestroyTextureObject(const unsigned int textureObject) noexcept;
			static void BindTextureObject(const unsigned int textureObject, const eTextureBindTarget textureBindTarget) noexcept;
			static void ActivateTextureUnit(const unsigned int unitIndex) noexcept;
			static void BindTextureObjectAndActivateTextureUnit
			(
				const unsigned int textureObject,
				const unsigned int unitIndex
			) noexcept;
			static void UnBindTextureObject(const eTextureBindTarget textureBindTarget) noexcept;

			enum eImageInterpolation : unsigned int
			{
				IMAGE_INTERPOLATION_NEAREST, // = GL_NEAREST,
				IMAGE_INTERPOLATION_LINEAR // = GL_LINEAR
			};

			static void BlitFrameBuffer
			(
				const unsigned int ReadFrameBufferObject,
				const unsigned int DrawFrameBufferObject,
				const int srcX0,
				const int srcY0,
				const int srcX1,
				const int srcY1,
				const int dstX0,
				const int dstY0,
				const int dstX1,
				const int dstY1,
				const GraphicsAPI::eBufferBitType mask,
				const GraphicsAPI::eImageInterpolation filter
			);

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

			static float GetTextureMetaDataFloat
			(
				const unsigned int textureObject,
				const eTextureBindTarget textureBindTarget,
				const unsigned int lodLevel,
				const eTextureMetaDataType textureMetaDataType
			) noexcept;

			static int GetTextureMetaDataInt
			(
				const unsigned int textureObject,
				const eTextureBindTarget textureBindTarget,
				const unsigned int lodLevel,
				const eTextureMetaDataType textureMetaDataType
			) noexcept;

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

			static void SetTextureParameterFloat(const eTextureBindTarget textureBindTarget, const eTextureParameterType textureParameterType, const float parameter) noexcept;
			static void SetTextureParameterInt(const eTextureBindTarget textureBindTarget, const eTextureParameterType textureParameterType, const int parameter) noexcept;

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

			enum eFilterMode : unsigned int
			{
				FILTER_MODE_NEAREST, // GL_NEAREST,
				FILTER_MODE_LINEAR, // GL_LINEAR,
				FILTER_MODE_NEAREST_MIPMAP_NEAREST, // GL_NEAREST_MIPMAP_NEAREST,
				FILTER_MODE_LINEAR_MIPMAP_NEAREST, // GL_LINEAR_MIPMAP_NEAREST,
				FILTER_MODE_NEAREST_MIPMAP_LINEAR, // GL_NEAREST_MIPMAP_LINEAR,
				FILTER_MODE_LINEAR_MIPMAP_LINEAR // GL_LINEAR_MIPMAP_LINEAR,
			};

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

			static unsigned char* FetchTexturePixels
			(
				const eTextureBindTarget textureBindTarget,
				const int lodLevel,
				const eTextureComponentFormat textureComponentFormat,
				const eDataType datatType,
				const unsigned long long bufferSize
			) noexcept;

			static unsigned char* ReadPixels
			(
				const unsigned long bufferSize,
				const int startX,
				const int startY,
				const int width,
				const int height,
				const dooms::graphics::GraphicsAPI::eTextureComponentFormat pixelFormat,
				const dooms::graphics::GraphicsAPI::eDataType dataType
			);

			static void Define1DTextureStorageRequirement
			(
				const eTextureBindTarget textureBindTarget,
				const unsigned int lodLevel,
				const eTextureInternalFormat textureInternalFormat,
				const unsigned long long width
			);

			static void Define2DTextureStorageRequirement
			(
				const eTextureBindTarget textureBindTarget,
				const unsigned int lodLevel,
				const eTextureInternalFormat textureInternalFormat,
				const unsigned long long width,
				const unsigned long long height
			);

			static void Define3DTextureStorageRequirement
			(
				const eTextureBindTarget textureBindTarget,
				const unsigned int lodLevel,
				const eTextureInternalFormat textureInternalFormat,
				const unsigned long long width,
				const unsigned long long height,
				const unsigned long long depth
			);

			static void Define1DCompressedTextureStorageRequirement
			(
				const eTextureBindTarget textureBindTarget,
				const unsigned int lodLevel,
				const eTextureCompressedInternalFormat textureInternalFormat,
				const unsigned long long width
			);

			static void Define2DCompressedTextureStorageRequirement
			(
				const eTextureBindTarget textureBindTarget,
				const unsigned int lodLevel,
				const eTextureCompressedInternalFormat textureInternalFormat,
				const unsigned long long width,
				const unsigned long long height
			);

			static void Define3DCompressedTextureStorageRequirement
			(
				const eTextureBindTarget textureBindTarget,
				const unsigned int lodLevel,
				const eTextureCompressedInternalFormat textureInternalFormat,
				const unsigned long long width,
				const unsigned long long height,
				const unsigned long long depth
			);

			static void UploadPixelsTo1DTexture
			(
				const eTargetTexture targetTexture,
				const unsigned int lodLevel,
				const unsigned int xOffset,
				const unsigned long long width,
				const eTextureComponentFormat textureComponentFormat,
				const eDataType dataType,
				const void* const pixelDatas
			);

			static void UploadPixelsTo2DTexture
			(
				const eTargetTexture targetTexture,
				const unsigned int lodLevel,
				const unsigned int xOffset,
				const unsigned int yOffset,
				const unsigned long long width,
				const unsigned long long height,
				const eTextureComponentFormat textureComponentFormat,
				const eDataType dataType,
				const void* const pixelDatas
			);

			static void UploadPixelsTo3DTexture
			(
				const eTargetTexture targetTexture,
				const unsigned int lodLevel,
				const unsigned int xOffset,
				const unsigned int yOffset,
				const unsigned int zOffset,
				const unsigned long long width,
				const unsigned long long height,
				const unsigned long long depth,
				const eTextureComponentFormat textureComponentFormat,
				const eDataType dataType,
				const void* const pixelDatas
			);

			static void UploadPixelsTo1DCompressedTexture
			(
				const eTargetTexture targetTexture,
				const unsigned int lodLevel,
				const unsigned int xOffset,
				const unsigned long long width,
				const eTextureComponentFormat textureComponentFormat,
				const eDataType dataType,
				const void* const pixelDatas
			);

			static void UploadPixelsTo2DCompressedTexture
			(
				const eTargetTexture targetTexture,
				const unsigned int lodLevel,
				const unsigned int xOffset,
				const unsigned int yOffset,
				const unsigned long long width,
				const unsigned long long height,
				const eTextureComponentFormat textureComponentFormat,
				const eDataType dataType,
				const void* const pixelDatas
			);

			static void UploadPixelsTo3DCompressedTexture
			(
				const eTargetTexture targetTexture,
				const unsigned int lodLevel,
				const unsigned int xOffset,
				const unsigned int yOffset,
				const unsigned int zOffset,
				const unsigned long long width,
				const unsigned long long height,
				const unsigned long long depth,
				const eTextureComponentFormat textureComponentFormat,
				const eDataType dataType,
				const void* const pixelDatas
			);

			static int GetConstantBufferBindingPoint
			(
				const unsigned int constantBufferObject,
				const unsigned int blockIndex
			);

			static int GetConstantBufferDataSize
			(
				const unsigned int constantBufferObject,
				const unsigned int blockIndex
			);

			static int GetConstantBufferBlockCount
			(
				const unsigned int constantBufferObject
			);

			static int GetConstantBufferUniformLocation(const unsigned int constantBufferObject, const char* const uniformStr);
		};
	}
}


