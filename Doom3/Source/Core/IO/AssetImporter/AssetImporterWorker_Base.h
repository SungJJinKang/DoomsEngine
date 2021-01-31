#pragma once
#include <optional>

#include "../../Core.h"

#include "../../Asset/Asset.h"


namespace doom
{
	namespace assetimporter
	{
		template <Asset::eAssetType assetType>
		std::optional<Asset::asset_type_t<assetType>> ReadAssetFile(std::filesystem::path path);
	}
}