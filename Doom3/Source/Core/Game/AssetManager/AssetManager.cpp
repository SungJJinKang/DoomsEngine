#include "AssetManager.h"

#include <Game/GameCore.h>

#include "../IO/AssetImporter/AssetImporter.h"
#include <IO/AssetImporter/Manager/AssetImporterWorkerManager.h>
#include <IO/AssetImporter/AssetImporterWorker/AssetImporterWorker_Texture.h>
#include <Asset/Helper/AssetFactory.h>

using namespace doom::assetimporter;

void doom::assetimporter::AssetManager::LoadAssetManagerSetting()
{
	AssetImporterWorker_Texture::TEXTURE_COMPRESSION_QUALITY = static_cast<float>(GameCore::GetSingleton()->mGameConfigData.GetConfigData().GetValue<double>("TEXTURE", "COMPRESSION_QUALITY"));
	AssetImporterWorker_Texture::MIP_MAP_LEVELS = GameCore::GetSingleton()->mGameConfigData.GetConfigData().GetValue<int>("TEXTURE", "MIP_MAP_LEVELS");
	AssetImporterWorker_Texture::MAX_IMAGE_SIZE = GameCore::GetSingleton()->mGameConfigData.GetConfigData().GetValue<int>("TEXTURE", "MAX_IMAGE_SIZE");
}

bool AssetManager::CheckFileIsValidAssetFile(const std::filesystem::directory_entry& entry)
{
	return entry.is_regular_file() == true;
}


void AssetManager::DestroyAllAssets()
{
	for(doom::asset::AssetContainer& assetContainer : mAssetConatiners)
	{
		assetContainer.ClearAssets();
	}
}

doom::asset::AssetContainer& AssetManager::GetAssetContainer(const doom::asset::eAssetType _eAssetType)
{
	D_ASSERT(static_cast<unsigned int>(eAssetType) < doom::asset::ENUM_ASSETTYPE_COUNT);

	return mAssetConatiners[static_cast<unsigned int>(_eAssetType)];
}

void AssetManager::AddAssetToAssetContainer(doom::asset::Asset* const asset)
{
	mAssetConatiners[static_cast<unsigned int>(asset->GetEAssetType())].AddNewAsset(asset);
}

doom::asset::Asset* AssetManager::_ImportAssetInstantly
(
	std::filesystem::path& path,
	const doom::asset::eAssetType assetType
)
{
	path.make_preferred();

	doom::asset::Asset* const newAsset = doom::asset::AssetFactory::CreateNewAsset(path, assetType);

	const bool isSuccess = doom::assetimporter::ImportAssetJob(path, newAsset);

	if(isSuccess == true)
	{
		AddAssetToAssetContainer(newAsset);
	}
	

	return newAsset;
}

doom::assetimporter::AssetFuture AssetManager::_ImportAssetAsync(std::filesystem::path& path, const doom::asset::eAssetType assetType)
{
	path.make_preferred();

	doom::asset::Asset* const newAsset = doom::asset::AssetFactory::CreateNewAsset(path, assetType);
	
	std::future<bool> assetFuture = doom::assetimporter::PushImportingAssetJobToThreadPool(path, newAsset);
	

	return doom::assetimporter::AssetFuture(newAsset, std::move(assetFuture));
}

std::vector<doom::assetimporter::AssetFuture> AssetManager::_ImportAssetAsync
(
	std::vector<std::filesystem::path>& paths,
	const std::vector<doom::asset::eAssetType>& assetTypes
)
{
	D_ASSERT(paths.size() == assets.size());

	std::vector<doom::assetimporter::AssetFuture> assetFutures;
	assetFutures.reserve(assetTypes.size());

	for (size_t i = 0; (i < assetTypes.size()) && (i < paths.size()); i++)
	{
		paths[i].make_preferred();

		doom::asset::Asset* const newAsset = doom::asset::AssetFactory::CreateNewAsset(paths[i], assetTypes[i]);

		assetFutures.emplace_back(newAsset, doom::assetimporter::PushImportingAssetJobToThreadPool(paths[i], newAsset));
	}
	
	return assetFutures;
}



