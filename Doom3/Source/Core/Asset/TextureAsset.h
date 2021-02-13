#pragma once
#include "Base_Asset.h"

namespace doom
{
	namespace graphics
	{
		class SingleTexture;
	}

	class TextureAsset : public Asset
	{
		friend class assetimporter::AssetManager;

		template <eAssetType assetType>
		friend class assetimporter::AssetImporterWorker;

		template<eAssetType loopVariable>
		friend struct assetimporter::OnEndImportInMainThreadFunctor;

	public:
		enum eTextureComponent
		{
			Grey = 1,
			GreyAlpha = 2,
			RGB = 3,
			RGBA = 4
		};
	private:


		int mWidth;
		int mHeight;
		eTextureComponent mComponentType; // 1 ~ 4 ( rgb, rgba ~~ )
		unsigned char* mData;

		graphics::SingleTexture* mSingleTexture;
		void CreateTexture();
	protected:

	public:
		
		TextureAsset(int width, int height, int componentCount, unsigned char* data);
		TextureAsset(const TextureAsset&) = delete;
		TextureAsset(TextureAsset&&) noexcept = default;
		TextureAsset& operator=(const TextureAsset&) = delete;
		TextureAsset& operator=(TextureAsset&&) noexcept = default;

		void OnEndImportInMainThread() final;
	};

	template <> struct Asset::asset_type<eAssetType::TEXTURE> { using type = typename TextureAsset; };
}


