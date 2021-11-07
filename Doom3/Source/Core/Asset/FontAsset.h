#pragma once

#include "Asset.h"
namespace dooms
{
	namespace assetImporter
	{
		class AssetImporterWorker_Font;
	}

	namespace asset
	{
		class DOOM_API FontAsset : public Asset
		{
			DOBJECT_CLASS_BODY(FontAsset, dooms::eDOBJECT_ClassFlags::NonCopyable)
				DOBJECT_CLASS_BASE_CHAIN(Asset)

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