#pragma once

#include "Base_Asset.h"
namespace doom
{

	class FontAsset : public Asset
	{
	};
	template <> struct Asset::asset_type<Asset::eAssetType::FONT> { using type = typename FontAsset; };
}