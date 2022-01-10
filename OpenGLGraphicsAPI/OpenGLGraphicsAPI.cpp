#include "GraphicsAPI.h"

#include <cassert>
#include <cstdio>
#include <string>

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

			enum class GetStringParameter
			{
				VENDOR = GL_VENDOR,
				RENDERER = GL_VENDOR,
				VERSION = GL_VENDOR,
				SHADING_LANGUAGE_VERSION = GL_VENDOR,
			};

			inline extern unsigned int GetGLDepthFuncType(const GraphicsAPI::eDepthFuncType depthFuncType)
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
			
			inline extern unsigned int GetTextureCompressedInternalFormat(const GraphicsAPI::eTextureCompressedInternalFormat textureCompressedInternalFormat)
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

			inline extern unsigned int GetGLTextureParameterValue(const GraphicsAPI::eTextureParameterValue textureParameterValue)
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

			inline extern unsigned int GetGLTextureWrapMode(const GraphicsAPI::eWrapMode wrapMode)
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

			inline extern unsigned int GetGLTextureFilterMode(const GraphicsAPI::eFilterMode filterMode)
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

			inline extern unsigned int GetGLTextureComponentFormat(const GraphicsAPI::eTextureComponentFormat textureComponentFormat)
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

			inline extern unsigned int GetGLTextureInternalFormat(const graphics::GraphicsAPI::eTextureInternalFormat textureInternalFormat)
			{
				switch (textureInternalFormat)
				{
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT:
					return GL_DEPTH_COMPONENT;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT16:
					return GL_DEPTH_COMPONENT16;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT24:
					return GL_DEPTH_COMPONENT24;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT32:
					return GL_DEPTH_COMPONENT32;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_COMPONENT32F:
					return GL_DEPTH_COMPONENT32F;
				case GraphicsAPI::TEXTURE_INTERNAL_FORMAT_DEPTH_STENCIL:
					return GL_DEPTH_STENCIL;
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

			inline extern unsigned int GetGLBufferTarget(const GraphicsAPI::eBufferTarget bufferTarget)
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
					NEVER_HAPPEN; return 0;
				}
			}

			inline extern unsigned int GetGLBufferBitType(const unsigned int bufferTypeBits)
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
					NEVER_HAPPEN; return 0;
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
					NEVER_HAPPEN; return 0;
				}
			}

			inline extern unsigned int GetGLTextureBindTarget(const GraphicsAPI::eTextureBindTarget textureBindTarget)
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
					NEVER_HAPPEN; return 0;

				}
			}

			inline extern unsigned int GetGLMapBufferAccessOption(const GraphicsAPI::eMapBufferAccessOption mapBufferAccessOption)
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

			inline extern unsigned int GetGLTextureMataDataType(const GraphicsAPI::eTextureMetaDataType textureMetaDataType)
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
			
			inline extern unsigned int GetGLTextureParameterType(const GraphicsAPI::eTextureParameterType textureParameterType)
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

			inline extern unsigned int GetGLTargetTexture(const GraphicsAPI::eTargetTexture targetTexture)
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


			
			inline extern unsigned int GetGLDataType(const GraphicsAPI::eDataType dataType)
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

			inline extern unsigned int GetGLBlendFactor(const graphics::GraphicsAPI::eBlendFactor blendFactor)
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

			inline extern unsigned int GetGLWinding(const GraphicsAPI::eWinding winding)
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

			inline extern unsigned int GetGLImageInterpolation(const GraphicsAPI::eImageInterpolation imageInterpolation)
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

			
			inline extern unsigned int GetGLFrameBufferAttachmentPoint(const GraphicsAPI::eFrameBufferAttachmentPoint frameBufferAttachmentPoint)
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

			inline extern unsigned int GetGLBindFrameBufferTarget(const GraphicsAPI::eBindFrameBufferTarget bindFrameBufferTarget)
			{
				switch (bindFrameBufferTarget)
				{
				case GraphicsAPI::DRAW_FRAMEBUFFER:
					return GL_DRAW_FRAMEBUFFER;
				case GraphicsAPI::READ_FRAMEBUFFER:
					return GL_READ_FRAMEBUFFER;
				case GraphicsAPI::FRAMEBUFFER:
					return GL_FRAMEBUFFER;
				default:
					NEVER_HAPPEN;
					return 0;
				}
			}

			static GLFWwindow* glfwWindow = nullptr;

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
				if(id == 131218) // NVIDIA: "shader will be recompiled due to GL state mismatches"
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
				(*dooms::graphics::GraphicsAPI::GetDebugFunction())(msg, debugCallbackseverity);
				
			}
		}
	}
}

void dooms::graphics::GraphicsAPI::SetDebugFunction(DEBUG_FUNCTION debugFunction)
{
	opengl::mDEBUG_FUNCTION = debugFunction;
}

dooms::graphics::GraphicsAPI::DEBUG_FUNCTION dooms::graphics::GraphicsAPI::GetDebugFunction()
{
	return opengl::mDEBUG_FUNCTION;
}

