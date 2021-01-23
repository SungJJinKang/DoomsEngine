#pragma once

#include "Base_Asset.h"
namespace Doom
{

	class AudioAsset : public Asset
	{
	};
	template <> struct Asset::asset_type<Asset::AssetType::AUDIO> { using type = AudioAsset; };
}

