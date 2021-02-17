#pragma once
#include "Base_Asset.h"

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

	public:
		enum class eTextureComponent
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
		std::unique_ptr<unsigned char[]> mData;

		graphics::Texture* mTexture;
		void CreateTexture();
	protected:
	
	public:
		
		TextureAsset(int width, int height, int componentCount, unsigned char* data);
		TextureAsset(const TextureAsset&) = delete;
		TextureAsset(TextureAsset&& textureAsset) noexcept = default;
		TextureAsset& operator=(const TextureAsset& ) = delete;
		TextureAsset& operator=(TextureAsset&& textureAsset) noexcept = default;
		virtual ~TextureAsset() = default;

		void OnEndImportInMainThread() final;
	};

	template <> struct Asset::asset_type<eAssetType::TEXTURE> { using type = typename TextureAsset; };
}


