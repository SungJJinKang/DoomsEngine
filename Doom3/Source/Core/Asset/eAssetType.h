#pragma once
#include <magic_enum.hpp>

namespace doom
{
	namespace asset
	{
		enum class eAssetType : unsigned int
		{
			AUDIO = 0,
			FONT,
			TEXT,
			TEXTURE,
			THREE_D_MODEL,
			SHADER
		};
		constexpr inline size_t ENUM_ASSETTYPE_COUNT = magic_enum::enum_count<eAssetType>();

		constexpr inline eAssetType FIRST_ENUM_ASSETTYPE_VALUE = magic_enum::enum_value<eAssetType>(0);
		constexpr inline eAssetType LAST_ENUM_ASSETTYPE_VALUE = magic_enum::enum_value<eAssetType>(ENUM_ASSETTYPE_COUNT - 1);

		constexpr auto GetAssetTypeName(eAssetType assetType)
		{
			return magic_enum::enum_name(assetType);
		}
	}
	

}