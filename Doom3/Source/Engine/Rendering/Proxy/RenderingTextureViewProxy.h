#pragma once

#include <memory>

#include <Graphics/Graphics_Core.h>
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
		class RenderingTextureProxy;

		/// <summary>
		/// reference : https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
		/// </summary>
		class RenderingTextureViewProxy
		{

		private:
			
			void DestroyTextureViewObjectIfExist();

			const RenderingTextureProxy* TargetTextureProxy;
			BufferID TextureViewObject;
			UINT32 DefaultBindingLocation;
			GraphicsAPI::eGraphicsPipeLineStage DefaultTargetGraphicsPipeLineStage;

			inline static const UINT32 MAX_TEXTURE_BOUND_LOCATION_COUNT = 30;
			static UINT64 BOUND_TEXTURE_ID[GRAPHICS_PIPELINE_STAGE_COUNT][MAX_TEXTURE_BOUND_LOCATION_COUNT];

		public:
			
			RenderingTextureViewProxy
			(
				const RenderingTextureProxy* const TextureProxy,
				const UINT32 DefaultBindingPosition,
				const GraphicsAPI::eGraphicsPipeLineStage DefaultTargetGraphicsPipeLineStage
			);
			RenderingTextureViewProxy(const RenderingTextureViewProxy&);
			RenderingTextureViewProxy& operator=(const RenderingTextureViewProxy&);

			RenderingTextureViewProxy(RenderingTextureViewProxy&&) noexcept;
			RenderingTextureViewProxy& operator=(RenderingTextureViewProxy&&) noexcept;
			
			virtual ~RenderingTextureViewProxy();
			virtual void OnEndContructor();
			
			FORCE_INLINE BufferID GetTextureViewObject() const
			{
				return TextureViewObject;
			}
			
			const RenderingTextureProxy* GetTargetTextureResourceObject() const;

			FORCE_INLINE UINT32 GetDefaultBindingLocation() const
			{
				return DefaultBindingLocation;
			}
			void SetDefaultBindingLocation(const UINT32 defaultBindingLocation);

			FORCE_INLINE GraphicsAPI::eGraphicsPipeLineStage GetDefaultTargetGraphicsPipeLineStage() const
			{
				return DefaultTargetGraphicsPipeLineStage;
			}
			void SetDefaultTargetGraphicsPipeLineStage(const GraphicsAPI::eGraphicsPipeLineStage defaultGraphicsPipeLineStage);

			void BindTexture() const noexcept;
			void BindTexture
			(
				const UINT32 bindingPoint,
				const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage
			) const noexcept;
			void UnBindTexture() const noexcept;
			void UnBindTexture
			(
				const UINT32 bindingPoint,
				const GraphicsAPI::eGraphicsPipeLineStage targetPipeLineStage
			) const noexcept;

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