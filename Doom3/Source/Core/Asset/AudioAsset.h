#pragma once

#include "Base_Asset.h"
namespace Doom
{

	struct AudioAsset : public Asset
	{
	};
	template <> struct Asset::AssetTypeConditional<Asset::AssetType::AUDIO> { using type = AudioAsset; };
}