const char* dooms::graphics::GraphicsAPI::GetPlatformVersion()
{
	return opengl::OpenGLVersion.c_str();
}

void* dooms::graphics::GraphicsAPI::GetPlatformWindow()
{
	return dooms::graphics::opengl::glfwWindow;
}


/**
 * \brief 
 * \return elapsed time since GLFW was initilized
 */
double dooms::graphics::GraphicsAPI::GetTime()
{
	return glfwGetTime();
}

unsigned int dooms::graphics::GraphicsAPI::Initialize(const int screenWidth, const int screenHeight, const unsigned int multiSamplingNum)
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

	dooms::graphics::opengl::glfwWindow = glfwCreateWindow(screenWidth, screenHeight, "SUNG JIN KANG", NULL, NULL);
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

void dooms::graphics::GraphicsAPI::SwapBuffer() noexcept
{
	assert(dooms::graphics::opengl::glfwWindow != nullptr);
	glfwSwapBuffers(dooms::graphics::opengl::glfwWindow);
}



void dooms::graphics::GraphicsAPI::SetVSync(const bool isEnabled) noexcept
{
	glfwSwapInterval(isEnabled == true ? 1 : 0);
}

void dooms::graphics::GraphicsAPI::SetIsDepthTestEnabled(const bool isEnabled) noexcept
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

void dooms::graphics::GraphicsAPI::SetDepthFunc(const eDepthFuncType depthFuncType) noexcept
{
	glDepthFunc(opengl::GetGLDepthFuncType(depthFuncType));
}

void dooms::graphics::GraphicsAPI::SetDepthMask(const bool isWriteDepthBuffer) noexcept
{
	glDepthMask(isWriteDepthBuffer);
}

void dooms::graphics::GraphicsAPI::SetIsAlphaTestEnabled(const bool isEnabled) noexcept
{
	if(isEnabled == true)
	{
		glEnable(GL_ALPHA_TEST);
	}
	else
	{
		glDisable(GL_ALPHA_TEST);
	}
	
}

void dooms::graphics::GraphicsAPI::SetIsBlendEnabled(const bool isEnabled) noexcept
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

void dooms::graphics::GraphicsAPI::SetViewport(const int startX, const int startY, const unsigned int width, const unsigned int height) noexcept
{
	glViewport(startX, startY, width, height);
}

std::array<int, 4> dooms::graphics::GraphicsAPI::GetViewPort()
{
	std::array<int, 4> viewPort;
	glGetIntegerv(GL_VIEWPORT, viewPort.data());
	return viewPort;
}

void dooms::graphics::GraphicsAPI::SetBlendFactor
(
	const eBlendFactor sourceBlendFactor,
	const eBlendFactor destinationBlendFactor
) noexcept
{
	glBlendFunc(opengl::GetGLBlendFactor(sourceBlendFactor), opengl::GetGLBlendFactor(destinationBlendFactor));
}

void dooms::graphics::GraphicsAPI::SetCullFace(const eCullFace cullFace) noexcept
{
	glEnable(GL_CULL_FACE);
	switch (cullFace)
	{
	case CULLFACE_FRONT:
		glCullFace(GL_FRONT);
		break;

	case CULLFACE_BACK:
		glCullFace(GL_BACK);
		break;

	case CULLFACE_FRONT_AND_BACK:
		glCullFace(GL_FRONT_AND_BACK);
		break;

	default: 
		NEVER_HAPPEN; 
	}
}

void dooms::graphics::GraphicsAPI::SetFrontFaceWinding(const eWinding winding) noexcept
{
	glFrontFace(opengl::GetGLWinding(winding));
}

void dooms::graphics::GraphicsAPI::SetDrawBuffer(const GraphicsAPI::eBufferMode bufferMode) noexcept
{
	glDrawBuffer(opengl::GetGLBufferMode(bufferMode));
}

void dooms::graphics::GraphicsAPI::SetDrawBuffers
(
	const unsigned int count,
	const std::vector<GraphicsAPI::eBufferMode> bufferModes
) noexcept
{
	std::vector<unsigned int> glBufferModes;
	glBufferModes.resize(bufferModes.size());
	for(unsigned int i = 0 ; i < bufferModes.size() ; i++)
	{
		glBufferModes[i] = opengl::GetGLBufferMode(bufferModes[i]);
	}
	glDrawBuffers(count, glBufferModes.data());
}

void dooms::graphics::GraphicsAPI::SetReadBuffer(const GraphicsAPI::eBufferMode bufferMode) noexcept
{
	glReadBuffer(opengl::GetGLBufferMode(bufferMode));
}

void dooms::graphics::GraphicsAPI::ClearColor(const float r, const float g, const float b, const float a) noexcept
{
	glClearColor(r, g, b, a);
}

void dooms::graphics::GraphicsAPI::ClearColor(const float* const color) noexcept
{
	glClearColor(color[0], color[1], color[2], color[3]);
}

void dooms::graphics::GraphicsAPI::ClearBuffer(const unsigned int clearMaskBits) noexcept
{
	glClear(opengl::GetGLBufferBitType(clearMaskBits));
}

