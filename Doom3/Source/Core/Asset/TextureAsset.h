#pragma once
#include "Base_Asset.h"

#include "../Graphics/Texture/TextureFormat.h"
#include <DirectXTex.h>
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

	namespace asset
	{
		class DOOM_API TextureAsset : public Asset
		{
			friend class graphics::SingleTexture;
			friend class graphics::Texture;
			friend class graphics::Material;

			friend class ::doom::assetimporter::AssetManager;
			friend class ::doom::assetimporter::Assetimporter;

			template <eAssetType assetType>
			friend class ::doom::assetimporter::AssetImporterWorker;

			template<eAssetType loopVariable>
			friend struct ::doom::assetimporter::OnEndImportInMainThreadFunctor;

		private:

			std::unique_ptr<DirectX::ScratchImage> mScratchImage{};

			int mWidth{};
			int mHeight{};
			int mMipMapLevel{};
			/// <summary>
			/// Size in bytes of All Images ( All mipmaps )
			/// </summary>
			size_t mEntireImageSize{};

			bool bmIsCompressed{ false };
			graphics::eTextureComponentFormat mComponentFormat{}; // 1 ~ 4 ( rgb, rgba ~~ )
			graphics::eTextureInternalFormat mInternalFormat{};
			graphics::eTextureCompressedInternalFormat mCompressedInternalFormat{};

			graphics::Texture* mTexture{ nullptr };
			void CreateTexture();
		protected:

		public:

			TextureAsset() = default;
			void SetScratchImage(std::unique_ptr<DirectX::ScratchImage>&& scratchImage);
			TextureAsset(const TextureAsset&) = delete;
			TextureAsset(TextureAsset&& textureAsset) noexcept = default;
			TextureAsset& operator=(const TextureAsset&) = delete;
			TextureAsset& operator=(TextureAsset&& textureAsset) noexcept = default;
			virtual ~TextureAsset() = default;

			void OnEndImportInMainThread_Internal() final;
		};

		template <> struct Asset::asset_type<eAssetType::TEXTURE> { using type = typename TextureAsset; };
	}
}


