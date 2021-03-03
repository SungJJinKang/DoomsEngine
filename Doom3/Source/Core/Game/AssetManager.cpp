#include "AssetManager.h"

#include <iterator>

#include "../IO/AssetImporter/AssetImporter.h"
#include "../../Helper/ForLoop_Compile_Time/ForLoop_Compile.h"


using namespace doom::assetimporter;

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
	std::filesystem::path lastEntryPath{};

	std::array<std::vector<std::filesystem::path>, doom::Asset::GetAssetTypeCount()> entireAssetPaths{};
	/// <summary>
	/// Check file extension
	/// </summary>
	for (const auto& entry : std::filesystem::recursive_directory_iterator(AssetFolderPath))
	{
		if (entry.is_regular_file() == false)
		{
			
			continue; // if directory if folder, continue
		}

		std::filesystem::path currentEntryPath = entry.path();
		std::optional<doom::eAssetType> optionalAssetType = Assetimporter::GetAssetType(currentEntryPath);

	
		
		if (optionalAssetType.has_value())
		{
			std::string extension = currentEntryPath.extension().string();
			doom::eAssetType assetType = optionalAssetType.value();

			// same file name with difference extension will be iterated sequentially
			// if Non-In Build Extension come first
			// push Non-In Build Extension and if next directory has same filename and it have In-Build Extension.
			// then pop_back vector before pusing In-Build Extension file
			//
			// if In Build Extension come first, next direcoty compare filename with vector's last element
			// And If file name is same, ignore Not-In Build Extension file

			auto iter = Assetimporter::AssetInBuildExtension.find(assetType);
			if (iter != Assetimporter::AssetInBuildExtension.end())
			{// if There is In-Build Extension of File's AssetType, 

				if (extension == iter->second)
				{// if current file is In-Build Extension
					while (true)
					{//iter from last to first for removing files with same file name with current file name
						if (entireAssetPaths[static_cast<unsigned int>(assetType)].size() > 0 && entireAssetPaths[static_cast<unsigned int>(assetType)].back().stem() == currentEntryPath.stem())
						{// if Already stored path's  last element file name is same with current file name
							entireAssetPaths[static_cast<unsigned int>(assetType)].pop_back();
						}
						else
						{
							break;
						}
					}
				}
				else
				{// if current file is not(!!) In-Build Extension
					if (entireAssetPaths[static_cast<unsigned int>(assetType)].size() > 0 && entireAssetPaths[static_cast<unsigned int>(assetType)].back().stem() == currentEntryPath.stem())
					{// if Already stored path's last element have same file name with current file name
						continue; // ignore current file
					}
				}
			}

			entireAssetPaths[static_cast<unsigned int>(assetType)].push_back(std::move(currentEntryPath));
		}
		
	}

	//push stored paths to AssetManager::AssetPaths
	for (size_t i = 0; i < entireAssetPaths.size(); ++i)
	{
		AssetManager::AssetPaths[i].insert(AssetManager::AssetPaths[i].end(), entireAssetPaths[i].begin(), entireAssetPaths[i].end());
	}
	
		
	{
		ForLoop_CompileTime<eAssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, ImportAssetInitSetting>();
		ForLoop_CompileTime<eAssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, ImportAssetFutureFunctor>(entireAssetPaths);
		ForLoop_CompileTime<eAssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, GetAssetFutureFunctor>();
	}
	ForLoop_CompileTime<eAssetType>::Loop<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, OnEndImportInMainThreadFunctor>();
	
}



const std::array<std::vector<std::filesystem::path>, doom::Asset::GetAssetTypeCount()>& AssetManager::GetAllAssetPath()
{
	return AssetManager::AssetPaths;
}

