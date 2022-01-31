#include "GraphicsAPI.h"

#include <cassert>
#include <cstdio>
#include <string>
#include "stdio.h"
#include <Windows.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


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
			static std::string OpenGLVersion{};
			static GraphicsAPI::DEBUG_FUNCTION mDEBUG_FUNCTION = nullptr;
			static unsigned int DrawCallCounter;

			enum class GetStringParameter
			{
				VENDOR = GL_VENDOR,
				RENDERER = GL_VENDOR,
				VERSION = GL_VENDOR,
				SHADING_LANGUAGE_VERSION = GL_VENDOR,
			};

			FORCE_INLINE static unsigned int GetGLTestFuncType(const GraphicsAPI::eTestFuncType depthFuncType)
			{
				switch (depthFuncType)
				{
				case GraphicsAPI::ALWAYS:
					return GL_ALWAYS;
				case GraphicsAPI::NEVER:
					return GL_NEVER;
				case GraphicsAPI::LESS:
					return GL_LESS;
				case GraphicsAPI::EQUAL:
					return GL_EQUAL;
				case GraphicsAPI::LEQUAL:
					return GL_LEQUAL;
				case GraphicsAPI::GREATER:
					return GL_GREATER;
				case GraphicsAPI::NOTEQUAL:
					return GL_NOTEQUAL;
				case GraphicsAPI::GEQUAL:
					return GL_GEQUAL;
				default:
					NEVER_HAPPEN; return 0;
				}
			}

#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT 0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3
#define GL_COMPRESSED_RED_GREEN_RGTC2_EXT 0x8DBD
#define GL_COMPRESSED_RED_RGTC1_EXT 0x8DBB

