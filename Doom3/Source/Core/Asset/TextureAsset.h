#pragma once
#include "Base_Asset.h"

namespace Doom
{
	struct TextureAsset : public Asset
	{
	};
	template <> struct AssetTypeConditional<AssetType::TEXTURE> { using type = typename TextureAsset; };
}


