#pragma once
#include "Macros/TypeDef.h"


namespace doom
{
	namespace asset
	{
		enum class eAssetType : UINT32
		{
			AUDIO = 0,
			FONT,
			TEXT,
			TEXTURE,
			THREE_D_MODEL,
			SHADER
		};
		constexpr inline size_t ENUM_ASSETTYPE_COUNT = 6;

		constexpr inline eAssetType FIRST_ENUM_ASSETTYPE_VALUE = eAssetType::AUDIO;
		constexpr inline eAssetType LAST_ENUM_ASSETTYPE_VALUE = eAssetType::SHADER;

		constexpr auto GetAssetTypeName(eAssetType assetType)
		{
			switch(assetType)
			{
			case eAssetType::AUDIO:
				return "AUDIO";

			case eAssetType::FONT:
				return "FONT";

			case eAssetType::TEXT:
				return "TEXT";

			case eAssetType::TEXTURE:
				return "TEXTURE";

			case eAssetType::THREE_D_MODEL:
				return "THREE_D_MODEL";

			case eAssetType::SHADER:
				return "SHADER";
			}
		}
	}
	

}
