#include "AssetManager.h"

#include <Game/GameCore.h>

#include <Asset/AssetImportExporter/AssetImporter/assetImporter.h>
#include <Asset/AssetImportExporter/AssetImporter/Manager/AssetImporterWorkerManager.h>
#include <Asset/AssetImportExporter/AssetImporter/AssetImporterWorker/AssetImporterWorker_Texture.h>
#include <Asset/Helper/AssetFactory.h>

//#define MULTI_THREAD_ASSET_IMPORT

using namespace dooms::assetImporter;

void dooms::assetImporter::AssetManager::LoadAssetManagerSetting()
{
	AssetImporterWorker_Texture::TEXTURE_COMPRESSION_QUALITY = static_cast<FLOAT32>(GameCore::GetSingleton()->mGameConfigData.GetConfigData().GetValue<FLOAT64>("TEXTURE", "COMPRESSION_QUALITY"));
	AssetImporterWorker_Texture::MIP_MAP_LEVELS = GameCore::GetSingleton()->mGameConfigData.GetConfigData().GetValue<INT32>("TEXTURE", "MIP_MAP_LEVELS");
	AssetImporterWorker_Texture::MAX_IMAGE_SIZE = GameCore::GetSingleton()->mGameConfigData.GetConfigData().GetValue<INT32>("TEXTURE", "MAX_IMAGE_SIZE");
}

bool AssetManager::CheckFileIsValidAssetFile(const std::filesystem::directory_entry& entry)
{
	return entry.is_regular_file() == true;
}


void AssetManager::DestroyAllAssets()
{
	for(dooms::asset::AssetContainer& assetContainer : mAssetConatiners)
	{
		assetContainer.ClearAssets();
	}
}

dooms::asset::AssetContainer& AssetManager::GetAssetContainer(const dooms::asset::eAssetType _eAssetType)
{
	D_ASSERT(static_cast<UINT32>(_eAssetType) < dooms::asset::ENUM_ASSETTYPE_COUNT);

	return mAssetConatiners[static_cast<UINT32>(_eAssetType)];
}

void AssetManager::AddAssetToAssetContainer(dooms::asset::Asset* const asset)
{
	mAssetConatiners[static_cast<UINT32>(asset->GetEAssetType())].AddNewAsset(asset);
}

dooms::asset::Asset* AssetManager::_ImportAssetInstantly
(
	std::filesystem::path& path,
	const dooms::asset::eAssetType assetType
)
{
	path.make_preferred();

	dooms::asset::Asset* const newAsset = dooms::asset::AssetFactory::CreateNewAsset(path, assetType);

	const bool isSuccess = dooms::assetImporter::ImportAssetJob(path, newAsset);

	if(isSuccess == true)
	{
		AddAssetToAssetContainer(newAsset);

		newAsset->OnEndImportInSubThread();
		newAsset->OnEndImportInMainThread();
	}
	

	return newAsset;
}

void AssetManager::_ImportAssetInstantly
(
	std::vector<std::filesystem::path>& paths,
	const std::vector<dooms::asset::eAssetType>& assetTypes
)
{
	D_ASSERT(paths.size() == assetTypes.size());

	for(size_t i = 0 ; i < paths.size() ; i++)
	{
		_ImportAssetInstantly(paths[i], assetTypes[i]);
	}
}

dooms::assetImporter::AssetFuture AssetManager::_ImportAssetAsync(std::filesystem::path& path, const dooms::asset::eAssetType assetType)
{
	path.make_preferred();

	dooms::asset::Asset* const newAsset = dooms::asset::AssetFactory::CreateNewAsset(path, assetType);
	
	std::future<bool> assetFuture = dooms::assetImporter::PushImportingAssetJobToThreadPool(path, newAsset);
	

	return dooms::assetImporter::AssetFuture(newAsset, std::move(assetFuture));
}

std::vector<dooms::assetImporter::AssetFuture> AssetManager::_ImportAssetAsync
(
	std::vector<std::filesystem::path>& paths,
	const std::vector<dooms::asset::eAssetType>& assetTypes
)
{
	D_ASSERT(paths.size() == assetTypes.size());

	std::vector<dooms::assetImporter::AssetFuture> assetFutures;
	assetFutures.reserve(assetTypes.size());

	for (size_t i = 0; (i < assetTypes.size()) && (i < paths.size()); i++)
	{
		paths[i].make_preferred();

		dooms::asset::Asset* const newAsset = dooms::asset::AssetFactory::CreateNewAsset(paths[i], assetTypes[i]);

		assetFutures.emplace_back(newAsset, dooms::assetImporter::PushImportingAssetJobToThreadPool(paths[i], newAsset));
	}
	
	return assetFutures;
}



