#pragma once
#include "Asset.h"

#include <memory>

#include <Graphics/GraphicsAPI/GraphicsAPI.h>
#include <Graphics/Buffer/BufferID.h>

#include "TextureAsset.reflection.h"
namespace DirectX
{
	class ScratchImage;
}

namespace dooms
{
	namespace graphics
	{
		class TextureView;
		class Material;
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
				

			friend class ::dooms::assetImporter::AssetImporterWorker_Texture;

		private:

			D_PROPERTY()
			dooms::graphics::BufferID mTextureResourceObject;

			std::unique_ptr<DirectX::ScratchImage> mScratchImage;

			D_PROPERTY()
			std::vector<const void*> mTextureData;

			D_PROPERTY()
			graphics::GraphicsAPI::eTargetTexture mTargetTexture;

			D_PROPERTY()
			std::vector<UINT32> mWidth;

			D_PROPERTY()
			std::vector<UINT32> mHeight;

			D_PROPERTY()
			std::vector<UINT32> mRowByteSizes;

			D_PROPERTY()
			std::vector<UINT32> mTotalDataSize;

			D_PROPERTY()
			INT32 mMipMapLevelCount;

			/// <summary>
			/// Size in bytes of All Images ( All mipmaps )
			/// </summary>
			D_PROPERTY()
			size_t mEntireImageSize;
			
			D_PROPERTY()
			graphics::GraphicsAPI::eTextureComponentFormat mComponentFormat; // 1 ~ 4 ( rgb, rgba ~~ )

			D_PROPERTY()
			graphics::GraphicsAPI::eTextureInternalFormat mInternalFormat;

			D_PROPERTY()
			graphics::GraphicsAPI::eTextureCompressedInternalFormat mCompressedInternalFormat;

			D_PROPERTY()
			graphics::GraphicsAPI::eDataType mDataType;

			D_PROPERTY()
			graphics::GraphicsAPI::eBindFlag mBindFlags;
			
			void AllocateTextureResourceObject();
			void DestroyTextureResourceObject();

		protected:

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
			graphics::TextureView* GenerateTextureViewObject();

			virtual dooms::asset::eAssetType GetEAssetType() const final;

			dooms::graphics::BufferID GetTextureResourceObject();

			graphics::GraphicsAPI::eTextureComponentFormat GetTextureComponentFormat() const;
			graphics::GraphicsAPI::eTextureInternalFormat GetTextureInternalFormat() const;
			graphics::GraphicsAPI::eTextureCompressedInternalFormat GetTextureCompressedInternalFormat() const;
			UINT32 GetTextureWidth(const size_t mipLevelIndex = 0) const;
			UINT32 GetTextureHeight(const size_t mipLevelIndex = 0) const;
			UINT32 GetMipMapLevel() const;
			UINT64 GetEntireImageSize() const;
			graphics::GraphicsAPI::eDataType GetTextureDataType() const;


			dooms::graphics::TextureView* GetTextureView();
		};
		
	}
}