void dooms::graphics::GraphicsAPI::ClearBuffer(const eBufferBitType clearMask) noexcept
{
	glClear(opengl::GetGLBufferBitType(clearMask));
}

void dooms::graphics::GraphicsAPI::ClearBuffer(const eBufferBitType clearMask1, const eBufferBitType clearMask2) noexcept
{
	glClear(opengl::GetGLBufferBitType(clearMask1) | opengl::GetGLBufferBitType(clearMask2));
}

void dooms::graphics::GraphicsAPI::ClearBuffer(const eBufferBitType clearMask1, const eBufferBitType clearMask2, const eBufferBitType clearMask3) noexcept
{
	glClear(opengl::GetGLBufferBitType(clearMask1) | opengl::GetGLBufferBitType(clearMask2) | opengl::GetGLBufferBitType(clearMask3));
}

void dooms::graphics::GraphicsAPI::ClearSpecificBuffer
(
	const eBufferType bufferType, 
	const unsigned int drawBufferIndex,
	const float r, const float g, const float b, const float a
) noexcept
{
	const std::vector<float> colors{ r, g, b, a };
	ClearSpecificBuffer(bufferType, drawBufferIndex, colors.data());
}

void dooms::graphics::GraphicsAPI::ClearSpecificBuffer
(
	const eBufferType bufferType, 
	const unsigned int drawBufferIndex,
	const float* const colors
) noexcept
{
	glClearBufferfv(opengl::GetGLBufferType(bufferType), drawBufferIndex, colors);
}

std::vector<unsigned int>  dooms::graphics::GraphicsAPI::GenerateBuffer(const unsigned int count) noexcept
{
	assert(count > 0);

	std::vector<unsigned int> renderBufferObject;
	renderBufferObject.resize(count);

	glGenBuffers(1, renderBufferObject.data());
	return renderBufferObject;
}

void dooms::graphics::GraphicsAPI::DestroyBuffer(const unsigned int bufferID) noexcept
{
	glDeleteBuffers(1, &bufferID);
}

std::vector<unsigned int> dooms::graphics::GraphicsAPI::CreateBuffers(const unsigned int bufferCount) noexcept
{
	std::vector<unsigned int> bufferObject;
	bufferObject.resize(bufferCount);

	glGenBuffers(bufferCount, bufferObject.data());
	return bufferObject;
}

void dooms::graphics::GraphicsAPI::DestroyBuffers(const std::vector<unsigned int>& buffers) noexcept
{
	glDeleteBuffers(buffers.size(), buffers.data());
}

std::vector<unsigned int> dooms::graphics::GraphicsAPI::CreateVertexArrayObject(const unsigned int count) noexcept
{
	assert(count > 0);

	std::vector<unsigned int> bufferObject;
	bufferObject.resize(count);
	
	glGenVertexArrays(count, bufferObject.data());
	return bufferObject;
}

void dooms::graphics::GraphicsAPI::DestroyVertexArrayObject(const std::vector<unsigned int>& vertexArrayObjects) noexcept
{
	glDeleteVertexArrays(vertexArrayObjects.size(), vertexArrayObjects.data());
}

void dooms::graphics::GraphicsAPI::BindVertexArrayObject(const unsigned int vertexArrayObject) noexcept
{
	glBindVertexArray(vertexArrayObject);
}

void dooms::graphics::GraphicsAPI::UnBindVertexArrayObject() noexcept
{
	glBindVertexArray(0);
}

void dooms::graphics::GraphicsAPI::AllocateBufferMemory
(
	const eBufferTarget bufferTarget, 
	const unsigned int bufferSize,
	const void* const initialData
) noexcept
{
	glBufferData(opengl::GetGLBufferTarget(bufferTarget), bufferSize, initialData, GL_STATIC_DRAW);
}

void dooms::graphics::GraphicsAPI::EnableVertexAttributeArrayIndex(const unsigned int vertexAttributeIndex) noexcept
{
	glEnableVertexAttribArray(vertexAttributeIndex);
}

void dooms::graphics::GraphicsAPI::DefineVertexAttributeLayout
(
	const unsigned int vertexAttributeIndex,
	const unsigned int componentNumber,
	const unsigned int stride,
	const unsigned int offset
) noexcept
{
	glVertexAttribPointer(vertexAttributeIndex, componentNumber, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<GLvoid*>(offset));
}

void dooms::graphics::GraphicsAPI::BindBuffer
(
	const unsigned int bufferObject, 
	const eBufferTarget bindBufferTarget
) noexcept
{
	glBindBuffer(opengl::GetGLBufferTarget(bindBufferTarget), bufferObject);
}

void dooms::graphics::GraphicsAPI::UnBindBuffer(const eBufferTarget bindBufferTarget) noexcept
{
	glBindBuffer(opengl::GetGLBufferTarget(bindBufferTarget), 0);
}

