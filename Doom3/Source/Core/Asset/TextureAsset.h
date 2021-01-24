#pragma once
#include "Base_Asset.h"

namespace doom
{
	class TextureAsset : public Asset
	{
	};

	template <> struct Asset::asset_type<Asset::eAssetType::TEXTURE> { using type = typename TextureAsset; };
}


