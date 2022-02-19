#pragma once

#include <memory>

#include <Graphics/Graphics_Core.h>
#include <Asset/TextureAsset.h>
#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include "../Buffer/BufferID.h"

#include "TextureView.reflection.h"
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
		class DOOM_API D_CLASS TextureView : public DObject
		{
			GENERATE_BODY()
			
		private:
			void OnSetPendingKill() override;
			void DestroyTextureViewObject();

			D_PROPERTY()
			const asset::TextureAsset* mTargetTextureResourceObject;

			D_PROPERTY()
			BufferID mTextureViewObject;

			D_PROPERTY()
			UINT32 mDefaultBindingLocation;

			D_PROPERTY()
			GraphicsAPI::eGraphicsPipeLineStage mDefaultTargetGraphicsPipeLineStage;

			inline static const UINT32 MAX_TEXTURE_BOUND_LOCATION_COUNT = 30;
			static UINT64 BOUND_TEXTURE_ID[GRAPHICS_PIPELINE_STAGE_COUNT][MAX_TEXTURE_BOUND_LOCATION_COUNT];

		public:

			

			TextureView
			(
				const asset::TextureAsset* const textureResourceObject, 
				const UINT32 defaultBindingPosition,
				const GraphicsAPI::eGraphicsPipeLineStage defaultTargetGraphicsPipeLineStage
			);
			TextureView(const TextureView&);
			TextureView& operator=(const TextureView&);

			TextureView(TextureView&&) noexcept;
			TextureView& operator=(TextureView&&) noexcept;
			
			virtual ~TextureView();
			virtual void OnEndContructor();
			
			FORCE_INLINE const BufferID& GetTextureViewObjectBufferID() const
			{
				return mTextureViewObject;
			}
			
			const asset::TextureAsset* GetTargetTextureResourceObject() const;

			FORCE_INLINE UINT32 GetDefaultBindingLocation() const
			{
				return mDefaultBindingLocation;
			}
			void SetDefaultBindingLocation(const UINT32 defaultBindingLocation);

			FORCE_INLINE GraphicsAPI::eGraphicsPipeLineStage GetDefaultTargetGraphicsPipeLineStage() const
			{
				return mDefaultTargetGraphicsPipeLineStage;
			}
			void SetDefaultTargetGraphicsPipeLineStage(const GraphicsAPI::eGraphicsPipeLineStage defaultGraphicsPipeLineStage);

			FORCE_INLINE void BindTexture() const noexcept
			{
				if (BOUND_TEXTURE_ID[static_cast<UINT32>(mDefaultTargetGraphicsPipeLineStage)][mDefaultBindingLocation] != mTextureViewObject.GetBufferID())
				{
					BOUND_TEXTURE_ID[static_cast<UINT32>(mDefaultTargetGraphicsPipeLineStage)][mDefaultBindingLocation] = mTextureViewObject.GetBufferID();
					GraphicsAPI::BindTextureObject
					(
						mTextureViewObject,
						mTargetTextureResourceObject->GetTextureBindTarget(),
						mDefaultBindingLocation,
						mDefaultTargetGraphicsPipeLineStage
					);
				}
			}

			FORCE_INLINE void UnBindTexture() const noexcept
			{
				if (BOUND_TEXTURE_ID[static_cast<UINT32>(mDefaultTargetGraphicsPipeLineStage)][mDefaultBindingLocation] != 0)
				{
					BOUND_TEXTURE_ID[static_cast<UINT32>(mDefaultTargetGraphicsPipeLineStage)][mDefaultBindingLocation] = 0;

					GraphicsAPI::BindTextureObject
					(
						0,
						mTargetTextureResourceObject->GetTextureBindTarget(),
						mDefaultBindingLocation,
						mDefaultTargetGraphicsPipeLineStage
					);
				}
			}

			FORCE_INLINE void BindTexture
			(
				const UINT32 bindingPoint, 
				const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage
			) const noexcept
			{
				if (BOUND_TEXTURE_ID[static_cast<UINT32>(targetPipeLineStage)][bindingPoint] != mTextureViewObject.GetBufferID())
				{
					BOUND_TEXTURE_ID[static_cast<UINT32>(targetPipeLineStage)][bindingPoint] = mTextureViewObject;

					GraphicsAPI::BindTextureObject
					(
						mTextureViewObject, 
						mTargetTextureResourceObject->GetTextureBindTarget(),
						bindingPoint,
						targetPipeLineStage
					);
				}
			}
			
			FORCE_INLINE void UnBindTexture
			(
				const UINT32 bindingPoint,
				const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage
			) const noexcept
			{
				if (BOUND_TEXTURE_ID[static_cast<UINT32>(targetPipeLineStage)][bindingPoint] != 0)
				{
					BOUND_TEXTURE_ID[static_cast<UINT32>(targetPipeLineStage)][bindingPoint] = 0;

					GraphicsAPI::BindTextureObject
					(
						0,
						mTargetTextureResourceObject->GetTextureBindTarget(),
						bindingPoint,
						targetPipeLineStage
					);
				}
			}

			const BufferID& GetTextureBufferID() const;
			
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