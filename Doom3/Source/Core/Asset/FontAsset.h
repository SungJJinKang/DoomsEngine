#pragma once

#include "Base_Asset.h"
namespace Doom
{

	struct FontAsset : public Asset
	{
	};
	template <> struct AssetTypeConditional<AssetType::FONT> { using type = typename FontAsset; };
}