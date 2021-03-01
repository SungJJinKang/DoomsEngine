#pragma once
#include "Base_Asset.h"

#include "../Graphics/TextureFormat.h"

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

	class TextureAsset : public Asset
	{
		friend class graphics::SingleTexture;
		friend class graphics::Texture;
		friend class graphics::Material;

		friend class assetimporter::AssetManager;

		template <eAssetType assetType>
		friend class assetimporter::AssetImporterWorker;

		template<eAssetType loopVariable>
		friend struct assetimporter::OnEndImportInMainThreadFunctor;

	private:


		int mWidth;
		int mHeight;
		int mMipMapLevel;
		/// <summary>
		/// Size in bytes of All Images ( All mipmaps )
		/// </summary>
		size_t mEntireImageSize;

		bool bmIsCompressed;
		graphics::eTextureComponentFormat mComponentFormat; // 1 ~ 4 ( rgb, rgba ~~ )
		graphics::eTextureInternalFormat mInternalFormat;
		graphics::eTextureCompressedInternalFormat mCompressedInternalFormat;

		DirectX::ScratchImage* mScratchImage;

		graphics::Texture* mTexture;
		void CreateTexture();
	protected:
	
	public:
		
		TextureAsset(DirectX::ScratchImage* scratchImage);
		TextureAsset(const TextureAsset&) = delete;
		TextureAsset(TextureAsset&& textureAsset) noexcept = default;
		TextureAsset& operator=(const TextureAsset& ) = delete;
		TextureAsset& operator=(TextureAsset&& textureAsset) noexcept = default;
		virtual ~TextureAsset() = default;

		void OnEndImportInMainThread() final;
	};

	template <> struct Asset::asset_type<eAssetType::TEXTURE> { using type = typename TextureAsset; };
}


