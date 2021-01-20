#pragma once

#include "Base_Asset.h"
#include <string>

namespace Doom
{

	class TextAsset : public Asset
	{
	public:
		std::string String;

		TextAsset(const std::string& str)
		{
			this->String = str;
		}

	};
	template <> struct Asset::AssetTypeConditional<Asset::AssetType::TEXT> { using type = typename TextAsset; };
}