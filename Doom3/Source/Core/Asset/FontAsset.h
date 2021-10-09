#pragma once

#include "Base_Asset.h"
namespace doom
{
	namespace asset
	{
		class DOOM_API FontAsset : public Asset
		{
			friend class ::doom::assetimporter::ImportedAssetPort<eAssetType::FONT>;

			friend class ::doom::assetimporter::AssetManager;
			friend class ::doom::assetimporter::Assetimporter;

			template <eAssetType assetType>
			friend class ::doom::assetimporter::AssetImporterWorker;

			template<eAssetType loopVariable>
			friend struct ::doom::assetimporter::OnEndImportInMainThreadFunctor;

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
}