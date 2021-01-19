#include "AssetManager.h"

#include "../IO/AssetImporter/AssetImporter.h"

void Doom::AssetManager::ImportEntireAsset()
{
	std::vector<std::filesystem::path> AssetPaths{};
	
	std::array<std::vector<const std::filesystem::path&>, Doom::AssetTypeCount
	std::vector<const std::filesystem::path&> ClassifiedAssetPath{ Doom::AssetTypeCount };

	for (const auto& entry : std::filesystem::recursive_directory_iterator(AssetFolderPath))
	{
		std::filesystem::path path = entry.path();
		auto assetType = GetAssetType(path);
	}
		AssetPaths.push_back(entry.path());


}

