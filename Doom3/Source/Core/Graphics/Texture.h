#pragma once

#include <unordered_map>

#include "Graphics_Core.h"


namespace doom
{
	namespace graphics
	{
		/// <summary>
		/// reference : https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
		/// </summary>
		class Texture
		{
		public:

			enum class eTextureType : unsigned int {
				NONE = 0,
				DIFFUSE = 1,
				SPECULAR = 2,
				AMBIENT = 3,
				EMISSIVE = 4,
				HEIGHT = 5,
				NORMALS = 6,
				SHININESS = 7,
				OPACITY = 8,
				DISPLACEMENT = 9,
				LIGHTMAP = 10,
				REFLECTION = 11,
				BASE_COLOR = 12,
				NORMAL_CAMERA = 13,
				EMISSION_COLOR = 14,
				METALNESS = 15,
				DIFFUSE_ROUGHNESS = 16,
				AMBIENT_OCCLUSION = 17,
				UNKNOWN = 18,
			};

			enum class eBindTarget : unsigned int
			{
				TEXTURE_1D = GL_TEXTURE_1D,
				TEXTURE_2D = GL_TEXTURE_2D,
				TEXTURE_3D = GL_TEXTURE_3D,
				TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
				TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
				TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
				TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
				TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
				TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
				TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
				TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
			};
			static constexpr eBindTarget DEFAULT_BIND_TARGET = eBindTarget::TEXTURE_2D;

			enum class eTargetTexture : unsigned int
			{
				TEXTURE_2D = GL_TEXTURE_2D,
				PROXY_TEXTURE_2D = GL_PROXY_TEXTURE_2D,
				TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
				PROXY_TEXTURE_1D_ARRAY = GL_PROXY_TEXTURE_1D_ARRAY,
				TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
				PROXY_TEXTURE_RECTANGLE = GL_PROXY_TEXTURE_RECTANGLE,
				TEXTURE_CUBE_MAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				TEXTURE_CUBE_MAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
				TEXTURE_CUBE_MAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
				TEXTURE_CUBE_MAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
				TEXTURE_CUBE_MAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
				TEXTURE_CUBE_MAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
				PROXY_TEXTURE_CUBE_MAP = GL_PROXY_TEXTURE_CUBE_MAP
			};
			static constexpr eTargetTexture DEFAULT_TARGET_TEXTURE = eTargetTexture::TEXTURE_2D;

