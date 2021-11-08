#pragma once

#include <memory>

#include "../Graphics_Core.h"
#include "../OverlapBindChecker.h"
#include "../Buffer/BufferID.h"
#include "TextureFormat.h"

namespace DirectX
{
	struct Image;
	class ScratchImage;
}


namespace dooms
{
	namespace graphics
	{
		/// <summary>
		/// reference : https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
		/// </summary>
		class DOOM_API D_CLASS Texture : public DObject
		{
			DOBJECT_ABSTRACT_CLASS_BODY(Texture, dooms::eDOBJECT_ClassFlags::NonCopyable);
			DOBJECT_CLASS_BASE_CHAIN(DObject)

		public:

			enum class D_ENUM eTextureType : UINT32 {
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

			enum class D_ENUM eBindTarget : UINT32
			{
				NONE = 0,
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

			/// <summary>
			/// why use this?
			/// Yeah i can use magic_enum::enum_index
			/// but to do that, i should increase magic_enum::MAGIC_ENUM_RANGE_MAX.
			/// Then this will increase compile time dramatically
			/// 
			/// and if you wanna get real index of enum value, you should use it at compiletime,
			/// 
			/// </summary>
			/// <returns></returns>
			inline static size_t GetArbitraryIndexOfeBindTarget(const eBindTarget bindTarget)
			{
				if (bindTarget == eBindTarget::TEXTURE_2D)
				{
					return 1;
				}

				//TODO : ���ں��� �ؽ��Լ��� ARRAY �۰� �ؼ� �ؽ����̺� ���� �� ������ ������. O(1)���� �� ��������
				switch (bindTarget)
				{
				case eBindTarget::TEXTURE_1D:
					return 0;
				case eBindTarget::TEXTURE_3D:
					return 2;
				case eBindTarget::TEXTURE_1D_ARRAY:
					return 3;
				case eBindTarget::TEXTURE_2D_ARRAY:
					return 4;
				case eBindTarget::TEXTURE_RECTANGLE:
					return 5;
				case eBindTarget::TEXTURE_CUBE_MAP:
					return 6;
				case eBindTarget::TEXTURE_CUBE_MAP_ARRAY:
					return 7;
				case eBindTarget::TEXTURE_BUFFER:
					return 8;
				case eBindTarget::TEXTURE_2D_MULTISAMPLE:
					return 9;
				case eBindTarget::TEXTURE_2D_MULTISAMPLE_ARRAY:
					return 10;
				default:
					NEVER_HAPPEN;
				}
			}
			
			enum class D_ENUM eTargetTexture : UINT32
			{
				TEXTURE_1D = GL_TEXTURE_1D,
				PROXY_TEXTURE_1D = GL_PROXY_TEXTURE_1D,
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
				PROXY_TEXTURE_CUBE_MAP = GL_PROXY_TEXTURE_CUBE_MAP,
				TEXTURE_3D = GL_TEXTURE_3D
			};
			static constexpr eTargetTexture DEFAULT_TARGET_TEXTURE = eTargetTexture::TEXTURE_2D;



			static constexpr eTextureInternalFormat DEFAULT_INTERNAL_FORMAT = eTextureInternalFormat::RGBA;

			
			static constexpr eTextureComponentFormat DEFAULT_DATA_FORMAT = eTextureComponentFormat::RGBA;

			enum class D_ENUM eDataType : UINT32
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
				UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
				UNSIGNED_INT_24_8 = GL_UNSIGNED_INT_24_8,
				FLOAT_32_UNSIGNED_INT_24_8_REV = GL_FLOAT_32_UNSIGNED_INT_24_8_REV
			};
			static constexpr eDataType DEFAULT_DATA_TYPE = eDataType::UNSIGNED_BYTE;

			enum class D_ENUM eTextureParameterType : UINT32
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

			enum class D_ENUM eTextureParameterValue : UINT32
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

			enum class D_ENUM eWrapMode : UINT32
			{
				CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
				CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
				MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
				REPEAT = GL_REPEAT,
				MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE,
			};

			enum class D_ENUM eFilterMode : UINT32
			{
				NEAREST = GL_NEAREST,
				LINEAR = GL_LINEAR,
				NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
				LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
				NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
				LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
			};

		protected:

			inline static const char BIND_TARGET_TAG[]{ "BIND_TARGET" };
			static inline const char ACTIVE_TEXTURE_TAG[]{ "ActiveTexture" };

			BufferID mBufferID{};

			INT32 mTextureBufferSize;

			eWrapMode mWrapS;
			eWrapMode mWrapT;
			eWrapMode mWrapR;

			eTextureType mTextureType = eTextureType::NONE;
			eBindTarget mBindTarget = eBindTarget::NONE;

			eTargetTexture mTarget;
			eTextureInternalFormat mInternalFormat = eTextureInternalFormat::NONE;
			eTextureCompressedInternalFormat mCompressedInternalFormat = eTextureCompressedInternalFormat::NONE;
			UINT32 mWidth;
			UINT32 mHeight;
			eTextureComponentFormat mDataFormat = eTextureComponentFormat::NONE;
			eDataType mDataType;
			
