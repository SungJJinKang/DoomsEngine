#pragma once

#include "Base_Asset.h"
namespace doom
{
	namespace asset
	{
		class AudioAsset : public Asset
		{
			friend class ::doom::assetimporter::ImportedAssetPort<eAssetType::AUDIO>;

			friend class ::doom::assetimporter::AssetManager;
			friend class ::doom::assetimporter::Assetimporter;

			template <eAssetType assetType>
			friend class ::doom::assetimporter::AssetImporterWorker;

			template<eAssetType loopVariable>
			friend struct ::doom::assetimporter::OnEndImportInMainThreadFunctor;

		private:

		protected:

		public:

			AudioAsset() = default;
			AudioAsset(const AudioAsset&) = delete;
			AudioAsset(AudioAsset&&) noexcept = default;
			AudioAsset& operator=(const AudioAsset&) = delete;
			AudioAsset& operator=(AudioAsset&&) noexcept = default;
			virtual ~AudioAsset() {}
		};
		template <> struct Asset::asset_type<eAssetType::AUDIO> { using type = AudioAsset; };
	}
}

