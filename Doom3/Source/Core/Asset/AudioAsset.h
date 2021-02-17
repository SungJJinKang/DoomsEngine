#pragma once

#include "Base_Asset.h"
namespace doom
{

	class AudioAsset : public Asset
	{
		friend class assetimporter::AssetManager;

		template <eAssetType assetType>
		friend class assetimporter::AssetImporterWorker;

		template<eAssetType loopVariable>
		friend struct assetimporter::OnEndImportInMainThreadFunctor;

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

