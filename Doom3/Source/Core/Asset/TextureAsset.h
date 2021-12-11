#pragma once
#include "Asset.h"

#include <memory>

#include "../Graphics/Texture/TextureFormat.h"

#include "TextureAsset.reflection.h"
namespace DirectX
{
	class ScratchImage;
}

namespace dooms
{
	namespace graphics
	{
		class SingleTexture;
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
			graphics::eTextureComponentFormat mComponentFormat{}; // 1 ~ 4 ( rgb, rgba ~~ )

			D_PROPERTY()
			graphics::eTextureInternalFormat mInternalFormat{};

			D_PROPERTY()
			graphics::eTextureCompressedInternalFormat mCompressedInternalFormat{};

			D_PROPERTY()
			graphics::Texture* mDefaultTextureObject{ nullptr };

			void CreateDefaultTexture();
			void DestroyDefaultTextureObject();

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
			const graphics::Texture* GetDefaultTextureObject() const;
			graphics::Texture* CreateTextureObject();

			virtual dooms::asset::eAssetType GetEAssetType() const final;
		};
		
	}
}