			enum class eInternalFormat : unsigned int
			{
				DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
				DEPTH_STENCIL = GL_DEPTH_STENCIL,
				RED = GL_RED,
				RG = GL_RG,
				RGB = GL_RGB,
				RGBA = GL_RGBA,
				R8 = GL_R8,
				R8_SNORM = GL_R8_SNORM,
				R16 = GL_R16,
				R16_SNORM = GL_R16_SNORM,
				RG8 = GL_RG8,
				RG8_SNORM = GL_RG8_SNORM,
				RG16 = GL_RG16,
				RG16_SNORM = GL_RG16_SNORM,
				R3_G3_B2 = GL_R3_G3_B2,
				RGB4 = GL_RGB4,
				RGB5 = GL_RGB5,
				RGB8 = GL_RGB8,
				RGB8_SNORM = GL_RGB8_SNORM,
				RGB10 = GL_RGB10,
				RGB12 = GL_RGB12,
				RGB16_SNORM = GL_RGB16_SNORM,
				RGBA2 = GL_RGBA2,
				RGBA4 = GL_RGBA4,
				RGB5_A1 = GL_RGB5_A1,
				RGBA8 = GL_RGBA8,
				RGBA8_SNORM = GL_RGBA8_SNORM,
				RGB10_A2 = GL_RGB10_A2,
				RGB10_A2UI = GL_RGB10_A2UI,
				RGBA12 = GL_RGBA12,
				RGBA16 = GL_RGBA16,
				SRGB8 = GL_SRGB8,
				SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
				R16F = GL_R16F,
				RG16F = GL_RG16F,
				RGB16F = GL_RGB16F,
				RGBA16F = GL_RGBA16F,
				R32F = GL_R32F,
				RG32F = GL_RG32F,
				RGB32F = GL_RGB32F,
				RGBA32F = GL_RGBA32F,
				R11F_G11F_B10F = GL_R11F_G11F_B10F,
				RGB9_E5 = GL_RGB9_E5,
				R8I = GL_R8I,
				R8UI = GL_R8UI,
				R16I = GL_R16I,
				R16UI = GL_R16UI,
				R32I = GL_R32I,
				R32UI = GL_R32UI,
				RG8I = GL_RG8I,
				RG8UI = GL_RG8UI,
				RG16I = GL_RG16I,
				RG16UI = GL_RG16UI,
				RG32I = GL_RG32I,
				RG32UI = GL_RG32UI,
				RGB8I = GL_RGB8I,
				RGB8UI = GL_RGB8UI,
				RGB16I = GL_RGB16I,
				RGB16UI = GL_RGB16UI,
				RGB32I = GL_RGB32I,
				RGB32UI = GL_RGB32UI,
				RGBA8I = GL_RGBA8I,
				RGBA8UI = GL_RGBA8UI,
				RGBA16I = GL_RGBA16I,
				RGBA16UI = GL_RGBA16UI,
				RGBA32I = GL_RGBA32I,
				RGBA32UI = GL_RGBA32UI,
				COMPRESSED_RED = GL_COMPRESSED_RED,
				COMPRESSED_RG = GL_COMPRESSED_RG,
				COMPRESSED_RGB = GL_COMPRESSED_RGB,
				COMPRESSED_RGBA = GL_COMPRESSED_RGBA,
				COMPRESSED_SRGB = GL_COMPRESSED_SRGB,
				COMPRESSED_SRGB_ALPHA = GL_COMPRESSED_SRGB_ALPHA,
				COMPRESSED_RED_RGTC1 = GL_COMPRESSED_RED_RGTC1,
				COMPRESSED_SIGNED_RED_RGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1,
				COMPRESSED_RG_RGTC2 = GL_COMPRESSED_RG_RGTC2,
				COMPRESSED_SIGNED_RG_RGTC2 = GL_COMPRESSED_SIGNED_RG_RGTC2,
				COMPRESSED_RGBA_BPTC_UNORM = GL_COMPRESSED_RGBA_BPTC_UNORM,
				COMPRESSED_SRGB_ALPHA_BPTC_UNORM = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
				COMPRESSED_RGB_BPTC_SIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
				COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT,

			};
			static constexpr eInternalFormat DEFAULT_INTERNAL_FORMAT = eInternalFormat::RGBA;

			enum class eDataFormat : unsigned int
			{
				RED = GL_RED,
				RG = GL_RG,
				RGB = GL_RGB,
				BGR = GL_BGR,
				RGBA = GL_RGBA,
				BGRA = GL_BGRA,
				RED_INTEGER = GL_RED_INTEGER,
				RG_INTEGER = GL_RG_INTEGER,
				RGB_INTEGER = GL_RGB_INTEGER,
				BGR_INTEGER = GL_BGR_INTEGER,
				RGBA_INTEGER = GL_RGBA_INTEGER,
				BGRA_INTEGER = GL_BGRA_INTEGER,
				STENCIL_INDEX = GL_STENCIL_INDEX,
				DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
				DEPTH_STENCIL = GL_DEPTH_STENCIL
			};
			static constexpr eDataFormat DEFAULT_DATA_FORMAT = eDataFormat::RGBA;

			enum class eDataType : unsigned int
			{
				UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
				BYTE = GL_BYTE,
				UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
				SHORT = GL_SHORT,
				UNSIGNED_INT = GL_UNSIGNED_INT,
				INT = GL_INT,
				HALF_FLOAT = GL_HALF_FLOAT,
				FLOAT = GL_FLOAT,
				UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
				UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
				UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
				UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
				UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
				UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
				UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
				UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
				UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
				UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
				UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
				UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
			};
			static constexpr eDataType DEFAULT_DATA_TYPE = eDataType::UNSIGNED_BYTE;

