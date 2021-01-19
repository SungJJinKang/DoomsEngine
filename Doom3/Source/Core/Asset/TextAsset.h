#pragma once

#include "Base_Asset.h"
#include <string>

namespace Doom
{

	struct TextAsset : public Asset
	{
		std::string String;

		TextAsset(std::string str)
		{
			this->String = str;
		}

	};
	template <> struct Asset::AssetTypeConditional<Asset::AssetType::TEXT> { using type = typename TextAsset; };
}