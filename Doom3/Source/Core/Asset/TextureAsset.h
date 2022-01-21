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
			const void* mTextureData = nullptr;

			D_PROPERTY()
			dooms::graphics::TextureView* mDefaultTextureViewObject = nullptr;

			D_PROPERTY()
			graphics::GraphicsAPI::eTargetTexture mTargetTexture;

			D_PROPERTY()
			INT32 mWidth{};

			D_PROPERTY()
			INT32 mHeight{};

			D_PROPERTY()
			INT32 mMipMapLevel{};

			/// <summary>
			/// Size in bytes of All Images ( All mipmaps )
			/// </summary>
			D_PROPERTY()
			size_t mEntireImageSize{};
			
			D_PROPERTY()
			graphics::GraphicsAPI::eTextureComponentFormat mComponentFormat{}; // 1 ~ 4 ( rgb, rgba ~~ )

			D_PROPERTY()
			graphics::GraphicsAPI::eTextureInternalFormat mInternalFormat{};

			D_PROPERTY()
			graphics::GraphicsAPI::eTextureCompressedInternalFormat mCompressedInternalFormat{};

			D_PROPERTY()
			graphics::GraphicsAPI::eDataType mDataType{};
			
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
				const void* data = 0,
				const size_t dataSize = 0
			);
			void SetScratchImage(std::unique_ptr<DirectX::ScratchImage>&& scratchImage);
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
			INT32 GetTextureWidth() const;
			INT32 GetTextureHeight() const;
			INT32 GetMipMapLevel() const;
			INT32 GetEntireImageSize() const;
			graphics::GraphicsAPI::eDataType GetTextureDataType() const;


			dooms::graphics::TextureView* GetDefaultTextureViewObject();
		};
		
	}
}


