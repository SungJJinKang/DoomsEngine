#pragma once

#include <memory>

#include "../Graphics_Core.h"
#include <Asset/TextureAsset.h>
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
			
			
		private:

			inline static const char BIND_TARGET_TAG[]{ "BIND_TARGET" };
			static inline const char ACTIVE_TEXTURE_TAG[]{ "ActiveTexture" };

			void OnSetPendingKill() override;
			void DestroyTextureViewObject();
			
			asset::TextureAsset* mTargetTextureResourceObject;
			BufferID mTextureViewObject{};

		public:

			

			Texture(asset::TextureAsset* const textureResourceObject);
			Texture(const Texture&) = delete;
			Texture& operator=(const Texture&) noexcept = delete;

			Texture(Texture&&) noexcept = default;
			Texture& operator=(Texture&&) noexcept = default;
			
			virtual ~Texture();
			virtual void OnEndContructor();
			
			const BufferID& GetBufferID() const
			{
				return mTextureViewObject;
			}

			asset::TextureAsset* GetTargetTextureResourceObject();
			const asset::TextureAsset* GetTargetTextureResourceObject() const;


			FORCE_INLINE void BindTexture() const noexcept
			{
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID_WITH_DOUBLE_INDEX(BIND_TARGET_TAG, GraphicsAPI::eTextureBindTarget::TEXTURE_2D, D_OVERLAP_BIND_GET_BIND_ID(ACTIVE_TEXTURE_TAG), mTextureViewObject))
				{
					GraphicsAPI::BindTextureObject(mTextureViewObject, GraphicsAPI::eTextureBindTarget::TEXTURE_2D);
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
				if (D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID_WITH_DOUBLE_INDEX(BIND_TARGET_TAG, GraphicsAPI::eTextureBindTarget::TEXTURE_2D, D_OVERLAP_BIND_GET_BIND_ID(ACTIVE_TEXTURE_TAG), 0))
				{
					GraphicsAPI::UnBindTextureObject(GraphicsAPI::eTextureBindTarget::TEXTURE_2D);
				}
			}

			FORCE_INLINE void BindTextureWithUnit(UINT32 bindingPoint) const
			{
				if (
					D_OVERLAP_BIND_CHECK_CHECK_IS_NOT_BOUND_AND_BIND_ID_WITH_DOUBLE_INDEX(BIND_TARGET_TAG, GraphicsAPI::eTextureBindTarget::TEXTURE_2D, bindingPoint, mTextureViewObject)
				)
				{
					GraphicsAPI::BindTextureObjectAndActivateTextureUnit(mTextureViewObject, bindingPoint);
				}
				//glActiveTexture(GL_TEXTURE0 + bindingPoint);
				//glBindTexture(GL_TEXTURE_2D, mTextureViewObject);
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