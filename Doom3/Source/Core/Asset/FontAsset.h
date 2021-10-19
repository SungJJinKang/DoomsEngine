#pragma once

#include "Asset.h"
namespace doom
{
	namespace assetimporter
	{
		class AssetImporterWorker_Font;
	}

	namespace asset
	{
		class DOOM_API FontAsset : public Asset
		{
			DOBJECT_CLASS_BODY(FontAsset, doom::eDOBJECT_ClassFlags::NonCopyable)

			friend class ::doom::assetimporter::AssetImporterWorker_Font;
			
		private:

		protected:

		public:

			FontAsset() = default;
			FontAsset(const FontAsset&) = delete;
			FontAsset(FontAsset&&) noexcept = default;
			FontAsset& operator=(const FontAsset&) = delete;
			FontAsset& operator=(FontAsset&&) noexcept = default;
			virtual ~FontAsset() = default;


			virtual doom::asset::eAssetType GetEAssetType() const final;

		};


	}
}