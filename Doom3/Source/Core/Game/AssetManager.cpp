#include "AssetManager.h"

#include <iterator>

#include "../IO/AssetImporter/AssetImporter.h"
#include "../../Helper/ForLoop_Compile_Time/ForLoop_Compile.h"


const std::filesystem::path doom::AssetManager::AssetFolderPath{ ASSET_FOLDER_DIRECTORY };




void doom::AssetManager::ImportEntireAsset()
{
	std::array<std::vector<std::filesystem::path>, doom::Asset::GetAssetTypeCount()> AssetPaths{};
	
	/// <summary>
	/// Check file extension
	/// </summary>
	for (const auto& entry : std::filesystem::recursive_directory_iterator(AssetFolderPath))
	{
		std::filesystem::path path = entry.path();
		auto assetType = doom::assetimporter::GetAssetType(path);
		if (assetType.has_value())
		{
			AssetPaths[assetType.value()].push_back(std::move(path));
		}
	}
		
	{
		doom::assetimporter::Assetimporter threadPool{ 5 };

		ForLoop_CompileTime<Asset::eAssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, doom::AssetManager::ImportAssetFutureFunctor>(AssetPaths);
		ForLoop_CompileTime<Asset::eAssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, doom::AssetManager::GetAssetFutureFunctor>();

	}

	
}

