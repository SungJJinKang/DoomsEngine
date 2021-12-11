#pragma once

#include "Asset.h"

#include "AudioAsset.reflection.h"
namespace dooms
{
	namespace assetImporter
	{
		class AssetImporterWorker_Audio;
	}


	namespace asset
	{
		class DOOM_API D_CLASS AudioAsset : public Asset
		{
			GENERATE_BODY()
			
			

			friend class ::dooms::assetImporter::AssetImporterWorker_Audio;
			
		private:

		protected:

		public:

			AudioAsset() = default;
			AudioAsset(const AudioAsset&) = delete;
			AudioAsset(AudioAsset&&) noexcept = default;
			AudioAsset& operator=(const AudioAsset&) = delete;
			AudioAsset& operator=(AudioAsset&&) noexcept = default;
			virtual ~AudioAsset() = default;

			virtual void OnSetPendingKill() override;


			virtual dooms::asset::eAssetType GetEAssetType() const final;

		};

	}
}

