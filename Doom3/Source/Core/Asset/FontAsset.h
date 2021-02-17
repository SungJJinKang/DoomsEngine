#pragma once

#include "Base_Asset.h"
namespace doom
{

	class FontAsset : public Asset
	{
		friend class assetimporter::AssetManager;

		template <eAssetType assetType>
		friend class assetimporter::AssetImporterWorker;

		template<eAssetType loopVariable>
		friend struct assetimporter::OnEndImportInMainThreadFunctor;

	private:
		
	protected:
		
	public:

		FontAsset() = default;
		FontAsset(const FontAsset&) = delete;
		FontAsset(FontAsset&&) noexcept = default;
		FontAsset& operator=(const FontAsset&) = delete;
		FontAsset& operator=(FontAsset&&) noexcept = default;
		virtual ~FontAsset() = default;
	};
	template <> struct Asset::asset_type<eAssetType::FONT> { using type = typename FontAsset; };
}