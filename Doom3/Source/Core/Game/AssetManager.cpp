#include "AssetManager.h"

#include "../IO/AssetImporter/AssetImporter.h"
#include "../../Helper/ForLoop_Compile_Time/ForLoop_Compile.h"
template <Doom::Asset::AssetType assetType>
Doom::AssetFutureTempContainer<assetType>::~AssetFutureTempContainer()
{
	for (auto& future : futures)
	{
		auto asset = future.get();
		if (asset.has_value())
		{
			Doom::AssetManager::ImportedAssets<assetType>.AddAsset(std::move(asset.value()));
		}
	}
}

template <Doom::Asset::AssetType assetType>
std::optional<typename AssetContainer<assetType>::asset_type&> AssetContainer<assetType>::GetAsset(const D_UUID& uuid)
{
	try
	{
		return Assets.at(uuid);
	}
	catch (const std::out_of_range& e)
	{
		DEBUG_LOG("Can't find asset");
		return {};
	}
	catch (...)
	{
		DEBUG_LOG("Unknown Error", LogType::D_ERROR);
		return {};
	}
}

template <Doom::Asset::AssetType assetType>
std::optional<const typename AssetContainer<assetType>::asset_type&> AssetContainer<assetType>::GetAsset_const(const D_UUID& uuid) const
{
	try
	{
		return Assets.at(uuid);
	}
	catch (const std::out_of_range& e)
	{
		DEBUG_LOG("Can't find asset");
		return {};
	}
	catch (...)
	{
		DEBUG_LOG("Unknown Error", LogType::D_ERROR);
		return {};
	}
}

const std::filesystem::path Doom::AssetManager::AssetFolderPath{ ASSET_FOLDER_DIRECTORY };

template <Doom::Asset::AssetType assetType>
Doom::AssetContainer<assetType> Doom::AssetManager::ImportedAssets{};

template <Asset::AssetType assetType>
constexpr AssetFutureTempContainer<assetType> Doom::AssetManager::ImportAssetAndAddToContainer(const std::vector<std::filesystem::path>& paths)
{
	AssetImporter<assetType> assetImporter{ };
	return assetImporter.ImportAsset(paths);
}

void Doom::AssetManager::ImportEntireAsset()
{
	std::array<std::vector<std::filesystem::path>, Doom::Asset::GetAssetTypeCount()> AssetPaths{};
	
	/// <summary>
	/// Check file extension
	/// </summary>
	for (const auto& entry : std::filesystem::recursive_directory_iterator(AssetFolderPath))
	{
		std::filesystem::path path = entry.path();
		auto assetType = GetAssetType(path);
		if (assetType.has_value())
		{
			AssetPaths[assetType.value()].push_back(std::move(path));
		}
	}
		
	{
		AssetImporterThreadPool threadPool{ 5 };

		
		ForLoop_CompileTime<Asset::AssetType>::LoopWithLoopVariable<Asset::FirstElementOfAssetType, Asset::LastElementOfAssetType, 1, LoopJobFunctor>(AssetPaths);
	
	}
	
	//TODO : Every future should be get at here after pass all import job to threadpool
}

template <Doom::Asset::AssetType assetType>
const std::vector<typename Doom::AssetContainer<assetType>::asset_type&>& Doom::AssetContainer<assetType>::GetAssets()
{
	return AssetsForIterating;
}