dooms::asset::Asset* AssetManager::_GetAsset(const D_UUID& UUID, const dooms::asset::eAssetType assetType)
{
	dooms::asset::Asset* asset = nullptr;

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

dooms::asset::Asset* AssetManager::_GetAsset(const UINT32 index, const dooms::asset::eAssetType assetType)
{
	dooms::asset::Asset* asset = nullptr;

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

dooms::asset::Asset* AssetManager::_GetAsset(const std::string& filename, const dooms::asset::eAssetType assetType)
{
	dooms::asset::Asset* asset = nullptr;

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

AssetManager::AssetManager()
	:	mAssetImporterWorkerManager(),
		AssetFolderPath{ std::filesystem::u8path(dooms::path::_GetAssetFolderDirectory()) },
		mAssetConatiners
		{
			dooms::asset::AssetContainer(dooms::asset::eAssetType::AUDIO),
			dooms::asset::AssetContainer(dooms::asset::eAssetType::FONT),
			dooms::asset::AssetContainer(dooms::asset::eAssetType::TEXT),
			dooms::asset::AssetContainer(dooms::asset::eAssetType::TEXTURE),
			dooms::asset::AssetContainer(dooms::asset::eAssetType::THREE_D_MODEL),
			dooms::asset::AssetContainer(dooms::asset::eAssetType::SHADER)
		}
{
	AddToRootObjectList();
}

AssetManager::~AssetManager()
{

}

void AssetManager::OnSetPendingKill()
{
	IGameFlow::OnSetPendingKill();

	DestroyAllAssets();
}

void dooms::assetImporter::AssetManager::Init(const int argc, char* const* const argv)
{
	AddToRootObjectList();

	LoadAssetManagerSetting();

	D_START_PROFILING(ImportEntireAsset, dooms::profiler::eProfileLayers::CPU);
	ImportEntireAsset();
	D_END_PROFILING(ImportEntireAsset);

}

void dooms::assetImporter::AssetManager::Update()
{

}

void dooms::assetImporter::AssetManager::OnEndOfFrame()
{
}




void dooms::assetImporter::AssetManager::ImportEntireAsset()
{
	//CHECK_IS_EXECUTED_ON_MAIN_THREAD;

	std::filesystem::path lastEntryPath{};

	std::vector<std::filesystem::path> pathList;
	std::vector<dooms::asset::eAssetType> assetTypeList;


	for (const auto& entry : std::filesystem::recursive_directory_iterator(AssetFolderPath))
	{
		if (CheckFileIsValidAssetFile(entry)== false)
		{
			continue; // if directory if folder, continue
		}

		const std::filesystem::path currentEntryPath = entry.path();
		const std::optional<::dooms::asset::eAssetType> optionalAssetType = dooms::assetImporter::GetAssetType(currentEntryPath);
		
		
		if (optionalAssetType.has_value())
		{
			const std::string extension = currentEntryPath.extension().string();
			const ::dooms::asset::eAssetType assetType = optionalAssetType.value();

			// same file name with difference extension will be iterated sequentially
			// if Non-In Build Extension come first
			// push Non-In Build Extension and if next directory has same filename and it have In-Build Extension.
			// then pop_back vector before pusing In-Build Extension file
			//
			// if In Build Extension come first, next direcoty compare filename with vector's last element
			// And If file name is same, ignore Not-In Build Extension file

			auto iter = dooms::assetImporter::AssetInBuildExtension.find(assetType);
			if (iter != dooms::assetImporter::AssetInBuildExtension.end())
			{// if There is In-Build Extension of File's AssetType, 

				if (extension == iter->second)
				{// if current file is In-Build Extension
					while (true)
					{//iter from last to first for removing files with same file name with current file name
						if (pathList.size() > 0 && pathList.back().stem() == currentEntryPath.stem())
						{// if Already stored path's  last element file name is same with current file name
							pathList.pop_back();
							assetTypeList.pop_back();
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

#ifdef MULTI_THREAD_ASSET_IMPORT
	std::vector<dooms::assetImporter::AssetFuture> assetFutureList = _ImportAssetAsync(pathList, assetTypeList);
	for (dooms::assetImporter::AssetFuture& future : assetFutureList)
	{
		future.WaitAsset();
	}
	mAssetImporterWorkerManager.ClearAssetImporterWorker();
#else
	_ImportAssetInstantly(pathList, assetTypeList);
#endif
	
	mAssetImporterWorkerManager.ClearAssetImporterWorker();
}

