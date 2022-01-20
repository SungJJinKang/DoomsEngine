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
		class Texture;
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

			dooms::graphics::BufferID mTextureResourceObject;

			std::unique_ptr<DirectX::ScratchImage> mScratchImage;

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
			bool bmIsCompressed{ false };

			D_PROPERTY()
			graphics::GraphicsAPI::eTextureComponentFormat mComponentFormat{}; // 1 ~ 4 ( rgb, rgba ~~ )

			D_PROPERTY()
			graphics::GraphicsAPI::eTextureInternalFormat mInternalFormat{};

			D_PROPERTY()
			graphics::GraphicsAPI::eTextureCompressedInternalFormat mCompressedInternalFormat{};
			
			void AllocateTextureResourceObject();
			void DestroyTextureResourceObject();

		protected:

		public:

			TextureAsset();
			void SetScratchImage(std::unique_ptr<DirectX::ScratchImage>&& scratchImage);
			TextureAsset(const TextureAsset&) = delete;
			TextureAsset(TextureAsset&& textureAsset) noexcept;
			TextureAsset& operator=(const TextureAsset&) = delete;
			TextureAsset& operator=(TextureAsset&& textureAsset) noexcept;
		
			virtual ~TextureAsset();

			virtual void OnSetPendingKill() override;

			void OnEndImportInMainThread_Internal() final;
			const graphics::Texture* GetTextureViewObject() const;

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

		};
		
	}
}


