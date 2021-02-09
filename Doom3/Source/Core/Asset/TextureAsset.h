#pragma once
#include "Base_Asset.h"

namespace doom
{
	class TextureAsset : public Asset
	{
		friend class assetimporter::AssetManager;

		template <eAssetType assetType>
		friend class assetimporter::AssetImporterWorker;

		template<eAssetType loopVariable>
		friend struct assetimporter::OnEndImportInMainThreadFunctor;

	private:

	protected:

	public:
		
		TextureAsset() = default;
		TextureAsset(const TextureAsset&) = delete;
		TextureAsset(TextureAsset&&) noexcept = default;
		TextureAsset& operator=(const TextureAsset&) = delete;
		TextureAsset& operator=(TextureAsset&&) noexcept = default;

	};

	template <> struct Asset::asset_type<eAssetType::TEXTURE> { using type = typename TextureAsset; };
}