void dooms::graphics::GraphicsAPI::BindBufferToIndexedBuffer
(
	const eBufferTarget bindBufferTarget,
	const unsigned int bindingPoint,
	const unsigned int bufferObject
) noexcept
{
	glBindBufferBase(opengl::GetGLBufferTarget(bindBufferTarget), bindingPoint, bufferObject);
}

void dooms::graphics::GraphicsAPI::UpdateDataToBuffer
(
	const eBufferTarget bindBufferTarget,
	const unsigned int offset,
	const unsigned int dataSize,
	const void* const data
) noexcept
{
	glBufferSubData(opengl::GetGLBufferTarget(bindBufferTarget), offset, dataSize, data);
}

unsigned dooms::graphics::GraphicsAPI::GenerateFrameBuffer() noexcept
{
	unsigned int frameBuffer;
	glGenFramebuffers(1, &frameBuffer);
	return frameBuffer;
}

void dooms::graphics::GraphicsAPI::DestroyFrameBuffer(const unsigned int frameBufferObject) noexcept
{
	glDeleteFramebuffers(1, &frameBufferObject);
}

void dooms::graphics::GraphicsAPI::BindFrameBuffer
(
	const unsigned int frameBufferObject,
	const eBindFrameBufferTarget bindFrameBufferTarget
) noexcept
{
	glBindFramebuffer(opengl::GetGLBindFrameBufferTarget(bindFrameBufferTarget), frameBufferObject);
}

unsigned int dooms::graphics::GraphicsAPI::CheckFrameBufferIsSuccesfullyCreated()
{
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		return 0;
	}
	else
	{
		return glCheckFramebufferStatus(GL_FRAMEBUFFER);
	}
	
}

void dooms::graphics::GraphicsAPI::BindRenderBuffer(const unsigned int renderBufferObject) noexcept
{
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
}

void dooms::graphics::GraphicsAPI::Attach2DTextureToFrameBuffer
(
	const eBindFrameBufferTarget bindFrameBufferTarget,
	const eFrameBufferAttachmentPoint frameBufferAttachmentPoint, 
	const eTextureBindTarget textureBindTarget,
	const unsigned int textureBufferObject,
	const int lodLevel
)
{
	glFramebufferTexture2D(opengl::GetGLBindFrameBufferTarget(bindFrameBufferTarget), opengl::GetGLFrameBufferAttachmentPoint(frameBufferAttachmentPoint), opengl::GetGLTextureBindTarget(textureBindTarget), textureBufferObject, lodLevel);
}

std::vector<unsigned int> dooms::graphics::GraphicsAPI::CreateRenderBufferObject(const unsigned int renderBufferCount) noexcept
{
	assert(renderBufferCount > 0);

	std::vector<unsigned int> renderBufferObject;
	renderBufferObject.resize(renderBufferCount);

	glGenRenderbuffers(1, renderBufferObject.data());
	return renderBufferObject;
}

void dooms::graphics::GraphicsAPI::AllocateRenderBufferMemory
(
	const unsigned int renderBufferObject,
	const eTextureInternalFormat textureInternalFormat,
	const unsigned int width, const unsigned int height,
	const unsigned int multiSample
) noexcept
{
	if(multiSample == 0)
	{
		glRenderbufferStorage(GL_RENDERBUFFER, opengl::GetGLTextureInternalFormat(textureInternalFormat), width, height);
	}
	else
	{
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, multiSample, opengl::GetGLTextureInternalFormat(textureInternalFormat), width, height);
	}

}

void dooms::graphics::GraphicsAPI::AttachRenderBufferToFrameBuffer
(
	const unsigned int renderBufferObject,
	const unsigned int frameBufferObject,
	const eFrameBufferAttachmentPoint frameBufferAttachmentPoint
) noexcept
{
	BindRenderBuffer(renderBufferObject);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, opengl::GetGLFrameBufferAttachmentPoint(frameBufferAttachmentPoint), GL_RENDERBUFFER, renderBufferObject);
}

void dooms::graphics::GraphicsAPI::DestroyRenderBuffer(const unsigned int renderBuffer) noexcept
{
	glDeleteRenderbuffers(1, &renderBuffer);
}

int dooms::graphics::GraphicsAPI::GetFrameBufferWidth(const unsigned int frameBuffer)
{
	GraphicsAPI::BindFrameBuffer(frameBuffer, eBindFrameBufferTarget::FRAMEBUFFER);

	int data;
	glGetFramebufferParameteriv(opengl::GetGLBindFrameBufferTarget(eBindFrameBufferTarget::FRAMEBUFFER), GL_FRAMEBUFFER_DEFAULT_WIDTH, &data);
	return data;
}

int dooms::graphics::GraphicsAPI::GetFrameBufferHeight(const unsigned int frameBuffer)
{
	GraphicsAPI::BindFrameBuffer(frameBuffer, eBindFrameBufferTarget::FRAMEBUFFER);

	int data;
	glGetFramebufferParameteriv(opengl::GetGLBindFrameBufferTarget(eBindFrameBufferTarget::FRAMEBUFFER), GL_FRAMEBUFFER_DEFAULT_HEIGHT, &data);
	return data;
}