doom::asset::Asset* AssetManager::_GetAsset(const D_UUID& UUID, const doom::asset::eAssetType assetType)
{
	doom::asset::Asset* asset = nullptr;

	auto iter = GetAssetContainer(assetType).mAssets.find(UUID);
	if (iter != GetAssetContainer(assetType).mAssets.end())
	{//find!!
		asset = iter->second;
	}
	else
	{//element containing UUID key doesn't exist
		D_ASSERT("Can't Find Asset");
	}

	return asset;
}

doom::asset::Asset* AssetManager::_GetAsset(const unsigned int index, const doom::asset::eAssetType assetType)
{
	doom::asset::Asset* asset = nullptr;

	if (index < GetAssetContainer(assetType).mAssetsForIterating.size())
	{
		asset = GetAssetContainer(assetType).mAssetsForIterating[index];
	}
	else
	{
		D_ASSERT("Can't Find Asset");
	}

	return asset;
}

doom::asset::Asset* AssetManager::_GetAsset(const std::string& filename, const doom::asset::eAssetType assetType)
{
	doom::asset::Asset* asset = nullptr;

	auto iter = GetAssetContainer(assetType).mAssetsForAssetName.find(filename);
	if (iter != GetAssetContainer(assetType).mAssetsForAssetName.end())
	{//find!!
		asset = iter->second;
	}
	else
	{//element containing UUID key doesn't exist
		D_ASSERT("Can't Find Asset");
	}

	return asset;
}

AssetManager::~AssetManager()
{
	DestroyAllAssets();

}

void doom::assetimporter::AssetManager::Init()
{
	LoadAssetManagerSetting();

	D_START_PROFILING(ImportEntireAsset, doom::profiler::eProfileLayers::CPU);
	ImportEntireAsset();
	D_END_PROFILING(ImportEntireAsset);

}

void doom::assetimporter::AssetManager::Update()
{

}

void doom::assetimporter::AssetManager::OnEndOfFrame()
{
}




void doom::assetimporter::AssetManager::ImportEntireAsset()
{
	CHECK_IS_EXECUTED_ON_MAIN_THREAD;

	std::filesystem::path lastEntryPath{};

	std::vector<std::filesystem::path> pathList;
	std::vector<doom::asset::eAssetType> assetTypeList;


	for (const auto& entry : std::filesystem::recursive_directory_iterator(AssetFolderPath))
	{
		if (CheckFileIsValidAssetFile(entry)== false)
		{
			continue; // if directory if folder, continue
		}

		const std::filesystem::path currentEntryPath = entry.path();
		const std::optional<::doom::asset::eAssetType> optionalAssetType = doom::assetimporter::GetAssetType(currentEntryPath);
		
		
		if (optionalAssetType.has_value())
		{
			const std::string extension = currentEntryPath.extension().string();
			const ::doom::asset::eAssetType assetType = optionalAssetType.value();

			// same file name with difference extension will be iterated sequentially
			// if Non-In Build Extension come first
			// push Non-In Build Extension and if next directory has same filename and it have In-Build Extension.
			// then pop_back vector before pusing In-Build Extension file
			//
			// if In Build Extension come first, next direcoty compare filename with vector's last element
			// And If file name is same, ignore Not-In Build Extension file

			auto iter = doom::assetimporter::AssetInBuildExtension.find(assetType);
			if (iter != doom::assetimporter::AssetInBuildExtension.end())
			{// if There is In-Build Extension of File's AssetType, 

				if (extension == iter->second)
				{// if current file is In-Build Extension
					while (true)
					{//iter from last to first for removing files with same file name with current file name
						if (pathList.size() > 0 && pathList.back().stem() == currentEntryPath.stem())
						{// if Already stored path's  last element file name is same with current file name
							pathList.pop_back();
						}
						else
						{
							break;
						}
					}
				}
				else
				{// if current file is not(!!) In-Build Extension
					if (pathList.size() > 0 && pathList.back().stem() == currentEntryPath.stem())
					{// if Already stored path's last element have same file name with current file name
						continue; // ignore current file
					}
				}
			}

			pathList.push_back(std::move(currentEntryPath));
			assetTypeList.push_back(assetType);
		}
		
	}
	
	std::vector<doom::assetimporter::AssetFuture> assetFutureList = _ImportAssetAsync(pathList, assetTypeList);
	for(doom::assetimporter::AssetFuture& future : assetFutureList)
	{
		future.WaitAsset();
	}
	

	mAssetImporterWorkerManager.ClearAssetImporterWorker();
	
}

