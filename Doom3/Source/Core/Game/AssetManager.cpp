#include "AssetManager.h"

#include <iterator>

#include "../IO/AssetImporter/AssetImporter.h"
#include "../../Helper/ForLoop_Compile_Time/ForLoop_Compile.h"



void doom::assetimporter::AssetManager::Init()
{

}

void doom::assetimporter::AssetManager::Update()
{

}

void doom::assetimporter::AssetManager::OnEndOfFrame()
{
}




void doom::assetimporter::AssetManager::ImportEntireAsset()
{
	
	
	/// <summary>
	/// Check file extension
	/// </summary>
	for (const auto& entry : std::filesystem::recursive_directory_iterator(AssetFolderPath))
	{
		if (entry.is_regular_file() == false)
		{
			continue; // if directory if folder, continue
		}

		std::filesystem::path path = entry.path();
		auto assetType = doom::assetimporter::Assetimporter::GetAssetType(path);
		if (assetType.has_value())
		{
			doom::assetimporter::AssetManager::AssetPaths[static_cast<unsigned int>(assetType.value())].push_back(std::move(path));
		}
	}
		
	{
		doom::assetimporter::Assetimporter threadPool{ 5 };

		ForLoop_CompileTime<eAssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, doom::assetimporter::ImportAssetFutureFunctor>(AssetPaths);
		ForLoop_CompileTime<eAssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, doom::assetimporter::GetAssetFutureFunctor>();
	}
	ForLoop_CompileTime<eAssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, doom::assetimporter::OnEndImportInMainThreadFunctor>();
	
}

const std::array<std::vector<std::filesystem::path>, doom::Asset::GetAssetTypeCount()>& doom::assetimporter::AssetManager::GetAllAssetPath()
{
	return AssetPaths;
}

