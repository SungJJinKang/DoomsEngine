#pragma once

#include "Asset.h"
namespace doom
{
	namespace assetimporter
	{
		class AssetImporterWorker_Audio;
	}


	namespace asset
	{
		class DOOM_API AudioAsset : public Asset
		{
			friend class ::doom::assetimporter::AssetImporterWorker_Audio;
			
		private:

		protected:

		public:

			AudioAsset() = default;
			AudioAsset(const AudioAsset&) = delete;
			AudioAsset(AudioAsset&&) noexcept = default;
			AudioAsset& operator=(const AudioAsset&) = delete;
			AudioAsset& operator=(AudioAsset&&) noexcept = default;
			virtual ~AudioAsset() {}


			virtual doom::asset::eAssetType GetEAssetType() const final;

		};

	}
}