		private:

		protected:
			unsigned int mID;

			ONLY_DEBUG(static inline std::unordered_map<eBindTarget, unsigned int> mCurrentBoundId{};)

		public:

			Texture(eTextureType textureType, eBindTarget bindTarget,
				eTargetTexture target, eInternalFormat internalFormat, unsigned int width, unsigned int height, eDataFormat format, eDataType type, const void* data);
			virtual ~Texture();

			const eTextureType mTextureType;
			const eBindTarget mBindTarget;

			const eTargetTexture mTarget;
			const eInternalFormat mInternalFormat;
			const unsigned int mWidth;
			const unsigned int mHeight;
			const eDataFormat mDataFormat;
			const eDataType mDataType;








			void BindTexture();
			void UnBindTexture();
			void ActiveTexture(unsigned int index);
			/// <summary>
			/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
			/// </summary>
			/// <param name="target"></param>
			/// <param name="level"></param>
			/// <param name="internalformat"></param>
			/// <param name="width"></param>
			/// <param name="height"></param>
			/// <param name="border"></param>
			/// <param name="format"></param>
			/// <param name="type"></param>
			/// <param name="data"></param>
			virtual void TexImage2D(
				int level,
				eInternalFormat internalformat,
				int width,
				int height,
				eDataFormat format,
				eDataType type,
				const void* data
			) = 0;

			enum class eTextureParameterType : unsigned int
			{
				DEPTH_STENCIL_TEXTURE_MODE = GL_DEPTH_STENCIL_TEXTURE_MODE,
				TEXTURE_BASE_LEVEL = GL_TEXTURE_BASE_LEVEL,
				TEXTURE_COMPARE_FUNC = GL_TEXTURE_COMPARE_FUNC,
				TEXTURE_COMPARE_MODE = GL_TEXTURE_COMPARE_MODE,
				TEXTURE_LOD_BIAS = GL_TEXTURE_LOD_BIAS,
				TEXTURE_MIN_FILTER = GL_TEXTURE_MIN_FILTER,
				TEXTURE_MAG_FILTER = GL_TEXTURE_MAG_FILTER,
				TEXTURE_MIN_LOD = GL_TEXTURE_MIN_LOD,
				TEXTURE_MAX_LOD = GL_TEXTURE_MAX_LOD,
				TEXTURE_MAX_LEVEL = GL_TEXTURE_MAX_LEVEL,
				TEXTURE_SWIZZLE_R = GL_TEXTURE_SWIZZLE_R,
				TEXTURE_SWIZZLE_G = GL_TEXTURE_SWIZZLE_G,
				TEXTURE_SWIZZLE_B = GL_TEXTURE_SWIZZLE_B,
				TEXTURE_SWIZZLE_A = GL_TEXTURE_SWIZZLE_A,
				TEXTURE_WRAP_S = GL_TEXTURE_WRAP_S,
				TEXTURE_WRAP_T = GL_TEXTURE_WRAP_T,
				TEXTURE_WRAP_R = GL_TEXTURE_WRAP_R
			};

			enum class eTextureParameterValue : unsigned int
			{
				NEAREST = GL_NEAREST,
				LINEAR = GL_LINEAR,
				NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
				LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
				NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
				LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
				CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
				CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
				MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
				REPEAT = GL_REPEAT,
				MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE,
			};

			void TexParameterf(eBindTarget target, eTextureParameterType pname, eTextureParameterValue param);
			void TexParameteri(eBindTarget target, eTextureParameterType pname, eTextureParameterValue param);
			void TexParameterf(eBindTarget target, eTextureParameterType pname, unsigned int param);
			void TexParameteri(eBindTarget target, eTextureParameterType pname, float param);
		};
	}
}