#pragma once

#include <memory>

#include "../Graphics_Core.h"
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include "../OverlapBindChecker.h"
#include "../Buffer/BufferID.h"

#include "Texture.reflection.h"
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
			GENERATE_BODY()
			

		public:
			
			static constexpr GraphicsAPI::eTextureBindTarget DEFAULT_BIND_TARGET = GraphicsAPI::eTextureBindTarget::TEXTURE_2D;

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
			inline static size_t GetArbitraryIndexOfeBindTarget(const GraphicsAPI::eTextureBindTarget bindTarget)
			{
				if (bindTarget == GraphicsAPI::eTextureBindTarget::TEXTURE_2D)
				{
					return 1;
				}

				//TODO : ���ں��� �ؽ��Լ��� ARRAY �۰� �ؼ� �ؽ����̺� ���� �� ������ ������. O(1)���� �� ��������
				switch (bindTarget)
				{
				case GraphicsAPI::eTextureBindTarget::TEXTURE_1D:
					return 0;
				case GraphicsAPI::eTextureBindTarget::TEXTURE_3D:
					return 2;
				case GraphicsAPI::eTextureBindTarget::TEXTURE_1D_ARRAY:
					return 3;
				case GraphicsAPI::eTextureBindTarget::TEXTURE_2D_ARRAY:
					return 4;
				case GraphicsAPI::eTextureBindTarget::TEXTURE_RECTANGLE:
					return 5;
				case GraphicsAPI::eTextureBindTarget::TEXTURE_CUBE_MAP:
					return 6;
				case GraphicsAPI::eTextureBindTarget::TEXTURE_CUBE_MAP_ARRAY:
					return 7;
				case GraphicsAPI::eTextureBindTarget::_TEXTURE_BUFFER:
					return 8;
				case GraphicsAPI::eTextureBindTarget::TEXTURE_2D_MULTISAMPLE:
					return 9;
				case GraphicsAPI::eTextureBindTarget::TEXTURE_2D_MULTISAMPLE_ARRAY:
					return 10;
				default:
					NEVER_HAPPEN;
				}
			}
			
			
			static constexpr GraphicsAPI::eTargetTexture DEFAULT_TARGET_TEXTURE = GraphicsAPI::eTargetTexture::TARGET_TEXTURE_TEXTURE_2D;



			static constexpr GraphicsAPI::eTextureInternalFormat DEFAULT_INTERNAL_FORMAT = GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_RGBA;

			
			static constexpr GraphicsAPI::eTextureComponentFormat DEFAULT_DATA_FORMAT = GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_RGBA;

			static constexpr GraphicsAPI::eDataType DEFAULT_DATA_TYPE = GraphicsAPI::eDataType::UNSIGNED_BYTE;

			
		private:

			void OnSetPendingKill() override;

		protected:

			inline static const char BIND_TARGET_TAG[]{ "BIND_TARGET" };
			static inline const char ACTIVE_TEXTURE_TAG[]{ "ActiveTexture" };

			BufferID mBufferID{};

			INT32 mTextureBufferSize;

			GraphicsAPI::eWrapMode mWrapS;
			GraphicsAPI::eWrapMode mWrapT;
			GraphicsAPI::eWrapMode mWrapR;

			GraphicsAPI::eTextureType mTextureType = GraphicsAPI::eTextureType::TextureType_NONE;
			GraphicsAPI::eTextureBindTarget mBindTarget = GraphicsAPI::eTextureBindTarget::TextureBindTarget_NONE;

			GraphicsAPI::eTargetTexture mTarget;
			GraphicsAPI::eTextureInternalFormat mInternalFormat = GraphicsAPI::eTextureInternalFormat::TEXTURE_INTERNAL_FORMAT_NONE;
			GraphicsAPI::eTextureCompressedInternalFormat mCompressedInternalFormat = GraphicsAPI::eTextureCompressedInternalFormat::TEXTURE_COMPRESSED_INTERNAL_FORMAT_NONE;
			UINT32 mWidth;
			UINT32 mHeight;
			GraphicsAPI::eTextureComponentFormat mDataFormat = GraphicsAPI::eTextureComponentFormat::TEXTURE_COMPONENT_FORMAT_NONE;
			GraphicsAPI::eDataType mDataType;
			
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
			Texture(GraphicsAPI::eTextureType textureType, GraphicsAPI::eTextureBindTarget bindTarget,
				GraphicsAPI::eTargetTexture targetTexture, GraphicsAPI::eTextureInternalFormat internalFormat, GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, GraphicsAPI::eTextureComponentFormat format, GraphicsAPI::eDataType type);

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
			Texture(GraphicsAPI::eTextureType textureType, GraphicsAPI::eTextureBindTarget bindTarget,
				GraphicsAPI::eTargetTexture targetTexture, GraphicsAPI::eTextureInternalFormat internalFormat, GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, GraphicsAPI::eTextureComponentFormat format, GraphicsAPI::eDataType type);

			virtual ~Texture();
			virtual void OnEndContructor();

			void InitializeTexture(GraphicsAPI::eTextureType textureType, GraphicsAPI::eTextureBindTarget bindTarget,
				GraphicsAPI::eTargetTexture targetTexture, GraphicsAPI::eTextureInternalFormat internalFormat, GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, GraphicsAPI::eTextureComponentFormat format, GraphicsAPI::eDataType type);

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
			void InitializeTexture(GraphicsAPI::eTextureType textureType, GraphicsAPI::eTextureBindTarget bindTarget,
				GraphicsAPI::eTargetTexture targetTexture, GraphicsAPI::eTextureInternalFormat internalFormat, GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, UINT32 width, UINT32 height, GraphicsAPI::eTextureComponentFormat format, GraphicsAPI::eDataType type);

			const BufferID& GetBufferID() const
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
					GraphicsAPI::BindTextureObject(mBufferID, mBindTarget);
				}
			}
			FORCE_INLINE void ActiveTexture(UINT32 bindingPoint) const noexcept
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID(ACTIVE_TEXTURE_TAG, bindingPoint))
				{
					GraphicsAPI::ActivateTextureUnit(bindingPoint);
				}
			}


			FORCE_INLINE void UnBindTexture() const noexcept
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID_WITH_DOUBLE_INDEX(BIND_TARGET_TAG, GetArbitraryIndexOfeBindTarget(mBindTarget), D_OVERLAP_BIND_GET_BIND_ID(ACTIVE_TEXTURE_TAG), 0))
				{
					GraphicsAPI::UnBindTextureObject(mBindTarget);
				}
			}

			FORCE_INLINE void BindTextureWithUnit(UINT32 bindingPoint) const
			{
				if (
					D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID_WITH_DOUBLE_INDEX(BIND_TARGET_TAG, GetArbitraryIndexOfeBindTarget(mBindTarget), bindingPoint, mBufferID)
				)
				{
					GraphicsAPI::BindTextureObjectAndActivateTextureUnit(mBufferID, bindingPoint);
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

			const BufferID& GetTextureBufferID() const;

			void SetWrapMode(GraphicsAPI::eWrapMode wrapMode, bool bBind);
			void SetFilterMin(GraphicsAPI::eFilterMode filterMode, bool bBind);
			void SetFilterMax(GraphicsAPI::eFilterMode filterMode, bool bBind);

			GraphicsAPI::eWrapMode GetWrapModeS() const;
			GraphicsAPI::eWrapMode GetWrapModeT() const;
			GraphicsAPI::eWrapMode GetWrapModeR() const;

			FORCE_INLINE GraphicsAPI::eTextureType GetTextureType() const
			{
				return mTextureType;
			}
			FORCE_INLINE GraphicsAPI::eTextureBindTarget GetBindTarget() const
			{
				return mBindTarget;
			}
			FORCE_INLINE GraphicsAPI::eTargetTexture GetTarget() const
			{
				return mTarget;
			}
			FORCE_INLINE GraphicsAPI::eTextureInternalFormat GetInternalFormat() const
			{
				return mInternalFormat;
			}
			FORCE_INLINE GraphicsAPI::eTextureCompressedInternalFormat GetCompressedInternalFormat() const
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
			FORCE_INLINE GraphicsAPI::eTextureComponentFormat GetDataFormat() const
			{
				return mDataFormat;
			}
			FORCE_INLINE GraphicsAPI::eDataType GetDataType() const
			{
				return mDataType;
			}

			FORCE_INLINE void TexParameterf(const GraphicsAPI::eTextureBindTarget target, const GraphicsAPI::eTextureParameterType pname, FLOAT32 param) const noexcept
			{
				GraphicsAPI::SetTextureParameterFloat(target, pname, param);
			}
			FORCE_INLINE void TexParameteri(const GraphicsAPI::eTextureBindTarget target, const GraphicsAPI::eTextureParameterType pname, INT32 param) const noexcept
			{
				GraphicsAPI::SetTextureParameterInt(target, pname, param);
			}

			

			
			FLOAT32 GetTextureMetaDataFLOAT32(const INT32 lodLevel, const GraphicsAPI::eTextureMetaDataType textureMetaDataType) const;
			INT32 GetTextureMetaDataINT32(const INT32 lodLevel, const GraphicsAPI::eTextureMetaDataType textureMetaDataType) const;
			
			
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
				const GraphicsAPI::eTextureComponentFormat dataFormat,
				const GraphicsAPI::eDataType dataType
			);

		};
	}
}