#define GL_COMPRESSED_SRGB_S3TC_DXT1_EXT 0x8C4C
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E
#define	GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F

			// 		https://en.wikipedia.org/wiki/S3_Texture_Compression#BC6H_and_BC7
			//		https://github.com/BinomialLLC/basis_universal/wiki/OpenGL-texture-format-enums-table
			// 		DXT1	BC1	1 - bit Alpha / Opaque	Yes	6:1 (for 24 - bit source image)	Simple non - alpha
			// 		DXT2	BC2	Explicit alpha	Yes	4 : 1	Sharp alpha
			// 		DXT3	BC2	Explicit alpha	No	4 : 1	Sharp alpha
			// 		DXT4	BC3	Interpolated alpha	Yes	4 : 1	Gradient alpha
			// 		DXT5	BC3
			//		N / A	BC4	Interpolated greyscale	N / A	2:1	Gradient
			//		N / A	BC5	Interpolated two - channel	N / A	2 : 1	Gradient

			// 		transcoder_texture_format	GL internal format	GL base internal format
			// 	!!cTFBC1_RGB	GL_COMPRESSED_RGB_S3TC_DXT1_EXT	GL_RGB
			// 	!!cTFBC3_RGBA	GL_COMPRESSED_RGBA_S3TC_DXT5_EXT	GL_RGBA
			// 	!!cTFBC4_R	GL_COMPRESSED_RED_RGTC1_EXT	GL_RED
			// 	!!cTFBC5_RG	GL_COMPRESSED_RED_GREEN_RGTC2_EXT	GL_RG
			// 		cTFETC1_RGB	GL_ETC1_RGB8_OES	GL_RGB
			// 		cTFETC2_RGBA	GL_COMPRESSED_RGBA8_ETC2_EAC	GL_RGBA
			// 		cTFBC7_M6_RGB, cTFBC7_M5_RGBA	GL_COMPRESSED_RGBA_BPTC_UNORM	GL_RGBA
			// 		cTFPVRTC1_4_RGB	GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG	GL_RGB
			// 		cTFPVRTC1_4_RGBA	GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG	GL_RGBA
			// 		cTFASTC_4x4_RGBA	GL_COMPRESSED_RGBA_ASTC_4x4_KHR	GL_RGBA
			// 		cTFATC_RGB	GL_ATC_RGB_AMD	GL_RGB
			// 		cTFATC_RGBA	GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD	GL_RGBA
			// 		cTFETC2_EAC_R11	GL_COMPRESSED_R11_EAC	GL_RED
			// 		cTFETC2_EAC_RG11	GL_COMPRESSED_RG11_EAC	GL_RG
			// 		cTFFXT1_RGB	GL_COMPRESSED_RGB_FXT1_3DFX	GL_RGB
			// 		cTFPVRTC2_4_RGB, cTFPVRTC2_4_RGBA	GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG	GL_RGBA

			FORCE_INLINE static unsigned int GetTextureCompressedInternalFormat(const GraphicsAPI::eTextureCompressedInternalFormat textureCompressedInternalFormat)
			{
				switch (textureCompressedInternalFormat)
				{
				case GraphicsAPI::COMPRESSED_RGB8_ETC2:
					return GL_COMPRESSED_RGB8_ETC2;
				case GraphicsAPI::COMPRESSED_SRGB8_ETC2:
					return GL_COMPRESSED_SRGB8_ETC2;
				case GraphicsAPI::COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
					return GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2;
				case GraphicsAPI::COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
					return GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2;
				case GraphicsAPI::COMPRESSED_RGBA8_ETC2_EAC:
					return GL_COMPRESSED_RGBA8_ETC2_EAC;
				case GraphicsAPI::COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
					return GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC;
				case GraphicsAPI::COMPRESSED_R11_EAC:
					return GL_COMPRESSED_R11_EAC;
				case GraphicsAPI::COMPRESSED_SIGNED_R11_EAC:
					return GL_COMPRESSED_SIGNED_R11_EAC;
				case GraphicsAPI::COMPRESSED_RG11_EAC:
					return GL_COMPRESSED_RG11_EAC;
				case GraphicsAPI::COMPRESSED_SIGNED_RG11_EAC:
					return GL_COMPRESSED_SIGNED_RG11_EAC;
				case GraphicsAPI::COMPRESSED_RGB_S3TC_DXT1_EXT:
					return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
				case GraphicsAPI::COMPRESSED_RGBA_S3TC_DXT1_EXT:
					return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				case GraphicsAPI::COMPRESSED_RGBA_S3TC_DXT3_EXT:
					return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				case GraphicsAPI::COMPRESSED_RGBA_S3TC_DXT5_EXT:
					return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				case GraphicsAPI::COMPRESSED_RED_GREEN_RGTC2_EXT:
					return GL_COMPRESSED_RED_GREEN_RGTC2_EXT;
				case GraphicsAPI::COMPRESSED_RED_RGTC1_EXT:
					return GL_COMPRESSED_RED_RGTC1_EXT;
				case GraphicsAPI::COMPRESSED_SRGB_S3TC_DXT1_EXT:
					return GL_COMPRESSED_SRGB_S3TC_DXT1_EXT;
				case GraphicsAPI::COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT:
					return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
				case GraphicsAPI::COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT:
					return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT;
				case GraphicsAPI::COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:
					return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT;
				default:
					NEVER_HAPPEN; return 0; return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLTextureParameterValue(const GraphicsAPI::eTextureParameterValue textureParameterValue)
			{
				switch (textureParameterValue)
				{
				case GraphicsAPI::IMAGE_INTERPOLATION_NEAREST:
					return GL_NEAREST;
				case GraphicsAPI::IMAGE_INTERPOLATION_LINEAR:
					return GL_LINEAR;
				case GraphicsAPI::NEAREST_MIPMAP_NEAREST:
					return GL_NEAREST_MIPMAP_NEAREST;
				case GraphicsAPI::LINEAR_MIPMAP_NEAREST:
					return GL_LINEAR_MIPMAP_NEAREST;
				case GraphicsAPI::NEAREST_MIPMAP_LINEAR:
					return GL_NEAREST_MIPMAP_LINEAR;
				case GraphicsAPI::LINEAR_MIPMAP_LINEAR:
					return GL_LINEAR_MIPMAP_LINEAR;
				case GraphicsAPI::CLAMP_TO_EDGE:
					return GL_CLAMP_TO_EDGE;
				case GraphicsAPI::CLAMP_TO_BORDER:
					return GL_CLAMP_TO_BORDER;
				case GraphicsAPI::MIRRORED_REPEAT:
					return GL_MIRRORED_REPEAT;
				case GraphicsAPI::REPEAT:
					return GL_REPEAT;
				case GraphicsAPI::MIRROR_CLAMP_TO_EDGE:
					return GL_MIRROR_CLAMP_TO_EDGE;
				default:
					NEVER_HAPPEN; return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLTextureWrapMode(const GraphicsAPI::eWrapMode wrapMode)
			{
				switch (wrapMode)
				{
				case GraphicsAPI::WRAP_MODE_CLAMP_TO_EDGE:
					return GL_CLAMP_TO_EDGE;
				case GraphicsAPI::WRAP_MODE_CLAMP_TO_BORDER:
					return GL_CLAMP_TO_BORDER;
				case GraphicsAPI::WRAP_MODE_MIRRORED_REPEAT:
					return GL_MIRRORED_REPEAT;
				case GraphicsAPI::WRAP_MODE_REPEAT:
					return GL_REPEAT;
				case GraphicsAPI::WRAP_MODE_MIRROR_CLAMP_TO_EDGE:
					return GL_MIRROR_CLAMP_TO_EDGE;
				default:
					NEVER_HAPPEN; return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLTextureFilterMode(const GraphicsAPI::eFilterMode filterMode)
			{
				switch (filterMode)
				{
				case GraphicsAPI::FILTER_MODE_NEAREST:
					return GL_NEAREST;
				case GraphicsAPI::FILTER_MODE_LINEAR:
					return GL_LINEAR;
				case GraphicsAPI::FILTER_MODE_NEAREST_MIPMAP_NEAREST:
					return GL_NEAREST_MIPMAP_NEAREST;
				case GraphicsAPI::FILTER_MODE_LINEAR_MIPMAP_NEAREST:
					return GL_LINEAR_MIPMAP_NEAREST;
				case GraphicsAPI::FILTER_MODE_NEAREST_MIPMAP_LINEAR:
					return GL_NEAREST_MIPMAP_LINEAR;
				case GraphicsAPI::FILTER_MODE_LINEAR_MIPMAP_LINEAR:
					return GL_LINEAR_MIPMAP_LINEAR;
				default:
					NEVER_HAPPEN; return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLTextureComponentFormat(const GraphicsAPI::eTextureComponentFormat textureComponentFormat)
			{
				switch (textureComponentFormat)
				{
				case GraphicsAPI::TEXTURE_COMPONENT_RED:
					return GL_RED;
				case GraphicsAPI::TEXTURE_COMPONENT_RG:
					return GL_RG;
				case GraphicsAPI::TEXTURE_COMPONENT_RGB:
					return GL_RGB;
				case GraphicsAPI::TEXTURE_COMPONENT_BGR:
					return GL_BGR;
				case GraphicsAPI::TEXTURE_COMPONENT_RGBA:
					return GL_RGBA;
				case GraphicsAPI::TEXTURE_COMPONENT_BGRA:
					return GL_BGRA;
				case GraphicsAPI::TEXTURE_COMPONENT_RED_INTEGER:
					return GL_RED_INTEGER;
				case GraphicsAPI::TEXTURE_COMPONENT_RG_INTEGER:
					return GL_RG_INTEGER;
				case GraphicsAPI::TEXTURE_COMPONENT_RGB_INTEGER:
					return GL_RGB_INTEGER;
				case GraphicsAPI::TEXTURE_COMPONENT_BGR_INTEGER:
					return GL_BGR_INTEGER;
				case GraphicsAPI::TEXTURE_COMPONENT_RGBA_INTEGER:
					return GL_RGBA_INTEGER;
				case GraphicsAPI::TEXTURE_COMPONENT_BGRA_INTEGER:
					return GL_BGRA_INTEGER;
				case GraphicsAPI::TEXTURE_COMPONENT_STENCIL_INDEX:
					return GL_STENCIL_INDEX;
				case GraphicsAPI::TEXTURE_COMPONENT_DEPTH_COMPONENT:
					return GL_DEPTH_COMPONENT;
				case GraphicsAPI::TEXTURE_COMPONENT_DEPTH_STENCIL:
					return GL_DEPTH_STENCIL;
				default:
					NEVER_HAPPEN; return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLTextureInternalFormat(const graphics::GraphicsAPI::eTextureInternalFormat textureInternalFormat)
			{
				switch (textureInternalFormat)
				{
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT16:
					return GL_DEPTH_COMPONENT16;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT24:
					return GL_DEPTH_COMPONENT24;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT32:
					return GL_DEPTH_COMPONENT32;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT32F:
					return GL_DEPTH_COMPONENT32F;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH24_STENCIL8:
					return GL_DEPTH24_STENCIL8;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH32F_STENCIL8:
					return GL_DEPTH32F_STENCIL8;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_STENCIL_INDEX:
					return GL_STENCIL_INDEX;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_STENCIL_INDEX8:
					return GL_STENCIL_INDEX8;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RED:
					return GL_RED;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG:
					return GL_RG;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB:
					return GL_RGB;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA:
					return GL_RGBA;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R8:
					return GL_R8;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R8_SNORM:
					return GL_R8_SNORM;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R16:
					return GL_R16;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R16_SNORM:
					return GL_R16_SNORM;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG8:
					return GL_RG8;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG8_SNORM:
					return GL_RG8_SNORM;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG16:
					return GL_RG16;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG16_SNORM:
					return GL_RG16_SNORM;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R3_G3_B2:
					return GL_R3_G3_B2;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB4:
					return GL_RGB4;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB5:
					return GL_RGB5;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB8:
					return GL_RGB8;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB8_SNORM:
					return GL_RGB8_SNORM;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB10:
					return GL_RGB10;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB12:
					return GL_RGB12;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB16_SNORM:
					return GL_RGB16_SNORM;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA2:
					return GL_RGBA2;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA4:
					return GL_RGBA4;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB5_A1:
					return GL_RGB5_A1;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA8:
					return GL_RGBA8;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA8_SNORM:
					return GL_RGBA8_SNORM;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB10_A2:
					return GL_RGB10_A2;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB10_A2UI:
					return GL_RGB10_A2UI;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA12:
					return GL_RGBA12;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA16:
					return GL_RGBA16;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_SRGB8:
					return GL_SRGB8;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_SRGB8_ALPHA8:
					return GL_SRGB8_ALPHA8;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R16F:
					return GL_R16F;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG16F:
					return GL_RG16F;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB16F:
					return GL_RGB16F;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA16F:
					return GL_RGBA16F;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R32F:
					return GL_R32F;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG32F:
					return GL_RG32F;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB32F:
					return GL_RGB32F;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA32F:
					return GL_RGBA32F;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R11F_G11F_B10F:
					return GL_R11F_G11F_B10F;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB9_E5:
					return GL_RGB9_E5;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R8I:
					return GL_R8I;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R8UI:
					return GL_R8UI;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R16I:
					return GL_R16I;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R16UI:
					return GL_R16UI;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R32I:
					return GL_R32I;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_R32UI:
					return GL_R32UI;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG8I:
					return GL_RG8I;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG8UI:
					return GL_RG8UI;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG16I:
					return GL_RG16I;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG16UI:
					return GL_RG16UI;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG32I:
					return GL_RG32I;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RG32UI:
					return GL_RG32UI;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB8I:
					return GL_RGB8I;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB8UI:
					return GL_RGB8UI;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB16I:
					return GL_RGB16I;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB16UI:
					return GL_RGB16UI;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB32I:
					return GL_RGB32I;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGB32UI:
					return GL_RGB32UI;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA8I:
					return GL_RGBA8I;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA8UI:
					return GL_RGBA8UI;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA16I:
					return GL_RGBA16I;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA16UI:
					return GL_RGBA16UI;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA32I:
					return GL_RGBA32I;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_RGBA32UI:
					return GL_RGBA32UI;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RED:
					return GL_COMPRESSED_RED;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RG:
					return GL_COMPRESSED_RG;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGB:
					return GL_COMPRESSED_RGB;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGBA:
					return GL_COMPRESSED_RGBA;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_SRGB:
					return GL_COMPRESSED_SRGB;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_SRGB_ALPHA:
					return GL_COMPRESSED_SRGB_ALPHA;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RED_RGTC1:
					return GL_COMPRESSED_RED_RGTC1;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_SIGNED_RED_RGTC1:
					return GL_COMPRESSED_SIGNED_RED_RGTC1;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RG_RGTC2:
					return GL_COMPRESSED_RG_RGTC2;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_SIGNED_RG_RGTC2:
					return GL_COMPRESSED_SIGNED_RG_RGTC2;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGBA_BPTC_UNORM:
					return GL_COMPRESSED_RGBA_BPTC_UNORM;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_SRGB_ALPHA_BPTC_UNORM:
					return GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGB_BPTC_SIGNED_FLOAT:
					return GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT:
					return GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT;
				default:
					NEVER_HAPPEN; return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLBufferTarget(const GraphicsAPI::eBufferTarget bufferTarget)
			{
				switch (bufferTarget)
				{
				case GraphicsAPI::eBufferTarget::ARRAY_BUFFER:
					return GL_ARRAY_BUFFER;

				case GraphicsAPI::eBufferTarget::ELEMENT_ARRAY_BUFFER:
					return GL_ELEMENT_ARRAY_BUFFER;

				case GraphicsAPI::eBufferTarget::TEXTURE_BUFFER:
					return GL_TEXTURE_BUFFER;

				case GraphicsAPI::DRAW_INDIRECT_BUFFER:
					return GL_DRAW_INDIRECT_BUFFER;

				case GraphicsAPI::UNIFORM_BUFFER:
					return GL_UNIFORM_BUFFER;

				default:
					NEVER_HAPPEN;
					return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLBufferBitType(const GraphicsAPI::eBufferBitType bufferType)
			{
				unsigned int bufferBitType = 0;

				if ((GraphicsAPI::COLOR_BUFFER & bufferType) != 0)
				{
					bufferBitType |= GL_COLOR_BUFFER_BIT;
				}

				if ((GraphicsAPI::DEPTH_BUFFER & bufferType) != 0)
				{
					bufferBitType |= GL_DEPTH_BUFFER_BIT;
				}

				if ((GraphicsAPI::STENCIL_BUFFER & bufferType) != 0)
				{
					bufferBitType |= GL_STENCIL_BUFFER_BIT;
				}

				if ((GraphicsAPI::DEPTH_STENCIL_BUFFER & bufferType) != 0)
				{
					bufferBitType |= (GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				}

				return bufferBitType;
			}

			FORCE_INLINE static unsigned int GetGLBufferBitType(const unsigned int bufferTypeBits)
			{
				unsigned int bufferBitType = 0;
				if ((bufferTypeBits & GraphicsAPI::COLOR_BUFFER) != 0)
				{
					bufferBitType |= GL_COLOR_BUFFER_BIT;
				}
				if ((bufferTypeBits & GraphicsAPI::DEPTH_BUFFER) != 0)
				{
					bufferBitType |= GL_DEPTH_BUFFER_BIT;
				}
				if ((bufferTypeBits & GraphicsAPI::DEPTH_STENCIL_BUFFER) != 0)
				{
					bufferBitType |= GL_STENCIL_BUFFER_BIT;
				}
				return bufferBitType;
			}

			FORCE_INLINE static unsigned int GetGLBufferType(const GraphicsAPI::eBufferType bufferType)
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
					NEVER_HAPPEN; return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLBufferMode(const GraphicsAPI::eBufferMode bufferMode)
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
				case GraphicsAPI::COLOR_ATTACHMENT11:
					return GL_COLOR_ATTACHMENT11;
				case GraphicsAPI::COLOR_ATTACHMENT12:
					return GL_COLOR_ATTACHMENT12;
				case GraphicsAPI::COLOR_ATTACHMENT13:
					return GL_COLOR_ATTACHMENT13;
				case GraphicsAPI::COLOR_ATTACHMENT14:
					return GL_COLOR_ATTACHMENT14;
				case GraphicsAPI::COLOR_ATTACHMENT15:
					return GL_COLOR_ATTACHMENT15;
				case GraphicsAPI::COLOR_ATTACHMENT16:
					return GL_COLOR_ATTACHMENT16;
				case GraphicsAPI::COLOR_ATTACHMENT17:
					return GL_COLOR_ATTACHMENT17;
				case GraphicsAPI::COLOR_ATTACHMENT18:
					return GL_COLOR_ATTACHMENT18;
				case GraphicsAPI::COLOR_ATTACHMENT19:
					return GL_COLOR_ATTACHMENT19;
				case GraphicsAPI::COLOR_ATTACHMENT20:
					return GL_COLOR_ATTACHMENT20;
				case GraphicsAPI::COLOR_ATTACHMENT21:
					return GL_COLOR_ATTACHMENT21;
				case GraphicsAPI::COLOR_ATTACHMENT22:
					return GL_COLOR_ATTACHMENT22;
				case GraphicsAPI::COLOR_ATTACHMENT23:
					return GL_COLOR_ATTACHMENT23;
				case GraphicsAPI::COLOR_ATTACHMENT24:
					return GL_COLOR_ATTACHMENT24;
				case GraphicsAPI::COLOR_ATTACHMENT25:
					return GL_COLOR_ATTACHMENT25;
				case GraphicsAPI::COLOR_ATTACHMENT26:
					return GL_COLOR_ATTACHMENT26;
				case GraphicsAPI::COLOR_ATTACHMENT27:
					return GL_COLOR_ATTACHMENT27;
				case GraphicsAPI::COLOR_ATTACHMENT28:
					return GL_COLOR_ATTACHMENT28;
				case GraphicsAPI::COLOR_ATTACHMENT29:
					return GL_COLOR_ATTACHMENT29;
				case GraphicsAPI::COLOR_ATTACHMENT30:
					return GL_COLOR_ATTACHMENT30;
				case GraphicsAPI::COLOR_ATTACHMENT31:
					return GL_COLOR_ATTACHMENT31;
				case GraphicsAPI::BUFFER_MODE_NONE:
					return GL_NONE;
				default:
					NEVER_HAPPEN; return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLShaderType(const GraphicsAPI::eGraphicsPipeLineStage shaderType)
			{
				switch (shaderType)
				{
				case GraphicsAPI::eGraphicsPipeLineStage::VERTEX_SHADER:
					return GL_VERTEX_SHADER;
				case GraphicsAPI::eGraphicsPipeLineStage::PIXEL_SHADER:
					return GL_FRAGMENT_SHADER;
				case GraphicsAPI::eGraphicsPipeLineStage::GEOMETRY_SHADER:
					return GL_GEOMETRY_SHADER;
				case GraphicsAPI::eGraphicsPipeLineStage::COMPUTE_SHADER:
					return GL_COMPUTE_SHADER;
				default:
					NEVER_HAPPEN;
					return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLTextureBindTarget(const GraphicsAPI::eTextureBindTarget textureBindTarget)
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
				case GraphicsAPI::_TEXTURE_BUFFER:
					return GL_TEXTURE_BUFFER;
				case GraphicsAPI::TEXTURE_CUBE_MAP_ARRAY:
					return GL_TEXTURE_CUBE_MAP_ARRAY;
				case GraphicsAPI::TEXTURE_2D_MULTISAMPLE:
					return GL_TEXTURE_2D_MULTISAMPLE;
				case GraphicsAPI::TEXTURE_2D_MULTISAMPLE_ARRAY:
					return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
				default:
					NEVER_HAPPEN; return 0;

				}
			}

			FORCE_INLINE static unsigned int GetGLMapBufferAccessOption(const GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption)
			{
				switch (mapBufferAccessOption)
				{
				case GraphicsAPI::READ_ONLY:
					return GL_READ_ONLY;

				case GraphicsAPI::WRITE_ONLY:
					return GL_WRITE_ONLY;

				case GraphicsAPI::READ_WRITE:
					return GL_READ_WRITE;

				default:
					NEVER_HAPPEN; return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLTextureMataDataType(const GraphicsAPI::eTextureMetaDataType textureMetaDataType)
			{
				switch (textureMetaDataType)
				{
				case GraphicsAPI::TEXTURE_WIDTH:
					return GL_TEXTURE_WIDTH;
				case GraphicsAPI::TEXTURE_HEIGHT:
					return GL_TEXTURE_HEIGHT;
				case GraphicsAPI::TEXTURE_DEPTH:
					return GL_TEXTURE_DEPTH;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT:
					return GL_TEXTURE_INTERNAL_FORMAT;
				case GraphicsAPI::TEXTURE_RED_SIZE:
					return GL_TEXTURE_RED_SIZE;
				case GraphicsAPI::TEXTURE_GREEN_SIZE:
					return GL_TEXTURE_GREEN_SIZE;
				case GraphicsAPI::TEXTURE_BLUE_SIZE:
					return GL_TEXTURE_BLUE_SIZE;
				case GraphicsAPI::TEXTURE_ALPHA_SIZE:
					return GL_TEXTURE_ALPHA_SIZE;
				case GraphicsAPI::TEXTURE_DEPTH_SIZE:
					return GL_TEXTURE_DEPTH_SIZE;
				case GraphicsAPI::TEXTURE_COMPRESSED:
					return GL_TEXTURE_COMPRESSED;
				case GraphicsAPI::TEXTURE_COMPRESSED_IMAGE_SIZE:
					return GL_TEXTURE_COMPRESSED_IMAGE_SIZE;
				case GraphicsAPI::TEXTURE_BUFFER_OFFSET:
					return GL_TEXTURE_BUFFER_OFFSET;
				case GraphicsAPI::TEXTURE_BUFFER_SIZE:
					return GL_TEXTURE_BUFFER_SIZE;
				default:
					NEVER_HAPPEN; return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLTextureParameterType(const GraphicsAPI::eTextureParameterType textureParameterType)
			{
				switch (textureParameterType)
				{
				case GraphicsAPI::DEPTH_STENCIL_TEXTURE_MODE:
					return GL_DEPTH_STENCIL_TEXTURE_MODE;
				case GraphicsAPI::TEXTURE_BASE_LEVEL:
					return GL_TEXTURE_BASE_LEVEL;
				case GraphicsAPI::TEXTURE_COMPARE_FUNC:
					return GL_TEXTURE_COMPARE_FUNC;
				case GraphicsAPI::TEXTURE_COMPARE_MODE:
					return GL_TEXTURE_COMPARE_MODE;
				case GraphicsAPI::TEXTURE_LOD_BIAS:
					return GL_TEXTURE_LOD_BIAS;
				case GraphicsAPI::TEXTURE_MIN_FILTER:
					return GL_TEXTURE_MIN_FILTER;
				case GraphicsAPI::TEXTURE_MAG_FILTER:
					return GL_TEXTURE_MAG_FILTER;
				case GraphicsAPI::TEXTURE_MIN_LOD:
					return GL_TEXTURE_MIN_LOD;
				case GraphicsAPI::TEXTURE_MAX_LOD:
					return GL_TEXTURE_MAX_LOD;
				case GraphicsAPI::TEXTURE_MAX_LEVEL:
					return GL_TEXTURE_MAX_LEVEL;
				case GraphicsAPI::TEXTURE_SWIZZLE_R:
					return GL_TEXTURE_SWIZZLE_R;
				case GraphicsAPI::TEXTURE_SWIZZLE_G:
					return GL_TEXTURE_SWIZZLE_G;
				case GraphicsAPI::TEXTURE_SWIZZLE_B:
					return GL_TEXTURE_SWIZZLE_B;
				case GraphicsAPI::TEXTURE_SWIZZLE_A:
					return GL_TEXTURE_SWIZZLE_A;
				case GraphicsAPI::TEXTURE_WRAP_S:
					return GL_TEXTURE_WRAP_S;
				case GraphicsAPI::TEXTURE_WRAP_T:
					return GL_TEXTURE_WRAP_T;
				case GraphicsAPI::TEXTURE_WRAP_R:
					return GL_TEXTURE_WRAP_R;
				default:
					NEVER_HAPPEN; return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLTargetTexture(const GraphicsAPI::eTargetTexture targetTexture)
			{
				switch (targetTexture)
				{
				case GraphicsAPI::TARGET_TEXTURE_TEXTURE_1D:
					return GL_TEXTURE_1D;
				case GraphicsAPI::TARGET_TEXTURE_PROXY_TEXTURE_1D:
					return GL_PROXY_TEXTURE_1D;
				case GraphicsAPI::TARGET_TEXTURE_TEXTURE_2D:
					return GL_TEXTURE_2D;
				case GraphicsAPI::TARGET_TEXTURE_PROXY_TEXTURE_2D:
					return GL_PROXY_TEXTURE_2D;
				case GraphicsAPI::TARGET_TEXTURE_TEXTURE_1D_ARRAY:
					return GL_TEXTURE_1D_ARRAY;
				case GraphicsAPI::TARGET_TEXTURE_PROXY_TEXTURE_1D_ARRAY:
					return GL_PROXY_TEXTURE_1D_ARRAY;
				case GraphicsAPI::TARGET_TEXTURE_TEXTURE_RECTANGLE:
					return GL_TEXTURE_RECTANGLE;
				case GraphicsAPI::TARGET_TEXTURE_PROXY_TEXTURE_RECTANGLE:
					return GL_PROXY_TEXTURE_RECTANGLE;
				case GraphicsAPI::TARGET_TEXTURE_TEXTURE_CUBE_MAP_POSITIVE_X:
					return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
				case GraphicsAPI::TARGET_TEXTURE_TEXTURE_CUBE_MAP_NEGATIVE_X:
					return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
				case GraphicsAPI::TARGET_TEXTURE_TEXTURE_CUBE_MAP_POSITIVE_Y:
					return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
				case GraphicsAPI::TARGET_TEXTURE_TEXTURE_CUBE_MAP_NEGATIVE_Y:
					return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
				case GraphicsAPI::TARGET_TEXTURE_TEXTURE_CUBE_MAP_POSITIVE_Z:
					return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
				case GraphicsAPI::TARGET_TEXTURE_TEXTURE_CUBE_MAP_NEGATIVE_Z:
					return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
				case GraphicsAPI::TARGET_TEXTURE_PROXY_TEXTURE_CUBE_MAP:
					return GL_PROXY_TEXTURE_CUBE_MAP;
				case GraphicsAPI::TARGET_TEXTURE_TEXTURE_3D:
					return GL_TEXTURE_3D;
				default:
					NEVER_HAPPEN; return 0;
				}
			}



			FORCE_INLINE static unsigned int GetGLDataType(const GraphicsAPI::eDataType dataType)
			{
				switch (dataType)
				{
				case GraphicsAPI::UNSIGNED_BYTE:
					return GL_UNSIGNED_BYTE;
				case GraphicsAPI::BYTE:
					return GL_BYTE;
				case GraphicsAPI::UNSIGNED_SHORT:
					return GL_UNSIGNED_SHORT;
				case GraphicsAPI::SHORT:
					return GL_SHORT;
				case GraphicsAPI::UNSIGNED_INT:
					return GL_UNSIGNED_INT;
				case GraphicsAPI::INT:
					return GL_INT;
				case GraphicsAPI::HALF_FLOAT:
					return GL_HALF_FLOAT;
				case GraphicsAPI::FLOAT:
					return GL_FLOAT;
				case GraphicsAPI::UNSIGNED_BYTE_3_3_2:
					return GL_UNSIGNED_BYTE_3_3_2;
				case GraphicsAPI::UNSIGNED_BYTE_2_3_3_REV:
					return GL_UNSIGNED_BYTE_2_3_3_REV;
				case GraphicsAPI::UNSIGNED_SHORT_5_6_5:
					return GL_UNSIGNED_SHORT_5_6_5;
				case GraphicsAPI::UNSIGNED_SHORT_5_6_5_REV:
					return GL_UNSIGNED_SHORT_5_6_5_REV;
				case GraphicsAPI::UNSIGNED_SHORT_4_4_4_4:
					return GL_UNSIGNED_SHORT_4_4_4_4;
				case GraphicsAPI::UNSIGNED_SHORT_4_4_4_4_REV:
					return GL_UNSIGNED_SHORT_4_4_4_4_REV;
				case GraphicsAPI::UNSIGNED_SHORT_5_5_5_1:
					return GL_UNSIGNED_SHORT_5_5_5_1;
				case GraphicsAPI::UNSIGNED_SHORT_1_5_5_5_REV:
					return GL_UNSIGNED_SHORT_1_5_5_5_REV;
				case GraphicsAPI::UNSIGNED_INT_8_8_8_8:
					return GL_UNSIGNED_INT_8_8_8_8;
				case GraphicsAPI::UNSIGNED_INT_8_8_8_8_REV:
					return GL_UNSIGNED_INT_8_8_8_8_REV;
				case GraphicsAPI::UNSIGNED_INT_10_10_10_2:
					return GL_UNSIGNED_INT_10_10_10_2;
				case GraphicsAPI::UNSIGNED_INT_2_10_10_10_REV:
					return GL_UNSIGNED_INT_2_10_10_10_REV;
				case GraphicsAPI::UNSIGNED_INT_24_8:
					return GL_UNSIGNED_INT_24_8;
				case GraphicsAPI::FLOAT_32_UNSIGNED_INT_24_8_REV:
					return GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
				default:
					NEVER_HAPPEN; return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLBlendFactor(const graphics::GraphicsAPI::eBlendFactor blendFactor)
			{
				switch (blendFactor)
				{
				case GraphicsAPI::eBlendFactor::ZERO:
					return GL_ZERO;
				case GraphicsAPI::eBlendFactor::ONE:
					return GL_ONE;
				case GraphicsAPI::eBlendFactor::SRC_COLOR:
					return GL_SRC_COLOR;
				case GraphicsAPI::eBlendFactor::ONE_MINUS_SRC_COLOR:
					return GL_ONE_MINUS_SRC_COLOR;
				case GraphicsAPI::eBlendFactor::DST_COLOR:
					return GL_DST_COLOR;
				case GraphicsAPI::eBlendFactor::ONE_MINUS_DST_COLOR:
					return GL_ONE_MINUS_DST_COLOR;
				case GraphicsAPI::eBlendFactor::SRC_ALPHA:
					return GL_SRC_ALPHA;
				case GraphicsAPI::eBlendFactor::ONE_MINUS_SRC_ALPHA:
					return GL_ONE_MINUS_SRC_ALPHA;
				case GraphicsAPI::eBlendFactor::DST_ALPHA:
					return GL_DST_ALPHA;
				case GraphicsAPI::eBlendFactor::ONE_MINUS_DST_ALPHA:
					return GL_ONE_MINUS_DST_ALPHA;
				case GraphicsAPI::eBlendFactor::CONSTANT_COLOR:
					return GL_CONSTANT_COLOR;
				case GraphicsAPI::eBlendFactor::ONE_MINUS_CONSTANT_COLOR:
					return GL_ONE_MINUS_CONSTANT_COLOR;
				case GraphicsAPI::eBlendFactor::CONSTANT_ALPHA:
					return GL_CONSTANT_ALPHA;
				case GraphicsAPI::eBlendFactor::ONE_MINUS_CONSTANT_ALPHA:
					return GL_ONE_MINUS_CONSTANT_ALPHA;
				default:
					NEVER_HAPPEN; return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLWinding(const GraphicsAPI::eWinding winding)
			{
				switch (winding)
				{
				case GraphicsAPI::CW:
					return GL_CW;
				case GraphicsAPI::CCW:
					return GL_CCW;
				default:
					NEVER_HAPPEN; return 0;
				}
			}

			FORCE_INLINE static unsigned int GetGLImageInterpolation(const GraphicsAPI::eImageInterpolation imageInterpolation)
			{
				switch (imageInterpolation)
				{
				case GraphicsAPI::eImageInterpolation::IMAGE_INTERPOLATION_NEAREST:
					return GL_NEAREST;
				case GraphicsAPI::eImageInterpolation::IMAGE_INTERPOLATION_LINEAR:
					return GL_LINEAR;
				default:
					NEVER_HAPPEN;
					return 0;
				}
			}


			FORCE_INLINE static unsigned int GetGLFrameBufferAttachmentPoint(const GraphicsAPI::eFrameBufferAttachmentPoint frameBufferAttachmentPoint)
			{
				switch (frameBufferAttachmentPoint)
				{
				case GraphicsAPI::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT0:
					return GL_COLOR_ATTACHMENT0;
				case GraphicsAPI::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT1:
					return GL_COLOR_ATTACHMENT1;
				case GraphicsAPI::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT2:
					return GL_COLOR_ATTACHMENT2;
				case GraphicsAPI::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT3:
					return GL_COLOR_ATTACHMENT3;
				case GraphicsAPI::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT4:
					return GL_COLOR_ATTACHMENT4;
				case GraphicsAPI::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT5:
					return GL_COLOR_ATTACHMENT5;
				case GraphicsAPI::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT6:
					return GL_COLOR_ATTACHMENT6;
				case GraphicsAPI::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT7:
					return GL_COLOR_ATTACHMENT7;
				case GraphicsAPI::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT8:
					return GL_COLOR_ATTACHMENT8;
				case GraphicsAPI::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT9:
					return GL_COLOR_ATTACHMENT9;
				case GraphicsAPI::FRAMEBUFFER_ATTACHMENT_POINT_COLOR_ATTACHMENT10:
					return GL_COLOR_ATTACHMENT10;
				case GraphicsAPI::FRAMEBUFFER_ATTACHMENT_POINT_DEPTH_ATTACHMENT:
					return GL_DEPTH_ATTACHMENT;
				case GraphicsAPI::FRAMEBUFFER_ATTACHMENT_POINT_STENCIL_ATTACHMENT:
					return GL_STENCIL_ATTACHMENT;
				case GraphicsAPI::FRAMEBUFFER_ATTACHMENT_POINT_DEPTH_STENCIL_ATTACHMENT:
					return GL_DEPTH_STENCIL_ATTACHMENT;
				default:
					NEVER_HAPPEN;
					return 0;
				}
			}


			FORCE_INLINE static unsigned int ConvertStencilOptionToGLStencilOption(const GraphicsAPI::eStencilOption stencilOption)
			{
				switch (stencilOption)
				{
				case GraphicsAPI::eStencilOption::KEEP:
					return GL_KEEP;
				case GraphicsAPI::eStencilOption::STENCIL_OPTION_ZERO:
					return GL_ZERO;
				case GraphicsAPI::eStencilOption::REPLACE:
					return GL_REPLACE;
				case GraphicsAPI::eStencilOption::INCR:
					return GL_INCR;
				case GraphicsAPI::eStencilOption::INCR_WRAP:
					return GL_INCR_WRAP;
				case GraphicsAPI::eStencilOption::DECR:
					return GL_DECR;
				case GraphicsAPI::eStencilOption::DECR_WRAP:
					return GL_DECR_WRAP;
				case GraphicsAPI::eStencilOption::INVERT:
					return GL_INVERT;
				default:
					NEVER_HAPPEN;
				}
			}

			static GLFWwindow* glfwWindow = nullptr;

			static void DEBUG_CALLBACK
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
				if (id == 131218) // NVIDIA: "shader will be recompiled due to GL state mismatches"
				{
					return; // https://stackoverflow.com/questions/12004396/opengl-debug-context-performance-warning
				}

				dooms::graphics::GraphicsAPI::eGraphisAPIDebugCallbackSeverity debugCallbackseverity;
				if (severity == 0x9146)
				{
					debugCallbackseverity = dooms::graphics::GraphicsAPI::eGraphisAPIDebugCallbackSeverity::HIGH;
				}
				else if (severity == 0x9147)
				{
					debugCallbackseverity = dooms::graphics::GraphicsAPI::eGraphisAPIDebugCallbackSeverity::MEDIUM;
				}
				else if (severity == 0x9148)
				{
					debugCallbackseverity = dooms::graphics::GraphicsAPI::eGraphisAPIDebugCallbackSeverity::LOW;
				}
				else if (severity == 0x826B)
				{
					debugCallbackseverity = dooms::graphics::GraphicsAPI::eGraphisAPIDebugCallbackSeverity::NOTIFICATION;
				}
				else
				{
					assert(false);
				}

				//https://www.khronos.org/registry/OpenGL/extensions/KHR/KHR_debug.txt
				(opengl::mDEBUG_FUNCTION)(msg, debugCallbackseverity);

			}
		}

		DOOMS_ENGINE_GRAPHICS_API GraphicsAPI::eGraphicsAPIType GetCuurentAPIType()
		{
			return GraphicsAPI::eGraphicsAPIType::OpenGL;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned int GetDrawCall()
		{
			return opengl::DrawCallCounter;
		}

		DOOMS_ENGINE_GRAPHICS_API void SetDebugFunction(GraphicsAPI::DEBUG_FUNCTION debugFunction)
		{
			opengl::mDEBUG_FUNCTION = debugFunction;
		}

		DOOMS_ENGINE_GRAPHICS_API GraphicsAPI::DEBUG_FUNCTION GetDebugFunction()
		{
			return opengl::mDEBUG_FUNCTION;
		}

		DOOMS_ENGINE_GRAPHICS_API const char* GetPlatformVersion()
		{
			return opengl::OpenGLVersion.c_str();
		}

		DOOMS_ENGINE_GRAPHICS_API void* GetPlatformWindow()
		{
			return dooms::graphics::opengl::glfwWindow;
		}


		/**
		 * \brief
		 * \return elapsed time since GLFW was initilized
		 */
		DOOMS_ENGINE_GRAPHICS_API double GetTime()
		{
			return glfwGetTime();
		}

		DOOMS_ENGINE_GRAPHICS_API GraphicsAPI::eGraphicsAPIType GetCurrentAPIType()
		{
			return GraphicsAPI::eGraphicsAPIType::OpenGL;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned int InitializeGraphicsAPI(const int screenWidth, const int screenHeight, const unsigned int multiSamplingNum)
		{
			glfwInit();
			const char* glsl_version = "#version 150";
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION); // 4.5 -> MAJOR 4  MINOR 5 , 3.1 -> MAJOR 3  MINOR 1
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);

#ifdef _DEBUG
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

			if (multiSamplingNum > 0)
			{
				glfwWindowHint(GLFW_SAMPLES, multiSamplingNum);
			}

#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif



			// glfw window creation
			// --------------------
			assert(screenWidth != 0 && screenHeight != 0);

			dooms::graphics::opengl::glfwWindow = glfwCreateWindow(screenWidth, screenHeight, "SUNG JIN KANG ( hour30000@gmail.com, https://github.com/SungJJinKang )", NULL, NULL);
			if (dooms::graphics::opengl::glfwWindow == NULL)
			{
				assert(0); // "Failed to create GLFW window"
				glfwTerminate();
				return 0;
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
				return 0;
			}

#ifdef _DEBUG
			std::string vendor{ reinterpret_cast<const char*>(glGetString(static_cast<const unsigned int>(dooms::graphics::opengl::GetStringParameter::VENDOR))) };
			if (vendor.find("ATI") != std::string::npos)
			{
				std::printf("Using AMD on board GPU, Maybe This will make driver error");
				assert(0);
				return 0;
			}

			std::printf("Current OpenGL version is : %s", glGetString(static_cast<const unsigned int>(dooms::graphics::opengl::GetStringParameter::VERSION)));
			std::printf("Vendor is : %s", vendor.c_str());
			std::printf("Renderer is : %s", glGetString(static_cast<const unsigned int>(dooms::graphics::opengl::GetStringParameter::VERSION)));
#endif // 

			//

			glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
			glDisable(GL_SAMPLE_ALPHA_TO_ONE);


#ifdef _DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(dooms::graphics::opengl::DEBUG_CALLBACK, NULL);
#endif

			int maxTextureUnitCount{ 0 };
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnitCount);
			assert(maxTextureUnitCount != 0);

			opengl::OpenGLVersion = glsl_version;

			return 1;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned int DeinitializeGraphicsAPI()
		{
			if (dooms::graphics::opengl::glfwWindow != nullptr)
			{
				glfwDestroyWindow(dooms::graphics::opengl::glfwWindow);
			}
			glfwTerminate();
			return 1;
		}

		DOOMS_ENGINE_GRAPHICS_API void SwapBuffer()
		{
			assert(dooms::graphics::opengl::glfwWindow != nullptr);
			glfwSwapBuffers(dooms::graphics::opengl::glfwWindow);
			opengl::DrawCallCounter = 0;
		}



		DOOMS_ENGINE_GRAPHICS_API void SetVSync(const bool isEnabled)
		{
			glfwSwapInterval(isEnabled == true ? 1 : 0);
		}

		DOOMS_ENGINE_GRAPHICS_API void SetIsDepthTestEnabled(const bool isEnabled)
		{
			if (isEnabled == true)
			{
				glEnable(GL_DEPTH_TEST);
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
			}
		}

		DOOMS_ENGINE_GRAPHICS_API void SetIsStencilTestEnabled(const bool isEnabled)
		{
			if (isEnabled == true)
			{
				glEnable(GL_STENCIL_TEST);
			}
			else
			{
				glDisable(GL_STENCIL_TEST);
			}
		}

		DOOMS_ENGINE_GRAPHICS_API void SetIsStencilFunc
		(
			const GraphicsAPI::eTestFuncType testFuncType,
			const int ref,
			const unsigned int mask
		)
		{
			glStencilFunc(graphics::opengl::GetGLTestFuncType(testFuncType), ref, mask);
		}

		DOOMS_ENGINE_GRAPHICS_API void SetIsStencilOp
		(
			const GraphicsAPI::eStencilOption stencilFailOption,
			const GraphicsAPI::eStencilOption actionWhenStencilTestPass_And_DepthTestFail,
			const GraphicsAPI::eStencilOption actionWhenStencilTestPass_And_DepthTestPass
		)
		{
			glStencilOp(graphics::opengl::ConvertStencilOptionToGLStencilOption(stencilFailOption), graphics::opengl::ConvertStencilOptionToGLStencilOption(actionWhenStencilTestPass_And_DepthTestFail), graphics::opengl::ConvertStencilOptionToGLStencilOption(actionWhenStencilTestPass_And_DepthTestPass));
		}

		DOOMS_ENGINE_GRAPHICS_API void SetDepthFunc(const GraphicsAPI::eTestFuncType depthFuncType)
		{
			glDepthFunc(opengl::GetGLTestFuncType(depthFuncType));
		}

		DOOMS_ENGINE_GRAPHICS_API void SetDepthMask(const bool isWriteDepthBuffer)
		{
			glDepthMask(isWriteDepthBuffer);
		}

		DOOMS_ENGINE_GRAPHICS_API void SetIsAlphaTestEnabled(const bool isEnabled)
		{
			if (isEnabled == true)
			{
				glEnable(GL_ALPHA_TEST);
			}
			else
			{
				glDisable(GL_ALPHA_TEST);
			}

		}

		DOOMS_ENGINE_GRAPHICS_API void SetIsBlendEnabled(const bool isEnabled)
		{
			if (isEnabled == true)
			{
				glEnable(GL_BLEND);
			}
			else
			{
				glDisable(GL_BLEND);
			}
		}

		DOOMS_ENGINE_GRAPHICS_API void SetViewport(const unsigned int index, const int startX, const int startY, const unsigned int width, const unsigned int height)
		{
			glViewportIndexedf(index, (float)startX, (float)startY, (float)width, (float)height);
		}

		DOOMS_ENGINE_GRAPHICS_API bool GetViewPort(const unsigned int index, int* const startX, int* const startY, int* const width, int* const height)
		{
			int viewPortData[4];
			glGetIntegeri_v(GL_VIEWPORT, index, viewPortData);
			*startX = viewPortData[0];
			*startY = viewPortData[1];
			*width = viewPortData[2];
			*height = viewPortData[3];

			return true;
		}

		DOOMS_ENGINE_GRAPHICS_API void SetBlendFactor
		(
			const GraphicsAPI::eBlendFactor sourceBlendFactor,
			const GraphicsAPI::eBlendFactor destinationBlendFactor
		)
		{
			glBlendFunc(opengl::GetGLBlendFactor(sourceBlendFactor), opengl::GetGLBlendFactor(destinationBlendFactor));
		}

		DOOMS_ENGINE_GRAPHICS_API void SetCullFace(const GraphicsAPI::eCullFace cullFace)
		{
			glEnable(GL_CULL_FACE);
			switch (cullFace)
			{
			case GraphicsAPI::CULLFACE_FRONT:
				glCullFace(GL_FRONT);
				break;

			case GraphicsAPI::CULLFACE_BACK:
				glCullFace(GL_BACK);
				break;

			case GraphicsAPI::CULLFACE_FRONT_AND_BACK:
				glCullFace(GL_FRONT_AND_BACK);
				break;

			default:
				NEVER_HAPPEN;
			}
		}

		DOOMS_ENGINE_GRAPHICS_API void SetFrontFaceWinding(const GraphicsAPI::eWinding winding)
		{
			glFrontFace(opengl::GetGLWinding(winding));
		}

		/*
		DOOMS_ENGINE_GRAPHICS_API void SetDrawBuffer(const GraphicsAPI::eBufferMode bufferMode)
		{
			glDrawBuffer(opengl::GetGLBufferMode(bufferMode));
		}

		DOOMS_ENGINE_GRAPHICS_API void SetDrawBuffers
		(
			const unsigned int count,
			const GraphicsAPI::eBufferMode* bufferModes
		)
		{
			unsigned int glBufferModes[35];
			for (unsigned int i = 0; i < count; i++)
			{
				glBufferModes[i] = opengl::GetGLBufferMode(bufferModes[i]);
			}
			glDrawBuffers(count, glBufferModes);
		}

		DOOMS_ENGINE_GRAPHICS_API void SetReadBuffer(const GraphicsAPI::eBufferMode bufferMode)
		{
			glReadBuffer(opengl::GetGLBufferMode(bufferMode));
		}
		*/

		DOOMS_ENGINE_GRAPHICS_API void ClearSpecificBuffer
		(
			const GraphicsAPI::eBufferType bufferType,
			const unsigned int drawBufferIndex,
			const float r, const float g, const float b, const float a
		)
		{
			float color[4] = { r, g, b, a };
			glClearBufferfv(opengl::GetGLBufferType(bufferType), drawBufferIndex, color);
		}

		DOOMS_ENGINE_GRAPHICS_API void DestroyBuffer(unsigned long long bufferID)
		{
			glDeleteBuffers(1, reinterpret_cast<unsigned int*>(&bufferID));
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned long long CreateVertexArrayObject()
		{
			unsigned long long bufferID;
			glGenVertexArrays(1, reinterpret_cast<unsigned int*>(&bufferID));
			return bufferID;
		}

		DOOMS_ENGINE_GRAPHICS_API void DestroyVertexArrayObject(unsigned long long vertexArrayObject)
		{
			glDeleteVertexArrays(1, reinterpret_cast<unsigned int*>(&vertexArrayObject));
		}

		DOOMS_ENGINE_GRAPHICS_API bool CompileShader
		(
			unsigned long long& shaderObject,
			const GraphicsAPI::eGraphicsPipeLineStage shaderType,
			const char* const shaderText,
			const unsigned long long shaderTextSize
		)
		{
			assert(shaderObject != 0);

			glShaderSource(shaderObject, 1, &shaderText, NULL);
			glCompileShader(shaderObject);

			int isSucess;
			glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &isSucess);

			return (isSucess == GL_TRUE);
		}

		DOOMS_ENGINE_GRAPHICS_API void BindVertexArrayObject(const unsigned long long vertexArrayObject)
		{
			assert(vertexArrayObject != 0);
			glBindVertexArray(vertexArrayObject);
		}

		DOOMS_ENGINE_GRAPHICS_API void BindVertexDataBuffer
		(
			const unsigned long long bufferObject,
			const unsigned int bindingPosition,
			const unsigned int stride,
			const unsigned int offset
		)
		{
			glBindBuffer(GL_ARRAY_BUFFER, bufferObject);
		}

		DOOMS_ENGINE_GRAPHICS_API void BindBuffer
		(
			const unsigned long long bufferObject,
			const unsigned int bindingPosition,
			const GraphicsAPI::eBufferTarget bindBufferTarget,
			const GraphicsAPI::eGraphicsPipeLineStage targetPipeLienStage
		)
		{
			glBindBuffer(opengl::GetGLBufferTarget(bindBufferTarget), bufferObject);
		}

		DOOMS_ENGINE_GRAPHICS_API void BindIndexBufferObject
		(
			const unsigned long long indexBufferObject//, 
			//const unsigned long long offset
		)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned long long CreateBufferObject
		(
			const GraphicsAPI::eBufferTarget bufferTarget,
			const unsigned long long bufferSize,
			const void* const initialData
		)
		{
			unsigned long long bufferID = 0;
			glGenBuffers(1, reinterpret_cast<unsigned int*>(&bufferID));

			BindBuffer(bufferID, 0, bufferTarget, GraphicsAPI::eGraphicsPipeLineStage::DUMMY);
			glBufferData(opengl::GetGLBufferTarget(bufferTarget), bufferSize, initialData, GL_STATIC_DRAW);

			return bufferID;
		}

		DOOMS_ENGINE_GRAPHICS_API void EnableVertexAttributeArrayIndex(const unsigned int vertexAttributeIndex)
		{
			glEnableVertexAttribArray(vertexAttributeIndex);
		}

		DOOMS_ENGINE_GRAPHICS_API void DefineVertexAttributeLayout
		(
			const unsigned long long vertexBufferObject,
			const unsigned int vertexAttributeIndex,
			const unsigned int componentCount,
			const unsigned int stride,
			const unsigned int offset
		)
		{
			glVertexAttribPointer(vertexAttributeIndex, componentCount, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
		}

		

		DOOMS_ENGINE_GRAPHICS_API void UnBindBuffer(const GraphicsAPI::eBufferTarget bindBufferTarget)
		{
			glBindBuffer(opengl::GetGLBufferTarget(bindBufferTarget), 0);
		}

		DOOMS_ENGINE_GRAPHICS_API void BindConstantBuffer
		(
			const unsigned long long bufferObject,
			const unsigned int bindingPoint,
			const GraphicsAPI::eGraphicsPipeLineStage pipeLineStage
		)
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, bufferObject);
		}

		DOOMS_ENGINE_GRAPHICS_API void UpdateDataToBuffer
		(
			const unsigned long long bufferObject,
			const GraphicsAPI::eBufferTarget bindBufferTarget,
			const unsigned long long offset,
			const unsigned long long dataSize,
			const void* const data
		)
		{
			assert(bufferObject != 0);
			glNamedBufferSubData(bufferObject, offset, dataSize, data);
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned int CheckFrameBufferIsSuccesfullyCreated()
		{
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
			{
				return 0;
			}
			else
			{
				return glCheckFramebufferStatus(GL_FRAMEBUFFER);
			}
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned long long GenerateFrameBuffer()
		{
			unsigned int frameBuffer;
			glGenFramebuffers(1, &frameBuffer);

			const unsigned int errorCode = CheckFrameBufferIsSuccesfullyCreated();
			assert(errorCode == 0, "fail frame buffer : %u", errorCode);

			return frameBuffer;
		}

		DOOMS_ENGINE_GRAPHICS_API void DestroyFrameBuffer(unsigned long long frameBufferObject)
		{
			glDeleteFramebuffers(1, reinterpret_cast<unsigned int*>(&frameBufferObject));
		}

		DOOMS_ENGINE_GRAPHICS_API void BindFrameBuffer
		(
			const unsigned int renderTargetCount,
			unsigned long long* const renderTargetViewObject,
			const unsigned int coloreTextureCount,
			unsigned long long depthStencilViewObject
		)
		{
			assert(renderTargetCount == 1);
			glBindFramebuffer(GL_FRAMEBUFFER, *renderTargetViewObject);

			static unsigned int attachments[] = 
			{
				GL_COLOR_ATTACHMENT0,
				GL_COLOR_ATTACHMENT1,
				GL_COLOR_ATTACHMENT2,
				GL_COLOR_ATTACHMENT3,
				GL_COLOR_ATTACHMENT4,
				GL_COLOR_ATTACHMENT5,
				GL_COLOR_ATTACHMENT6,
				GL_COLOR_ATTACHMENT7,
				GL_COLOR_ATTACHMENT8,
				GL_COLOR_ATTACHMENT9,
				GL_COLOR_ATTACHMENT10,
				GL_COLOR_ATTACHMENT11,
				GL_COLOR_ATTACHMENT12,
				GL_COLOR_ATTACHMENT13,
				GL_COLOR_ATTACHMENT14,
				GL_COLOR_ATTACHMENT15,
				GL_COLOR_ATTACHMENT16,
				GL_COLOR_ATTACHMENT17,
				GL_COLOR_ATTACHMENT18,
				GL_COLOR_ATTACHMENT19,
				GL_COLOR_ATTACHMENT20,
				GL_COLOR_ATTACHMENT21,
				GL_COLOR_ATTACHMENT22,
				GL_COLOR_ATTACHMENT23,
				GL_COLOR_ATTACHMENT24,
				GL_COLOR_ATTACHMENT25,
				GL_COLOR_ATTACHMENT26,
				GL_COLOR_ATTACHMENT27,
				GL_COLOR_ATTACHMENT28,
				GL_COLOR_ATTACHMENT29,
				GL_COLOR_ATTACHMENT30,
				GL_COLOR_ATTACHMENT31,
			};
			glNamedFramebufferDrawBuffers(*renderTargetViewObject, coloreTextureCount, attachments);
		}

		DOOMS_ENGINE_GRAPHICS_API void BindBackBuffer()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		

		DOOMS_ENGINE_GRAPHICS_API void BindRenderBuffer(const unsigned long long renderBufferObject)
		{
			glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned long long Attach2DTextureToFrameBuffer
		(
			const unsigned long long frameBufferObject,
			const GraphicsAPI::eFrameBufferAttachmentPoint frameBufferAttachmentPoint,
			const GraphicsAPI::eTextureBindTarget textureBindTarget,
			const unsigned long long textureBufferObject,
			const unsigned int lodLevel
		)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);

			glFramebufferTexture2D(GL_FRAMEBUFFER, opengl::GetGLFrameBufferAttachmentPoint(frameBufferAttachmentPoint), opengl::GetGLTextureBindTarget(textureBindTarget), textureBufferObject, lodLevel);

			const unsigned int errorCode = CheckFrameBufferIsSuccesfullyCreated();
			assert(errorCode == 0, "fail frame buffer : %u", errorCode);

			return textureBufferObject;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned long long CopyRenderTargetView(const unsigned long long renderTargetView)
		{
			return renderTargetView;
		}
		
		/*
		DOOMS_ENGINE_GRAPHICS_API unsigned long long CreateRenderBufferObject()
		{
			unsigned int bufferID;
			glGenRenderbuffers(1, &bufferID);
			return bufferID;
		}

		DOOMS_ENGINE_GRAPHICS_API void AllocateRenderBufferMemory
		(
			const unsigned long long renderBufferObject,
			const GraphicsAPI::eTextureInternalFormat textureInternalFormat,
			const unsigned int width, const unsigned int height,
			const unsigned int multiSample
		)
		{
			BindRenderBuffer(renderBufferObject);
			if (multiSample == 0)
			{
				glRenderbufferStorage(GL_RENDERBUFFER, opengl::GetGLTextureInternalFormat(textureInternalFormat), width, height);
			}
			else
			{
				glRenderbufferStorageMultisample(GL_RENDERBUFFER, multiSample, opengl::GetGLTextureInternalFormat(textureInternalFormat), width, height);
			}

		}

		DOOMS_ENGINE_GRAPHICS_API void AttachRenderBufferToFrameBuffer
		(
			const unsigned long long renderBufferObject,
			const unsigned long long frameBufferObject,
			const GraphicsAPI::eFrameBufferAttachmentPoint frameBufferAttachmentPoint
		)
		{
			BindRenderBuffer(renderBufferObject);
			BindFrameBuffer(frameBufferObject, GL_FRAMEBUFFER);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, opengl::GetGLFrameBufferAttachmentPoint(frameBufferAttachmentPoint), GL_RENDERBUFFER, renderBufferObject);
		}

		DOOMS_ENGINE_GRAPHICS_API void DestroyRenderBuffer(unsigned long long renderBuffer)
		{
			glDeleteRenderbuffers(1, reinterpret_cast<unsigned int*>(&renderBuffer));
		}
		*/

		DOOMS_ENGINE_GRAPHICS_API int GetFrameBufferWidth(const unsigned long long frameBuffer)
		{
			glBindBuffer(frameBuffer, GL_FRAMEBUFFER);

			int data;
			glGetFramebufferParameteriv(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, &data);
			return data;
		}

		DOOMS_ENGINE_GRAPHICS_API int GetFrameBufferHeight(const unsigned long long frameBuffer)
		{
			glBindBuffer(frameBuffer, GL_FRAMEBUFFER);

			int data;
			glGetFramebufferParameteriv(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, &data);
			return data;
		}

		static unsigned int PrimitiveTypeJumpTable[5] =
		{
			(unsigned int)-1,
			(unsigned int)GL_POINTS,
			(unsigned int)GL_LINES,
			(unsigned int)GL_TRIANGLES,
			(unsigned int)-1,
		};

		DOOMS_ENGINE_GRAPHICS_API void Draw
		(
			const GraphicsAPI::ePrimitiveType primitiveType,
			const unsigned long long vertexCount,
			const unsigned long long startVertexLocation
		)
		{
			assert((unsigned int)primitiveType < GraphicsAPI::ePrimitiveType::END);
			glDrawArrays(PrimitiveTypeJumpTable[(unsigned int)primitiveType], startVertexLocation, vertexCount);
			opengl::DrawCallCounter++;

		}


		DOOMS_ENGINE_GRAPHICS_API void DrawIndexed
		(
			const GraphicsAPI::ePrimitiveType primitiveType,
			const unsigned long long indiceCount
		)
		{
			assert((unsigned int)primitiveType < GraphicsAPI::ePrimitiveType::END);
			glDrawElements(PrimitiveTypeJumpTable[(unsigned int)primitiveType], indiceCount, GL_UNSIGNED_INT, 0);
			opengl::DrawCallCounter++;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned long long CreateMaterial()
		{
			unsigned int materialObject = glCreateProgram();
			assert(materialObject != 0);
			return materialObject;
		}

		DOOMS_ENGINE_GRAPHICS_API void DestroyMaterial(unsigned long long materialObject)
		{
			glDeleteProgram(materialObject);
		}

		DOOMS_ENGINE_GRAPHICS_API bool LinkMaterial(const unsigned long long materialObject)
		{
			glLinkProgram(materialObject);

			int isSuccess = 0;
			glGetProgramiv(materialObject, GL_LINK_STATUS, &isSuccess);
#ifdef _DEBUG
			if (isSuccess == 0)
			{
				char infoLog[512];
				glGetProgramInfoLog(materialObject, 512, NULL, infoLog);
				printf("SHADER::PROGRAM::LINKING_FAILED ( Material ID : %d ) : ( %s ) ", materialObject, infoLog);
			}
#endif

			return isSuccess != 0;
		}

		DOOMS_ENGINE_GRAPHICS_API void BindShader(const unsigned long long materialObject, const GraphicsAPI::eGraphicsPipeLineStage shaderType)
		{
			glUseProgram(materialObject);
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned long long CreateShaderObject(const GraphicsAPI::eGraphicsPipeLineStage shaderType)
		{
			assert(shaderType != GraphicsAPI::eGraphicsPipeLineStage::DUMMY);

			unsigned int shaderObject = glCreateShader(opengl::GetGLShaderType(shaderType));
			assert(shaderObject != 0);
			return shaderObject;
		}

		DOOMS_ENGINE_GRAPHICS_API void DestroyShaderObject(unsigned long long shaderObject)
		{
			glDeleteShader(shaderObject);
		}
		
		DOOMS_ENGINE_GRAPHICS_API bool AttachShaderToMaterial
		(
			unsigned long long& shaderView,
			const unsigned long long materialObject,
			const unsigned long long shaderObject,
			const GraphicsAPI::eGraphicsPipeLineStage targetGraphicsPipeLineStage // only used in dx11
		)
		{
			glAttachShader(materialObject, shaderObject);

			return true;
		}

		DOOMS_ENGINE_GRAPHICS_API bool DetachShaderFromMaterial
		(
			unsigned long long shaderView,
			const unsigned long long materialObject,
			const unsigned long long shaderObject
		)
		{
			glDetachShader(materialObject, shaderObject);

			return true;
		}
		
		DOOMS_ENGINE_GRAPHICS_API void* MapBufferObjectToClientAddress
		(
			const unsigned long long bufferID,
			const GraphicsAPI::eBufferTarget bindBufferTarget,
			const GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption
		)
		{
			BindBuffer(bufferID, 0, bindBufferTarget, GraphicsAPI::eGraphicsPipeLineStage::DUMMY);

			// https://www.khronos.org/registry/OpenGL-Refpages/es3.0/html/glMapBufferRange.xhtml
			return glMapBuffer(opengl::GetGLBufferTarget(bindBufferTarget), opengl::GetGLMapBufferAccessOption(mapBufferAccessOption));
		}

		DOOMS_ENGINE_GRAPHICS_API void* RangedMapBufferObjectToClientAddress
		(
			const unsigned long long bufferID,
			const unsigned long long offset,
			const unsigned long long length,
			const GraphicsAPI::eBufferTarget bindBufferTarget,
			const GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption
		)
		{
			BindBuffer(bufferID, 0, bindBufferTarget, GraphicsAPI::eGraphicsPipeLineStage::DUMMY);
			
			// https://www.khronos.org/registry/OpenGL-Refpages/es3.0/html/glMapBufferRange.xhtml
			return glMapBufferRange(opengl::GetGLBufferTarget(bindBufferTarget), offset, length, opengl::GetGLMapBufferAccessOption(mapBufferAccessOption));
		}

		DOOMS_ENGINE_GRAPHICS_API void UnMapBufferObjectMappedToClientAddress
		(
			const unsigned long long bufferID,
			const GraphicsAPI::eBufferTarget bindBufferTarget
		)
		{
			BindBuffer(bufferID, 0, bindBufferTarget, GraphicsAPI::eGraphicsPipeLineStage::DUMMY);
			glUnmapBuffer(opengl::GetGLBufferTarget(bindBufferTarget));
		}

		DOOMS_ENGINE_GRAPHICS_API void DestroyTextureObject(unsigned long long textureObject)
		{
			glDeleteTextures(1, reinterpret_cast<unsigned int*>(&textureObject));
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned long long CreateTextureViewObject(const unsigned long long textureObject)
		{
			assert(textureObject != 0);

			return textureObject;
		}

		DOOMS_ENGINE_GRAPHICS_API void DestroyTextureViewObject(unsigned long long textureViewObject)
		{
			assert(textureViewObject != 0);

			
		}

		DOOMS_ENGINE_GRAPHICS_API void BindTextureObject
		(
			const unsigned long long textureObject,
			const GraphicsAPI::eTextureBindTarget textureBindTarget,
			const unsigned int bindingLocation,
			const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage
		)
		{
			glActiveTexture(GL_TEXTURE0 + bindingLocation);
			glBindTexture(opengl::GetGLTextureBindTarget(textureBindTarget), textureObject);
		}

		DOOMS_ENGINE_GRAPHICS_API void ActivateTextureUnit(const unsigned int unitIndex)
		{
			glActiveTexture(GL_TEXTURE0 + unitIndex);
		}

		DOOMS_ENGINE_GRAPHICS_API void BindTextureObjectAndActivateTextureUnit
		(
			const unsigned long long textureObject,
			const unsigned int unitIndex
		)
		{
			glBindTextureUnit(unitIndex, textureObject);
		}

		DOOMS_ENGINE_GRAPHICS_API void UnBindTextureObject(const GraphicsAPI::eTextureBindTarget textureBindTarget)
		{
			glBindTexture(opengl::GetGLTextureBindTarget(textureBindTarget), 0);
		}

		DOOMS_ENGINE_GRAPHICS_API void BlitFrameBuffer
		(
			const unsigned long long ReadFrameBufferObject,
			const unsigned int ReadBindingPoint,
			const unsigned long long DrawFrameBufferObject,
			const unsigned int DrawBindingPoint,
			const int srcX0, const int srcY0, const int srcX1, const int srcY1,
			const int dstX0, const int dstY0, const int dstX1, const int dstY1,
			const GraphicsAPI::eBufferBitType mask,
			const GraphicsAPI::eImageInterpolation filter
		)
		{
			glBindFramebuffer(GL_READ_FRAMEBUFFER, ReadFrameBufferObject);
			if (ReadFrameBufferObject == 0)
			{
				glReadBuffer(GL_BACK);
			}
			else
			{
				glReadBuffer(GL_COLOR_ATTACHMENT0 + ReadBindingPoint);
			}
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, DrawFrameBufferObject);
			if(DrawFrameBufferObject == 0)
			{
				glDrawBuffer(GL_BACK);
			}
			else
			{
				glDrawBuffer(GL_COLOR_ATTACHMENT0 + DrawBindingPoint);
			}
			
			glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, opengl::GetGLBufferBitType(mask), opengl::GetGLImageInterpolation(filter));
		}

		DOOMS_ENGINE_GRAPHICS_API float GetTextureMetaDataFloat
		(
			const unsigned long long textureObject,
			const GraphicsAPI::eTextureBindTarget textureBindTarget,
			const unsigned int lodLevel,
			const GraphicsAPI::eTextureMetaDataType textureMetaDataType
		)
		{
			float data;

			BindTextureObject(textureObject, textureBindTarget, 0, GraphicsAPI::DUMMY);
			glGetTexLevelParameterfv(opengl::GetGLTextureBindTarget(textureBindTarget), lodLevel, opengl::GetGLTextureMataDataType(textureMetaDataType), &data);

			return data;
		}

		DOOMS_ENGINE_GRAPHICS_API int GetTextureMetaDataInt
		(
			const unsigned long long textureObject,
			const GraphicsAPI::eTextureBindTarget textureBindTarget,
			const unsigned int lodLevel,
			const GraphicsAPI::eTextureMetaDataType textureMetaDataType
		)
		{
			int data;

			BindTextureObject(textureObject, textureBindTarget, 0, GraphicsAPI::DUMMY);
			glGetTexLevelParameteriv(opengl::GetGLTextureBindTarget(textureBindTarget), lodLevel, opengl::GetGLTextureMataDataType(textureMetaDataType), &data);

			return data;
		}

		DOOMS_ENGINE_GRAPHICS_API void SetTextureParameterFloat
		(
			const GraphicsAPI::eTextureBindTarget textureBindTarget,
			const GraphicsAPI::eTextureParameterType textureParameterType,
			const float parameter
		)
		{
			glTexParameterf(opengl::GetGLTextureBindTarget(textureBindTarget), opengl::GetGLTextureParameterType(textureParameterType), parameter);
		}

		DOOMS_ENGINE_GRAPHICS_API void SetTextureParameterInt
		(
			const GraphicsAPI::eTextureBindTarget textureBindTarget,
			const GraphicsAPI::eTextureParameterType textureParameterType,
			const int parameter
		)
		{
			glTexParameteri(opengl::GetGLTextureBindTarget(textureBindTarget), opengl::GetGLTextureParameterType(textureParameterType), parameter);
		}

		DOOMS_ENGINE_GRAPHICS_API void SetTextureWrapMode_S(const GraphicsAPI::eTextureBindTarget textureBindTarget, const GraphicsAPI::eWrapMode wrapMode)
		{
			glTexParameteri(opengl::GetGLTextureBindTarget(textureBindTarget), GL_TEXTURE_WRAP_S, opengl::GetGLTextureWrapMode(wrapMode));
		}

		DOOMS_ENGINE_GRAPHICS_API void SetTextureWrapMode_T(const GraphicsAPI::eTextureBindTarget textureBindTarget, const GraphicsAPI::eWrapMode wrapMode)
		{
			glTexParameteri(opengl::GetGLTextureBindTarget(textureBindTarget), GL_TEXTURE_WRAP_T, opengl::GetGLTextureWrapMode(wrapMode));
		}

		DOOMS_ENGINE_GRAPHICS_API void SetTextureWrapMode_R(const GraphicsAPI::eTextureBindTarget textureBindTarget, const GraphicsAPI::eWrapMode wrapMode)
		{
			glTexParameteri(opengl::GetGLTextureBindTarget(textureBindTarget), GL_TEXTURE_WRAP_R, opengl::GetGLTextureWrapMode(wrapMode));
		}

		DOOMS_ENGINE_GRAPHICS_API void SetMinFilter
		(
			const GraphicsAPI::eTextureBindTarget textureBindTarget,
			const GraphicsAPI::eFilterMode filterMode
		)
		{
			glTexParameteri(opengl::GetGLTextureBindTarget(textureBindTarget), GL_TEXTURE_MIN_FILTER, opengl::GetGLTextureFilterMode(filterMode));
		}

		DOOMS_ENGINE_GRAPHICS_API void SetMagFilter
		(
			const GraphicsAPI::eTextureBindTarget textureBindTarget,
			const GraphicsAPI::eFilterMode filterMode
		)
		{
			glTexParameteri(opengl::GetGLTextureBindTarget(textureBindTarget), GL_TEXTURE_MAG_FILTER, opengl::GetGLTextureFilterMode(filterMode));
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned char* FetchTexturePixels
		(
			const GraphicsAPI::eTextureBindTarget textureBindTarget,
			const int lodLevel,
			const GraphicsAPI::eTextureComponentFormat textureComponentFormat,
			const GraphicsAPI::eDataType datatType,
			const unsigned long long bufferSize
		)
		{
			assert(bufferSize > 0);

			unsigned char* pixels = new unsigned char[bufferSize];

			glGetTexImage(opengl::GetGLTextureBindTarget(textureBindTarget), lodLevel, opengl::GetGLTextureComponentFormat(textureComponentFormat), opengl::GetGLDataType(datatType), reinterpret_cast<void*>(pixels));

			return pixels;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned char* ReadPixels
		(
			const unsigned long long frameBufferObject,
			const GraphicsAPI::eBufferMode bufferMode,
			const unsigned long long bufferSize,
			const int startX,
			const int startY,
			const int width,
			const int height,
			const GraphicsAPI::eTextureComponentFormat pixelFormat,
			const GraphicsAPI::eDataType dataType
		)
		{
			glReadBuffer(opengl::GetGLBufferMode(bufferMode));

			glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBufferObject);
			unsigned char* const buffer = new unsigned char[bufferSize];
			glReadPixels(startX, startY, width, height, opengl::GetGLTextureComponentFormat(pixelFormat), opengl::GetGLDataType(dataType), buffer);
			return buffer;
		}

		DOOMS_ENGINE_GRAPHICS_API unsigned long long Allocate2DTextureObject
		(
			const GraphicsAPI::eTextureBindTarget textureBindTarget,
			const unsigned int lodCount,
			const GraphicsAPI::eTextureInternalFormat textureInternalFormat,
			const GraphicsAPI::eTextureCompressedInternalFormat textureCompressedInternalFormat,
			const unsigned long long width,
			const unsigned long long height,
			const GraphicsAPI::eBindFlag bindFlag
		)
		{
			unsigned int internalFormat;
			if(textureInternalFormat != GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE)
			{
				internalFormat = opengl::GetGLTextureInternalFormat(textureInternalFormat);
			}
			else if (textureCompressedInternalFormat != GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE)
			{
				internalFormat = opengl::GetTextureCompressedInternalFormat(textureCompressedInternalFormat);
			}
			else
			{
				NEVER_HAPPEN;
			}

			unsigned long long buffer = 0;
			glGenTextures(1, reinterpret_cast<unsigned int*>(&buffer));
			
			BindTextureObject(buffer, textureBindTarget, 0, GraphicsAPI::eGraphicsPipeLineStage::DUMMY);

			glTexStorage2D
			(
				opengl::GetGLTextureBindTarget(textureBindTarget),
				lodCount,
				internalFormat,
				width,
				height
			);

			return buffer;
		}
		
		DOOMS_ENGINE_GRAPHICS_API void UploadPixelsTo2DTexture
		(
			const unsigned long long textureResourceObject,
			const GraphicsAPI::eTextureBindTarget textureBindTarget,
			const GraphicsAPI::eTargetTexture targetTexture,
			const unsigned int lodLevel,
			const unsigned int xOffset,
			const unsigned int yOffset,
			const unsigned long long width,
			const unsigned long long height,
			const GraphicsAPI::eTextureComponentFormat textureComponentFormat,
			const GraphicsAPI::eDataType dataType,
			const GraphicsAPI::eTextureInternalFormat textureInternalFormat,
			const GraphicsAPI::eTextureCompressedInternalFormat textureCompressedInternalFormat,
			const void* const pixelDatas,
			const size_t rowByteSize,
			const size_t totalDataSize
		)
		{
			assert(textureInternalFormat == graphics::GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE || textureCompressedInternalFormat == graphics::GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE);

			BindTextureObject(textureResourceObject, textureBindTarget, 0, GraphicsAPI::DUMMY);


			if(textureInternalFormat != GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE)
			{
				glTexSubImage2D
				(
					opengl::GetGLTargetTexture(targetTexture),
					lodLevel,
					xOffset,
					yOffset,
					width,
					height,
					opengl::GetGLTextureComponentFormat(textureComponentFormat),
					opengl::GetGLDataType(dataType),
					pixelDatas
				);
			}
			else
			{
				glCompressedTexSubImage2D
				(
					opengl::GetGLTargetTexture(targetTexture),
					lodLevel,
					xOffset,
					yOffset,
					width,
					height,
					opengl::GetTextureCompressedInternalFormat(textureCompressedInternalFormat),
					totalDataSize,
					pixelDatas
				);
			}
			
		}
		
		DOOMS_ENGINE_GRAPHICS_API int GetConstantBufferBindingPoint
		(
			const unsigned long long constantBufferObject,
			const unsigned blockIndex
		)
		{
			int uniformBlockBindingPoint;
			glGetActiveUniformBlockiv(constantBufferObject, blockIndex, GL_UNIFORM_BLOCK_BINDING, &uniformBlockBindingPoint);
			return uniformBlockBindingPoint;
		}

		DOOMS_ENGINE_GRAPHICS_API int GetConstantBufferDataSize
		(
			const unsigned long long constantBufferObject,
			const unsigned blockIndex
		)
		{
			int dataSize;
			glGetActiveUniformBlockiv(constantBufferObject, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &dataSize);
			return dataSize;
		}

		DOOMS_ENGINE_GRAPHICS_API int GetConstantBufferBlockCount
		(
			const unsigned long long constantBufferObject
		)
		{
			int blockCount;
			glGetProgramiv(constantBufferObject, GL_ACTIVE_UNIFORM_BLOCKS, &blockCount);
			return blockCount;
		}

		DOOMS_ENGINE_GRAPHICS_API int GetConstantBufferUniformLocation
		(
			const unsigned long long constantBufferObject,
			const char* const uniformStr
		)
		{
			return glGetUniformLocation(constantBufferObject, uniformStr);
		}


		DOOMS_ENGINE_GRAPHICS_API void SetWindowTitle(const char* const title)
		{
			assert(dooms::graphics::opengl::glfwWindow != nullptr);
			glfwSetWindowTitle(dooms::graphics::opengl::glfwWindow, title);
		}

		DOOMS_ENGINE_GRAPHICS_API void SetWindowTitleW(const wchar_t* const title)
		{
			assert(dooms::graphics::opengl::glfwWindow != nullptr);

			char buffer[256];
			const int length = WideCharToMultiByte(CP_UTF8, 0, title, -1, buffer, 256, NULL, NULL);
			WideCharToMultiByte(CP_UTF8, 0, title, -1, buffer, length, NULL, NULL);
			glfwSetWindowTitle(dooms::graphics::opengl::glfwWindow, buffer);
		}

		DOOMS_ENGINE_GRAPHICS_API void ClearBackFrameBufferColorBuffer(const float r, const float g, const float b, const float a)
		{
			BindBackBuffer();
			glClearColor(r, g, b, a);
			glClear(opengl::GetGLBufferBitType(GraphicsAPI::COLOR_BUFFER));
		}

		DOOMS_ENGINE_GRAPHICS_API void ClearBackFrameBufferDepthBuffer(const double depthValue)
		{
			BindBackBuffer();
			glClearDepth(depthValue);
			glClear(opengl::GetGLBufferBitType(GraphicsAPI::DEPTH_BUFFER));
		}

		DOOMS_ENGINE_GRAPHICS_API void ClearBackFrameBufferStencilBuffer(const int stencilValue)
		{
			BindBackBuffer();
			glClearStencil(stencilValue);
			glClear(opengl::GetGLBufferBitType(GraphicsAPI::STENCIL_BUFFER));
		}

		DOOMS_ENGINE_GRAPHICS_API void ClearBackFrameBufferDepthStencilBuffer(const double depthValue, const int stencilValue)
		{
			BindBackBuffer();
			glClearDepth(depthValue);
			glClearStencil(stencilValue);
			glClear(opengl::GetGLBufferBitType(GraphicsAPI::DEPTH_STENCIL_BUFFER));
		}

		DOOMS_ENGINE_GRAPHICS_API void ClearFrameBufferColorBuffer
		(
			unsigned long long bufferObject, 
			const unsigned int colorTextureIndex,
			const float r, 
			const float g, 
			const float b,
			const float a
		)
		{
			assert(bufferObject != 0);

			glBindFramebuffer(GL_FRAMEBUFFER, bufferObject);
			glClearColor(r, g, b, a);
			glNamedFramebufferDrawBuffer(bufferObject, GL_COLOR_ATTACHMENT0 + colorTextureIndex);
			glClear(opengl::GetGLBufferBitType(GraphicsAPI::COLOR_BUFFER));
		}

		DOOMS_ENGINE_GRAPHICS_API void ClearFrameBufferDepthBuffer(unsigned long long bufferObject, const double depthValue)
		{
			assert(bufferObject != 0);

			glBindFramebuffer(GL_FRAMEBUFFER, bufferObject);
			glClearDepth(depthValue);
			glClear(opengl::GetGLBufferBitType(GraphicsAPI::DEPTH_BUFFER));
		}

		DOOMS_ENGINE_GRAPHICS_API void ClearFrameBufferStencilBuffer(unsigned long long bufferObject, const int stecilValue)
		{
			assert(bufferObject != 0);

			glBindFramebuffer(GL_FRAMEBUFFER, bufferObject);
			glClearStencil(stecilValue);
			glClear(opengl::GetGLBufferBitType(GraphicsAPI::STENCIL_BUFFER));
		}
		DOOMS_ENGINE_GRAPHICS_API void ClearFrameBufferDepthStencilBuffer(unsigned long long bufferObject, const double depthValue, const int stencilValue)
		{
			assert(bufferObject != 0);

			glBindFramebuffer(GL_FRAMEBUFFER, bufferObject);
			glClearDepth(depthValue);
			glClearStencil(stencilValue);
			glClear(opengl::GetGLBufferBitType(GraphicsAPI::DEPTH_STENCIL_BUFFER));
		}
	}
}
