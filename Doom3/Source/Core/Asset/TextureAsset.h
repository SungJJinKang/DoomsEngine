#pragma once
#include "Asset.h"

#include "../Graphics/Texture/TextureFormat.h"

namespace DirectX
{
	class ScratchImage;
}

namespace doom
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
		class DOOM_API TextureAsset : public Asset
		{
			DOBJECT_CLASS_BODY(TextureAsset, doom::eDOBJECT_ClassFlags::NonCopyable)
				DOBJECT_CLASS_BASE_CHAIN(Asset)

			friend class ::doom::assetImporter::AssetImporterWorker_Texture;

		private:

			std::unique_ptr<DirectX::ScratchImage> mScratchImage;

			INT32 mWidth{};
			INT32 mHeight{};
			INT32 mMipMapLevel{};
			/// <summary>
			/// Size in bytes of All Images ( All mipmaps )
			/// </summary>
			SIZE_T mEntireImageSize{};

			bool bmIsCompressed{ false };
			graphics::eTextureComponentFormat mComponentFormat{}; // 1 ~ 4 ( rgb, rgba ~~ )
			graphics::eTextureInternalFormat mInternalFormat{};
			graphics::eTextureCompressedInternalFormat mCompressedInternalFormat{};

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

			void OnEndImportInMainThread_Internal() final;
			const graphics::Texture* GetDefaultTextureObject() const;
			graphics::Texture* CreateTextureObject();

			virtual doom::asset::eAssetType GetEAssetType() const final;
		};
		
	}
}


