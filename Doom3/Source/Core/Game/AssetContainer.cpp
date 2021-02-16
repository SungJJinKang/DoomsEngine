#include "AssetContainer.h"

using namespace doom;
using namespace doom::assetimporter;

template class AssetContainer<eAssetType::AUDIO>;
template class AssetContainer<eAssetType::FONT>;
template class AssetContainer<eAssetType::SHADER>;
template class AssetContainer<eAssetType::TEXT>;
template class AssetContainer<eAssetType::TEXTURE>;
template class AssetContainer<eAssetType::THREE_D_MODEL>;


template <eAssetType assetType>
constexpr AssetContainer<assetType>::AssetContainer() : mAssets{}, mAssetsForIterating{}, mAssetsForAssetName{}, ImportedAssetFutures{}
{

}

template <eAssetType assetType>
void AssetContainer<assetType>::AddAsset(AssetContainer<assetType>::container_asset_type_t& asset)
{
	auto pair = this->mAssets.emplace(std::make_pair(asset.GetUUID(), std::move(asset)));

	if (pair.second == true)
	{
		D_DEBUG_LOG({ "Asset is completely imported : ", pair.first->second.GetAssetFileName() }, eLogType::D_LOG);
		this->mAssetsForIterating.push_back(pair.first->second);
		this->mAssetsForAssetName.emplace(std::make_pair(pair.first->second.GetAssetFileName(), std::ref(pair.first->second)));
		
	}
	else
	{
		D_DEBUG_LOG("UUID is already inserted", logger::eLogType::D_ERROR);
	}
}

template <eAssetType assetType>
void AssetContainer<assetType>::AddAssetFuture(AssetContainer<assetType>::container_imported_asset_future_t&& asset)
{
	ImportedAssetFutures.push_back(std::move(asset));
}

template <eAssetType assetType>
void AssetContainer<assetType>::AddAssetFutures(std::vector<AssetContainer<assetType>::container_imported_asset_future_t>&& assets)
{
	ImportedAssetFutures.insert(ImportedAssetFutures.end(), std::make_move_iterator(assets.begin()), std::make_move_iterator(assets.end()));
}

template <eAssetType assetType>
void AssetContainer<assetType>::GetAssetFutures()
{
	for (auto& future : this->ImportedAssetFutures)
	{
		auto asset = future.get();
		if (asset.has_value())
		{
			this->AddAsset(asset.value());
		}
	}
	this->ImportedAssetFutures.clear();
}