void dooms::graphics::GraphicsAPI::Draw
(
	const ePrimitiveType primitiveType, 
	const unsigned int vertexCount,
	const unsigned int startVertexLocation
) noexcept
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
		break;
	}

	
}


void dooms::graphics::GraphicsAPI::DrawIndexed
(
	const ePrimitiveType primitiveType, 
	const unsigned int indiceCount,
	const void* const indices
) noexcept
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

unsigned dooms::graphics::GraphicsAPI::CreateMaterial() noexcept
{
	unsigned int materialObject = glCreateProgram();
	assert(materialObject != 0);
	return materialObject;
}

void dooms::graphics::GraphicsAPI::DestroyMaterial(const unsigned int materialObject) noexcept
{
	glDeleteProgram(materialObject);
}

bool dooms::graphics::GraphicsAPI::LinkMaterial(const unsigned int materialObject) noexcept
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

void dooms::graphics::GraphicsAPI::BindMaterial(const unsigned int materialObject) noexcept
{
	glUseProgram(materialObject);
}

unsigned dooms::graphics::GraphicsAPI::CreateShaderObject(const eShaderType shaderType) noexcept
{
	assert(shaderType != eShaderType::ShaderType_None);

	unsigned int shaderObject = glCreateShader(opengl::GetGLShaderType(shaderType));
	assert(shaderObject != 0);
	return shaderObject;
}

void dooms::graphics::GraphicsAPI::DestroyShaderObject(const unsigned int shaderObject) noexcept
{
	glDeleteShader(shaderObject);
}

void dooms::graphics::GraphicsAPI::CompileShaders
(
	const unsigned int shaderObject,
	const unsigned int shaderCount,
	const char* const* const shaderTexts
) noexcept
{
	glShaderSource(shaderObject, shaderCount, shaderTexts, NULL);
	glCompileShader(shaderObject);
}

void dooms::graphics::GraphicsAPI::AttachShaderToMaterial(const unsigned int materialObject, const unsigned int shaderObject) noexcept
{
	glAttachShader(materialObject, shaderObject);
}



