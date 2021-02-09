#pragma once

#include "Base_Asset.h"
namespace doom
{

	class AudioAsset : public Asset
	{
		template<Asset::eAssetType loopVariable>
		friend struct assetimporter::OnEndImportInMainThreadFunctor;
	public:

	};
	template <> struct Asset::asset_type<Asset::eAssetType::AUDIO> { using type = AudioAsset; };
}

