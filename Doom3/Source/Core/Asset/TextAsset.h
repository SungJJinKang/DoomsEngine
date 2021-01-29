#pragma once

#include "Base_Asset.h"
#include <string>

namespace doom
{

	class TextAsset : public Asset
	{
	public:
		std::string mString;

		TextAsset(const std::string& str)
		{
			this->mString = str;
		}

	};
	template <> struct Asset::asset_type<Asset::eAssetType::TEXT> { using type = typename TextAsset; };
}