void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_bool1
(
	const int location, 
	const bool value1
) noexcept
{
	glUniform1i(location, static_cast<int>(value1));
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_bool2
(
	const int location, 
	const bool value1,
	const bool value2
) noexcept
{
	glUniform2i(location, static_cast<int>(value1), static_cast<int>(value2));
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_bool3
(
	const int location, 
	const bool value1,
	const bool value2, 
	const bool value3
) noexcept
{
	glUniform3i(location, static_cast<int>(value1), static_cast<int>(value2), static_cast<int>(value3));
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_bool4
(
	const int location, 
	const bool value1,
	const bool value2, 
	const bool value3, 
	const bool value4
) noexcept
{
	glUniform4i(location, static_cast<int>(value1), static_cast<int>(value2), static_cast<int>(value3), static_cast<int>(value4));
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_int1
(
	const int location, 
	const int value1
) noexcept
{
	glUniform1i(location, value1);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_int2
(
	const int location, 
	const int value1,
	const int value2
) noexcept
{
	glUniform2i(location, value1, value2);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_int3
(
	const int location, 
	const int value1,
	const int value2, 
	const int value3
) noexcept
{
	glUniform3i(location, value1, value2, value3);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_int4
(
	const int location, 
	const int value1,
	const int value2, 
	const int value3, 
	const int value4
) noexcept
{
	glUniform4i(location, value1, value2, value3, value4);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_float1
(
	const int location,
	const float value1
) noexcept
{
	glUniform1f(location, value1);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_float2
(
	const int location,
	const float value1,
	const float value2
) noexcept
{
	glUniform2f(location, value1, value2);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_float3
(
	const int location,
	const float value1,
	const float value2, 
	const float value3
) noexcept
{
	glUniform3f(location, value1, value2, value3);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_float4
(
	const int location,
	const float value1,
	const float value2, 
	const float value3, 
	const float value4
) noexcept
{
	glUniform4f(location, value1, value2, value3, value4);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_mat2x2f(const int location, const float* const matrix) noexcept
{
	glUniformMatrix2fv(location, 1, GL_FALSE, matrix);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_mat3x3f(const int location, const float* const matrix) noexcept
{
	glUniformMatrix3fv(location, 1, GL_FALSE, matrix);
}

void dooms::graphics::GraphicsAPI::UpdateConstantBuffer_mat4x4f(const int location, const float* const matrix) noexcept
{
	glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void* dooms::graphics::GraphicsAPI::MapBufferObjectToClientAddress
(
	const unsigned int bufferID,
	const unsigned long long offset,
	const unsigned long long length,
	const eBufferTarget bindBufferTarget, 
	const eMapBufferAccessOption mapBufferAccessOption
) noexcept
{
	GraphicsAPI::BindBuffer(bufferID, bindBufferTarget);
	return glMapBufferRange(opengl::GetGLBufferTarget(bindBufferTarget), offset, length, opengl::GetGLMapBufferAccessOption(mapBufferAccessOption));
}

unsigned dooms::graphics::GraphicsAPI::CreateTextureObject() noexcept
{
	unsigned int bufferID;
	glGenTextures(1, &bufferID);
	return bufferID;
}

void dooms::graphics::GraphicsAPI::DestroyTextureObject(const unsigned int textureObject) noexcept
{
	glDeleteTextures(1, &textureObject);
}

void dooms::graphics::GraphicsAPI::BindTextureObject(const unsigned int textureObject, const eTextureBindTarget textureBindTarget) noexcept
{
	glBindTexture(opengl::GetGLTextureBindTarget(textureBindTarget), textureObject);
}

void dooms::graphics::GraphicsAPI::ActivateTextureUnit(const unsigned int unitIndex) noexcept
{
	glActiveTexture(GL_TEXTURE0 + unitIndex);
}

void dooms::graphics::GraphicsAPI::BindTextureObjectAndActivateTextureUnit
(
	const unsigned int textureObject,
	const unsigned int unitIndex
) noexcept
{
	glBindTextureUnit(unitIndex, textureObject);
}

void dooms::graphics::GraphicsAPI::UnBindTextureObject(const eTextureBindTarget textureBindTarget) noexcept
{
	glBindTexture(opengl::GetGLTextureBindTarget(textureBindTarget), 0);
}

void dooms::graphics::GraphicsAPI::BlitFrameBuffer
(
	const unsigned int ReadFrameBufferObject,
	const unsigned int DrawFrameBufferObject,
	const int srcX0, const int srcY0, const int srcX1, const int srcY1,
	const int dstX0, const int dstY0, const int dstX1, const int dstY1,
	const GraphicsAPI::eBufferBitType mask,
	const GraphicsAPI::eImageInterpolation filter
)
{
	BindFrameBuffer(ReadFrameBufferObject, GraphicsAPI::eBindFrameBufferTarget::READ_FRAMEBUFFER);
	BindFrameBuffer(DrawFrameBufferObject, GraphicsAPI::eBindFrameBufferTarget::DRAW_FRAMEBUFFER);
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, opengl::GetGLBufferBitType(mask), opengl::GetGLImageInterpolation(filter));
}

float dooms::graphics::GraphicsAPI::GetTextureMetaDataFloat
(
	const unsigned int textureObject,
	const eTextureBindTarget textureBindTarget, 
	const unsigned int lodLevel,
	const eTextureMetaDataType textureMetaDataType
) noexcept
{
	float data;

	GraphicsAPI::BindTextureObject(textureObject, textureBindTarget);
	glGetTexLevelParameterfv(opengl::GetGLTextureBindTarget(textureBindTarget), lodLevel, opengl::GetGLTextureMataDataType(textureMetaDataType), &data);

	return data;
}

int dooms::graphics::GraphicsAPI::GetTextureMetaDataInt
(
	const unsigned int textureObject,
	const eTextureBindTarget textureBindTarget, 
	const unsigned int lodLevel,
	const eTextureMetaDataType textureMetaDataType
) noexcept
{
	int data;

	GraphicsAPI::BindTextureObject(textureObject, textureBindTarget);
	glGetTexLevelParameteriv(opengl::GetGLTextureBindTarget(textureBindTarget), lodLevel, opengl::GetGLTextureMataDataType(textureMetaDataType), &data);

	return data;
}

void dooms::graphics::GraphicsAPI::SetTextureParameterFloat
(
	const eTextureBindTarget textureBindTarget,
	const eTextureParameterType textureParameterType, 
	const float parameter
) noexcept
{
	glTexParameterf(opengl::GetGLTextureBindTarget(textureBindTarget), opengl::GetGLTextureParameterType(textureParameterType), parameter);
}

void dooms::graphics::GraphicsAPI::SetTextureParameterInt
(
	const eTextureBindTarget textureBindTarget,
	const eTextureParameterType textureParameterType, 
	const int parameter
) noexcept
{ 
	glTexParameteri(opengl::GetGLTextureBindTarget(textureBindTarget), opengl::GetGLTextureParameterType(textureParameterType), parameter);
}

void dooms::graphics::GraphicsAPI::SetTextureWrapMode_S(const eTextureBindTarget textureBindTarget, const eWrapMode wrapMode)
{
	glTexParameteri(opengl::GetGLTextureBindTarget(textureBindTarget), GL_TEXTURE_WRAP_S, opengl::GetGLTextureWrapMode(wrapMode));
}

void dooms::graphics::GraphicsAPI::SetTextureWrapMode_T(const eTextureBindTarget textureBindTarget, const eWrapMode wrapMode)
{
	glTexParameteri(opengl::GetGLTextureBindTarget(textureBindTarget), GL_TEXTURE_WRAP_T, opengl::GetGLTextureWrapMode(wrapMode));
}

void dooms::graphics::GraphicsAPI::SetTextureWrapMode_R(const eTextureBindTarget textureBindTarget, const eWrapMode wrapMode)
{
	glTexParameteri(opengl::GetGLTextureBindTarget(textureBindTarget), GL_TEXTURE_WRAP_R, opengl::GetGLTextureWrapMode(wrapMode));
}

void dooms::graphics::GraphicsAPI::SetMinFilter
(
	const eTextureBindTarget textureBindTarget,
	const eFilterMode filterMode
)
{
	glTexParameteri(opengl::GetGLTextureBindTarget(textureBindTarget), GL_TEXTURE_MIN_FILTER, opengl::GetGLTextureFilterMode(filterMode));
}

void dooms::graphics::GraphicsAPI::SetMagFilter
(
	const eTextureBindTarget textureBindTarget,
	const eFilterMode filterMode
)
{
	glTexParameteri(opengl::GetGLTextureBindTarget(textureBindTarget), GL_TEXTURE_MAG_FILTER, opengl::GetGLTextureFilterMode(filterMode));
}

unsigned char* dooms::graphics::GraphicsAPI::FetchTexturePixels
(
	const eTextureBindTarget textureBindTarget,
	const int lodLevel, 
	const eTextureComponentFormat textureComponentFormat, 
	const eDataType datatType,
	const unsigned long long bufferSize
) noexcept
{
	assert(bufferSize > 0);

	unsigned char* pixels = new unsigned char[bufferSize];

	glGetTexImage(opengl::GetGLTextureBindTarget(textureBindTarget), lodLevel, opengl::GetGLTextureComponentFormat(textureComponentFormat), opengl::GetGLDataType(datatType), reinterpret_cast<void*>(pixels));

	return pixels;
}

unsigned char* dooms::graphics::GraphicsAPI::ReadPixels
(
	const unsigned long bufferSize, 
	const int startX,
	const int startY, 
	const int width, 
	const int height,
	const dooms::graphics::GraphicsAPI::eTextureComponentFormat pixelFormat,
	const dooms::graphics::GraphicsAPI::eDataType dataType
)
{
	unsigned char* const buffer = new unsigned char[bufferSize];
	glReadPixels(startX, startY, width, height, opengl::GetGLTextureComponentFormat(pixelFormat), opengl::GetGLDataType(dataType), buffer);
	return buffer;
}

void dooms::graphics::GraphicsAPI::Define1DTextureStorageRequirement
(
	const eTextureBindTarget textureBindTarget,
	const unsigned int lodCount,
	const eTextureInternalFormat textureInternalFormat, 
	const unsigned long long width
)
{
	glTexStorage1D
	(
		opengl::GetGLTextureBindTarget(textureBindTarget),
		lodCount,
		opengl::GetGLTextureInternalFormat(textureInternalFormat),
		width
	);
}

void dooms::graphics::GraphicsAPI::Define2DTextureStorageRequirement
(
	const eTextureBindTarget textureBindTarget,
	const unsigned int lodCount,
	const eTextureInternalFormat textureInternalFormat, 
	const unsigned long long width,
	const unsigned long long height
)
{
	glTexStorage2D
	(
		opengl::GetGLTextureBindTarget(textureBindTarget),
		lodCount,
		opengl::GetGLTextureInternalFormat(textureInternalFormat),
		width,
		height
	);
}

void dooms::graphics::GraphicsAPI::Define3DTextureStorageRequirement
(
	const eTextureBindTarget textureBindTarget,
	const unsigned int lodCount,
	const eTextureInternalFormat textureInternalFormat, 
	const unsigned long long width,
	const unsigned long long height, 
	const unsigned long long depth
)
{
	glTexStorage3D
	(
		opengl::GetGLTextureBindTarget(textureBindTarget),
		lodCount,
		opengl::GetGLTextureInternalFormat(textureInternalFormat),
		width,
		height,
		depth
	);
}

void dooms::graphics::GraphicsAPI::Define1DCompressedTextureStorageRequirement
(
	const eTextureBindTarget textureBindTarget,
	const unsigned int createdLodCount,
	const eTextureCompressedInternalFormat textureInternalFormat,
	const unsigned long long width
)
{
	glTexStorage1D
	(
		opengl::GetGLTextureBindTarget(textureBindTarget),
		createdLodCount,
		opengl::GetTextureCompressedInternalFormat(textureInternalFormat),
		width
	);
}

void dooms::graphics::GraphicsAPI::Define2DCompressedTextureStorageRequirement
(
	const eTextureBindTarget textureBindTarget,
	const unsigned int createdLodCount,
	const eTextureCompressedInternalFormat textureInternalFormat,
	const unsigned long long width,
	const unsigned long long height
)
{
	glTexStorage2D
	(
		opengl::GetGLTextureBindTarget(textureBindTarget),
		createdLodCount,
		opengl::GetTextureCompressedInternalFormat(textureInternalFormat),
		width,
		height
	);
}

void dooms::graphics::GraphicsAPI::Define3DCompressedTextureStorageRequirement
(
	const eTextureBindTarget textureBindTarget,
	const unsigned int createdLodCount,
	const eTextureCompressedInternalFormat textureInternalFormat,
	const unsigned long long width,
	const unsigned long long height,
	const unsigned long long depth
)
{
	glTexStorage3D
	(
		opengl::GetGLTextureBindTarget(textureBindTarget),
		createdLodCount,
		opengl::GetTextureCompressedInternalFormat(textureInternalFormat),
		width,
		height,
		depth
	);
}


void dooms::graphics::GraphicsAPI::UploadPixelsTo1DTexture
(
	const eTargetTexture targetTexture,
	const unsigned int lodLevel,
	const unsigned int xOffset,
	const unsigned long long width,
	const eTextureComponentFormat textureComponentFormat,
	const eDataType dataType, 
	const void* const pixelDatas
)
{
	glTexSubImage1D
	(
		opengl::GetGLTargetTexture(targetTexture),
		lodLevel,
		xOffset,
		width,
		opengl::GetGLTextureComponentFormat(textureComponentFormat),
		opengl::GetGLDataType(dataType),
		pixelDatas
	);
}

void dooms::graphics::GraphicsAPI::UploadPixelsTo2DTexture
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
)
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

void dooms::graphics::GraphicsAPI::UploadPixelsTo3DTexture
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
)
{
	glTexSubImage3D
	(
		opengl::GetGLTargetTexture(targetTexture),
		lodLevel,
		xOffset,
		yOffset,
		zOffset,
		width,
		height,
		depth,
		opengl::GetGLTextureComponentFormat(textureComponentFormat),
		opengl::GetGLDataType(dataType),
		pixelDatas
	);
}


void dooms::graphics::GraphicsAPI::UploadPixelsTo1DCompressedTexture
(
	const eTargetTexture targetTexture,
	const unsigned int lodLevel,
	const unsigned int xOffset,
	const unsigned long long width,
	const eTextureCompressedInternalFormat textureCompressedInternalFormat,
	const unsigned long long imgSize,
	const void* const pixelDatas
)
{
	glCompressedTexSubImage1D
	(
		opengl::GetGLTargetTexture(targetTexture),
		lodLevel,
		xOffset,
		width,
		opengl::GetTextureCompressedInternalFormat(textureCompressedInternalFormat),
		imgSize,
		pixelDatas
	);
}

void dooms::graphics::GraphicsAPI::UploadPixelsTo2DCompressedTexture
(
	const eTargetTexture targetTexture,
	const unsigned int lodLevel,
	const unsigned int xOffset,
	const unsigned int yOffset,
	const unsigned long long width,
	const unsigned long long height,
	const eTextureCompressedInternalFormat textureCompressedInternalFormat,
	const unsigned long long imgSize,
	const void* const pixelDatas
)
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
		imgSize,
		pixelDatas
	);
}

void dooms::graphics::GraphicsAPI::UploadPixelsTo3DCompressedTexture
(
	const eTargetTexture targetTexture,
	const unsigned int lodLevel,
	const unsigned int xOffset,
	const unsigned int yOffset,
	const unsigned int zOffset,
	const unsigned long long width,
	const unsigned long long height,
	const unsigned long long depth,
	const eTextureCompressedInternalFormat textureCompressedInternalFormat,
	const unsigned long long imgSize,
	const void* const pixelDatas
)
{
	glCompressedTexSubImage3D
	(
		opengl::GetGLTargetTexture(targetTexture),
		lodLevel,
		xOffset,
		yOffset,
		zOffset,
		width,
		height,
		depth,
		opengl::GetTextureCompressedInternalFormat(textureCompressedInternalFormat),
		imgSize,
		pixelDatas
	);
}

int dooms::graphics::GraphicsAPI::GetConstantBufferBindingPoint
(
	const unsigned constantBufferObject,
	const unsigned blockIndex
)
{
	int uniformBlockBindingPoint;
	glGetActiveUniformBlockiv(constantBufferObject, blockIndex, GL_UNIFORM_BLOCK_BINDING, &uniformBlockBindingPoint);
	return uniformBlockBindingPoint;
}

int dooms::graphics::GraphicsAPI::GetConstantBufferDataSize
(
	const unsigned constantBufferObject,
	const unsigned blockIndex
)
{
	int dataSize;
	glGetActiveUniformBlockiv(constantBufferObject, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &dataSize);
	return dataSize;
}

int dooms::graphics::GraphicsAPI::GetConstantBufferBlockCount
(
	const unsigned constantBufferObject
)
{
	int blockCount;
	glGetProgramiv(constantBufferObject, GL_ACTIVE_UNIFORM_BLOCKS, &blockCount);
	return blockCount;
}

int dooms::graphics::GraphicsAPI::GetConstantBufferUniformLocation
(
	const unsigned constantBufferObject,
	const char* const uniformStr
)
{
	return glGetUniformLocation(constantBufferObject, uniformStr);
}


void dooms::graphics::GraphicsAPI::CompileShader
(
	const unsigned int shaderObject,
	const char* const shaderText
) noexcept
{
	glShaderSource(shaderObject, 1, &shaderText, NULL);
	glCompileShader(shaderObject);
}

