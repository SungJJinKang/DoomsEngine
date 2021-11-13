#pragma once

#include "Asset.h"

#include "FontAsset.reflection.h"
namespace dooms
{
	namespace assetImporter
	{
		class AssetImporterWorker_Font;
	}

	namespace asset
	{
		class DOOM_API D_CLASS FontAsset : public Asset
		{
			GENERATE_BODY()
			

			friend class ::dooms::assetImporter::AssetImporterWorker_Font;
			
		private:

		protected:

		public:

			FontAsset() = default;
			FontAsset(const FontAsset&) = delete;
			FontAsset(FontAsset&&) noexcept = default;
			FontAsset& operator=(const FontAsset&) = delete;
			FontAsset& operator=(FontAsset&&) noexcept = default;
			virtual ~FontAsset() = default;


			virtual dooms::asset::eAssetType GetEAssetType() const final;

		};


	}
}