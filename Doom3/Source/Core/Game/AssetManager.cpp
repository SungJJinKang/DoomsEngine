#include "AssetManager.h"

#include "../IO/AssetImporter/AssetImporter.h"

template <Doom::Asset::AssetType assetType>
std::optional<const typename AssetContainer<assetType>::type&> AssetContainer<assetType>::GetAsset(const D_UUID& uuid)
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

template <Asset::AssetType assetType, size_t ThreadSize>
void Doom::AssetManager::ImportAssetAndAddToContainer(const std::vector<std::filesystem::path>& paths)
{
	if (paths.size() == 0)
		return;

	AssetImporter<assetType> assetImporter{ ThreadSize };
	auto ImportedAssets = assetImporter.ImportAsset(paths);

	for (auto& asset : ImportedAssets)
	{
		if (asset.has_value())
		{
			Doom::AssetManager::ImportedAssets<assetType>.AddAsset(std::move(asset.value()));
		}
	}
	
}

void Doom::AssetManager::ImportEntireAsset()
{
	std::array<std::vector<std::filesystem::path>, Doom::Asset::AssetTypeCount> AssetPaths{};
	
	for (const auto& entry : std::filesystem::recursive_directory_iterator(AssetFolderPath))
	{
		std::filesystem::path path = entry.path();
		auto assetType = GetAssetType(path);
		if (assetType.has_value())
		{
			AssetPaths[assetType.value()].push_back(std::move(path));
		}
		
	}
		
	ImportAssetAndAddToContainer<Asset::AssetType::AUDIO, 5>(AssetPaths[Asset::AssetType::AUDIO]);
	ImportAssetAndAddToContainer<Asset::AssetType::FONT, 5>(AssetPaths[Asset::AssetType::FONT]);
	ImportAssetAndAddToContainer<Asset::AssetType::TEXT, 5>(AssetPaths[Asset::AssetType::TEXT]);
	ImportAssetAndAddToContainer<Asset::AssetType::TEXTURE, 5>(AssetPaths[Asset::AssetType::TEXTURE]);
	ImportAssetAndAddToContainer<Asset::AssetType::THREE_D_MODELL, 5>(AssetPaths[Asset::AssetType::THREE_D_MODELL]);
}

