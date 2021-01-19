#pragma once
#include "Base_Asset.h"

namespace Doom
{
	struct TextureAsset : public Asset
	{
	};

	template <> struct Asset::AssetTypeConditional<Asset::AssetType::TEXTURE> { using type = typename TextureAsset; };
}


