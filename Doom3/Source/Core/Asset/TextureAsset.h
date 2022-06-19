#pragma once
#include "Asset.h"

#include <memory>

#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include <Rendering/Buffer/BufferID.h>

#include "TextureAsset.reflection.h"
namespace DirectX
{
	class ScratchImage;
}

namespace dooms
{
	namespace graphics
	{
		class RenderingTextureViewProxy;
		class Material;
		class RenderingTextureProxy;
	}

	namespace assetImporter
	{
		class AssetImporterWorker_Texture;
	}

	namespace asset
	{
		class DOOM_API D_CLASS TextureAsset : public Asset
		{
			GENERATE_BODY()
				
		public:

			TextureAsset();
			TextureAsset
			(
				dooms::graphics::GraphicsAPI::eTargetTexture targetTexture, 
				dooms::graphics::GraphicsAPI::eTextureInternalFormat internalFormat, 
				dooms::graphics::GraphicsAPI::eTextureCompressedInternalFormat compressedInternalFormat, 
				UINT32 width, UINT32 height, 
				dooms::graphics::GraphicsAPI::eTextureComponentFormat format, 
				dooms::graphics::GraphicsAPI::eDataType dataType,
				dooms::graphics::GraphicsAPI::eBindFlag resourceBindFlag,
				dooms::graphics::GraphicsAPI::eTextureBindTarget textureBindTarget,
				const void* data = 0,
				const size_t dataSize = 0
			);
			TextureAsset(std::unique_ptr<DirectX::ScratchImage>&& scratchImage, const dooms::graphics::GraphicsAPI::eBindFlag resourceBindFlag);
			void SetScratchImage(std::unique_ptr<DirectX::ScratchImage>&& scratchImage, const dooms::graphics::GraphicsAPI::eBindFlag resourceBindFlag);
			TextureAsset(const TextureAsset&) = delete;
			TextureAsset(TextureAsset&& textureAsset) noexcept;
			TextureAsset& operator=(const TextureAsset&) = delete;
			TextureAsset& operator=(TextureAsset&& textureAsset) noexcept;
		
			virtual ~TextureAsset();

			virtual void OnSetPendingKill() override;

			void OnEndImportInMainThread_Internal() final;

			virtual dooms::asset::eAssetType GetEAssetType() const final;
			
			graphics::GraphicsAPI::eTextureComponentFormat GetTextureComponentFormat() const;
			graphics::GraphicsAPI::eTextureInternalFormat GetTextureInternalFormat() const;
			graphics::GraphicsAPI::eTextureCompressedInternalFormat GetTextureCompressedInternalFormat() const;
			UINT32 GetTextureWidth(const size_t mipLevelIndex = 0) const;
			UINT32 GetTextureHeight(const size_t mipLevelIndex = 0) const;
			UINT32 GetMipMapLevel() const;
			UINT64 GetEntireImageSize() const;
			graphics::GraphicsAPI::eDataType GetTextureDataType() const;
			FORCE_INLINE graphics::GraphicsAPI::eTextureBindTarget GetTextureBindTarget() const
			{
				return TextureBindTarget;
			}

			dooms::graphics::RenderingTextureViewProxy* GenerateTextureView
			(
				const UINT32 defaultBindingPosition,
				const graphics::GraphicsAPI::eGraphicsPipeLineStage defaultTargetGraphicsPipeLineStage
			) const;

			graphics::RenderingTextureProxy* GetRenderingTextureProxy() const;
			bool IsRenderingTextureProxyCreated() const;

		private:

			graphics::RenderingTextureProxy* TextureProxy{ nullptr };

			D_PROPERTY()
			dooms::graphics::BufferID TextureResourceObject{};

			std::unique_ptr<DirectX::ScratchImage> ScratchImage{};

			D_PROPERTY()
			std::vector<const void*> TextureData;

			D_PROPERTY()
			graphics::GraphicsAPI::eTargetTexture TargetTexture;

			D_PROPERTY()
			graphics::GraphicsAPI::eTextureBindTarget TextureBindTarget;

			D_PROPERTY()
			std::vector<UINT32> Width;

			D_PROPERTY()
			std::vector<UINT32> Height;

			D_PROPERTY()
			std::vector<UINT32> SrcRowPitch;

			D_PROPERTY()
			std::vector<UINT32> SrcDepthPitch;

			D_PROPERTY()
			INT32 MipMapLevelCount;

			/// <summary>
			/// Size in bytes of All Images ( All mipmaps )
			/// </summary>
			D_PROPERTY()
			size_t EntireImageSize;

			D_PROPERTY()
			graphics::GraphicsAPI::eTextureComponentFormat ComponentFormat; // 1 ~ 4 ( rgb, rgba ~~ )

			D_PROPERTY()
			graphics::GraphicsAPI::eTextureInternalFormat InternalFormat;

			D_PROPERTY()
			graphics::GraphicsAPI::eTextureCompressedInternalFormat CompressedInternalFormat;

			D_PROPERTY()
			graphics::GraphicsAPI::eDataType DataType;

			D_PROPERTY()
			graphics::GraphicsAPI::eBindFlag BindFlags;

			void CreateRenderingTextureProxy();
			void CreateRenderingTextureProxyIfNotCreated();
			void DestroyRenderingTextureProxy();

			void AllocateTextureResourceObject();
			void DestroyTextureResourceObject();

		};


		
	}
}