			void DestroyTextureBufferObject();

		public:

			

			Texture();
			Texture(const Texture&) = delete;
			Texture& operator=(const Texture&) noexcept = delete;

			Texture(Texture&&) noexcept = default;
			Texture& operator=(Texture&&) noexcept = default;

			/// <summary>
			/// for 1d texture
			/// </summary>
			Texture(eTextureType textureType, eBindTarget bindTarget,
				eTargetTexture targetTexture, eTextureInternalFormat internalFormat, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, eTextureComponentFormat format, eDataType type);

			/// <summary>
			/// for 2d texture
			/// </summary>
			/// <param name="textureType"></param>
			/// <param name="bindTarget"></param>
			/// <param name="target"></param>
			/// <param name="internalFormat"></param>
			/// <param name="width"></param>
			/// <param name="height"></param>
			/// <param name="format"></param>
			/// <param name="type"></param>
			/// <param name="data"></param>
			Texture(eTextureType textureType, eBindTarget bindTarget,
				eTargetTexture targetTexture, eTextureInternalFormat internalFormat, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type);

			virtual ~Texture();
			virtual void OnEndContructor();

			void InitializeTexture(eTextureType textureType, eBindTarget bindTarget,
				eTargetTexture targetTexture, eTextureInternalFormat internalFormat, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, eTextureComponentFormat format, eDataType type);

			/// <summary>
			/// for 2d texture
			/// </summary>
			/// <param name="textureType"></param>
			/// <param name="bindTarget"></param>
			/// <param name="target"></param>
			/// <param name="internalFormat"></param>
			/// <param name="width"></param>
			/// <param name="height"></param>
			/// <param name="format"></param>
			/// <param name="type"></param>
			/// <param name="data"></param>
			void InitializeTexture(eTextureType textureType, eBindTarget bindTarget,
				eTargetTexture targetTexture, eTextureInternalFormat internalFormat, eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, eTextureComponentFormat format, eDataType type);

			UINT32 GetBufferID() const
			{
				return mBufferID;
			}
			

			//	BindTarget
			//					--->	Texture Buffer ID
			//	BindingPoint
			// 
			//
			//
			//
			//

