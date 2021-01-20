#pragma once
#include "Base_Asset.h"

namespace Doom
{
	class TextureAsset : public Asset
	{
	};

	template <> struct Asset::AssetTypeConditional<Asset::AssetType::TEXTURE> { using type = typename TextureAsset; };
}


