#pragma once

#include "Asset.h"
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

}