			FORCE_INLINE void BindTexture() const noexcept
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID_WITH_DOUBLE_INDEX(BIND_TARGET_TAG, GetArbitraryIndexOfeBindTarget(mBindTarget), D_OVERLAP_BIND_GET_BIND_ID(ACTIVE_TEXTURE_TAG), mBufferID))
				{
					glBindTexture(static_cast<UINT32>(mBindTarget), mBufferID);
				}
			}
			FORCE_INLINE void ActiveTexture(UINT32 bindingPoint) const noexcept
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(ACTIVE_TEXTURE_TAG, bindingPoint))
				{
					glActiveTexture(GL_TEXTURE0 + bindingPoint);
				}
			}


			FORCE_INLINE void UnBindTexture() const noexcept
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID_WITH_DOUBLE_INDEX(BIND_TARGET_TAG, GetArbitraryIndexOfeBindTarget(mBindTarget), D_OVERLAP_BIND_GET_BIND_ID(ACTIVE_TEXTURE_TAG), 0))
				{
					glBindTexture(static_cast<UINT32>(mBindTarget), 0);
				}
			}

			FORCE_INLINE void BindTextureWithUnit(UINT32 bindingPoint) const
			{
				if (
					D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID_WITH_DOUBLE_INDEX(BIND_TARGET_TAG, GetArbitraryIndexOfeBindTarget(mBindTarget), bindingPoint, mBufferID)
				)
				{
					glBindTextureUnit(bindingPoint, mBufferID);
				}
				//glActiveTexture(GL_TEXTURE0 + bindingPoint);
				//glBindTexture(GL_TEXTURE_2D, mBufferID);
			}

			virtual inline void TexImage1D(
				INT32 level, const void* data
			) const = 0;

			
			/// <summary>
			/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
			/// </summary>
			/// <param name="level"></param>
			/// <param name="data"></param>
			virtual inline void TexImage2D(
				INT32 level, const void* data
			) const  = 0;

			UINT32 GetTextureBufferID() const;

			void SetWrapMode(eWrapMode wrapMode, bool bBind);
			void SetFilterMin(eFilterMode filterMode, bool bBind);
			void SetFilterMax(eFilterMode filterMode, bool bBind);

			eWrapMode GetWrapModeS() const;
			eWrapMode GetWrapModeT() const;
			eWrapMode GetWrapModeR() const;

			FORCE_INLINE eTextureType GetTextureType() const
			{
				return mTextureType;
			}
			FORCE_INLINE eBindTarget GetBindTarget() const
			{
				return mBindTarget;
			}
			FORCE_INLINE eTargetTexture GetTarget() const
			{
				return mTarget;
			}
			FORCE_INLINE eTextureInternalFormat GetInternalFormat() const
			{
				return mInternalFormat;
			}
			FORCE_INLINE eTextureCompressedInternalFormat GetCompressedInternalFormat() const
			{
				return mCompressedInternalFormat;
			}
			FORCE_INLINE UINT32 GetWidth() const
			{
				return mWidth;
			}
			FORCE_INLINE UINT32 GetHeight() const
			{
				return mHeight;
			}
			FORCE_INLINE eTextureComponentFormat GetDataFormat() const
			{
				return mDataFormat;
			}
			FORCE_INLINE eDataType GetDataType() const
			{
				return mDataType;
			}

			FORCE_INLINE void TexParameterf(eBindTarget target, eTextureParameterType pname, eTextureParameterValue param) const noexcept
			{
				glTexParameterf(static_cast<UINT32>(target), static_cast<UINT32>(pname), static_cast<FLOAT32>(param));
			}
			FORCE_INLINE void TexParameteri(eBindTarget target, eTextureParameterType pname, eTextureParameterValue param) const noexcept
			{
				glTexParameteri(static_cast<UINT32>(target), static_cast<UINT32>(pname), static_cast<INT32>(param));
			}
			FORCE_INLINE void TexParameterf(eBindTarget target, eTextureParameterType pname, FLOAT32 param) const noexcept
			{
				glTexParameterf(static_cast<UINT32>(target), static_cast<UINT32>(pname), param);
			}
			FORCE_INLINE void TexParameteri(eBindTarget target, eTextureParameterType pname, INT32 param) const noexcept
			{
				glTexParameteri(static_cast<UINT32>(target), static_cast<UINT32>(pname), param);
			}

			enum class D_ENUM eTextureMataDataType : UINT32
			{
				TEXTURE_WIDTH = GL_TEXTURE_WIDTH,
				TEXTURE_HEIGHT = GL_TEXTURE_HEIGHT,
				TEXTURE_DEPTH = GL_TEXTURE_DEPTH,
				TEXTURE_INTERNAL_FORMAT = GL_TEXTURE_INTERNAL_FORMAT,
				TEXTURE_RED_SIZE = GL_TEXTURE_RED_SIZE,
				TEXTURE_GREEN_SIZE = GL_TEXTURE_GREEN_SIZE,
				TEXTURE_BLUE_SIZE = GL_TEXTURE_BLUE_SIZE,
				TEXTURE_ALPHA_SIZE = GL_TEXTURE_ALPHA_SIZE,
				TEXTURE_DEPTH_SIZE = GL_TEXTURE_DEPTH_SIZE,
				TEXTURE_COMPRESSED = GL_TEXTURE_COMPRESSED,
				TEXTURE_COMPRESSED_IMAGE_SIZE = GL_TEXTURE_COMPRESSED_IMAGE_SIZE,
				TEXTURE_BUFFER_OFFSET = GL_TEXTURE_BUFFER_OFFSET, // available only if the GL version is 4.3 or greater.
				TEXTURE_BUFFER_SIZE = GL_TEXTURE_BUFFER_SIZE // available only if the GL version is 4.3 or greater.
			};

			FLOAT32 GetTextureMetaDataFLOAT32(const INT32 lodLevel, const eTextureMataDataType textureMetaDataType) const;
			INT32 GetTextureMetaDataINT32(const INT32 lodLevel, const eTextureMataDataType textureMetaDataType) const;

			enum class D_ENUM ePixelFormat : UINT32
			{
				STENCIL_INDEX = GL_STENCIL_INDEX,
				DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
				DEPTH_STENCIL = GL_DEPTH_STENCIL,
				RED = GL_RED,
				GREEN = GL_GREEN,
				BLUE = GL_BLUE,
				RG = GL_RG,
				RGB = GL_RGB,
				RGBA = GL_RGBA,
				BGR = GL_BGR,
				BGRA = GL_BGRA,
				RED_INTEGER = GL_RED_INTEGER,
				GREEN_INTEGER = GL_GREEN_INTEGER,
				BLUE_INTEGER = GL_BLUE_INTEGER,
				RG_INTEGER = GL_RG_INTEGER,
				RGB_INTEGER = GL_RGB_INTEGER,
				RGBA_INTEGER = GL_RGBA_INTEGER,
				STENCILBGR_INTEGER_INDEX = GL_BGR_INTEGER,
				BGRA_INTEGER = GL_BGRA_INTEGER
			};
			
			
			/// <summary>
			/// This function is really really fxcking slow, Don't use this at release build
			///	I can optimize this, But I want more safe way
			/// </summary>
			/// <param name="lodLevel"></param>
			/// <param name="pixelFormat"></param>
			/// <returns></returns>
			const std::unique_ptr<UINT8[]> GetTexturePixels(const INT32 lodLevel) const;
			UINT8* GetTexturePixelsUnsafe(const INT32 lodLevel) const;

			INT32 GetTextureBufferSize(const INT32 lodLevel) const;

			static INT32 GetTextureBufferSizeStatic
			(
				const INT32 width, 
				const INT32 height, 
				const eTextureComponentFormat dataFormat,
				const eDataType dataType
			);

		};
	}
}