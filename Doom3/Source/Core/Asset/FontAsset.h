#pragma once

#include "Base_Asset.h"
namespace Doom
{

	class FontAsset : public Asset
	{
	};
	template <> struct Asset::asset_type<Asset::AssetType::FONT> { using type = typename FontAsset; };
}