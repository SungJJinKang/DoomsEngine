#pragma once
#include "AssetImporterBase.h"
#include "../../Asset/TextAsset.h"

using namespace Doom;


template<>
std::optional <Asset::AssetTypeConditional_t<Asset::AssetType::TEXT>> Doom::AssetImporter<Asset::AssetType::TEXT>::ReadAssetFile(std::filesystem::path path, AssetImporter<Asset::AssetType::TEXT>* assetImporter)
{
	std::ifstream inputFileStream(path, std::ios::in | std::ios::binary | std::ios::ate);

	if (inputFileStream.is_open())
	{
		std::string str{};
		str.reserve(inputFileStream.tellg()); // prevent reallocation. reallocation is really really expensive
		inputFileStream.seekg(0, std::ios::beg);
		str.assign(std::istreambuf_iterator{ inputFileStream }, {});
		inputFileStream.close();

		return str;
	}
	else
	{
		return {};
	}
}