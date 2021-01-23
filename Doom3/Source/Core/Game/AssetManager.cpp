#include "AssetManager.h"

#include <iterator>

#include "../IO/AssetImporter/AssetImporter.h"
#include "../../Helper/ForLoop_Compile_Time/ForLoop_Compile.h"


const std::filesystem::path Doom::AssetManager::AssetFolderPath{ ASSET_FOLDER_DIRECTORY };




void Doom::AssetManager::ImportEntireAsset()
{
	std::array<std::vector<std::filesystem::path>, Doom::Asset::GetAssetTypeCount()> AssetPaths{};
	
	/// <summary>
	/// Check file extension
	/// </summary>
	for (const auto& entry : std::filesystem::recursive_directory_iterator(AssetFolderPath))
	{
		std::filesystem::path path = entry.path();
		auto assetType = Doom::AssetImporter::GetAssetType(path);
		if (assetType.has_value())
		{
			AssetPaths[assetType.value()].push_back(std::move(path));
		}
	}
		
	{
		Doom::AssetImporter::Assetimporter threadPool{ 5 };

		ForLoop_CompileTime<Asset::AssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, Doom::AssetManager::ImportAssetFutureFunctor>(AssetPaths);
		ForLoop_CompileTime<Asset::AssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, Doom::AssetManager::GetAssetFutureFunctor>();

	}

	
}

