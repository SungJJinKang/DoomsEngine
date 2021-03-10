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
		constexpr inline size_t AssetTypeCount = magic_enum::enum_count<eAssetType>();

		constexpr inline eAssetType FirstAssetType = magic_enum::enum_value<eAssetType>(0);
		constexpr inline eAssetType LastAssetType = magic_enum::enum_value<eAssetType>(AssetTypeCount - 1);

		constexpr auto GetAssetTypeName(eAssetType assetType)
		{
			return magic_enum::enum_name(assetType);
		}
	}
	

}