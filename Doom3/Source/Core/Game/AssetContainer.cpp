#include "AssetContainer.h"

using namespace doom;
using namespace doom::assetimporter;

template class AssetContainer<Asset::eAssetType::AUDIO>;
template class AssetContainer<Asset::eAssetType::FONT>;
template class AssetContainer<Asset::eAssetType::SHADER>;
template class AssetContainer<Asset::eAssetType::TEXT>;
template class AssetContainer<Asset::eAssetType::TEXTURE>;
template class AssetContainer<Asset::eAssetType::THREE_D_MODEL>;


template <Asset::eAssetType assetType>
constexpr AssetContainer<assetType>::AssetContainer() : mAssets{}, mAssetsForIterating{}, ImportedAssetFutures{}
{

}

template <Asset::eAssetType assetType>
void AssetContainer<assetType>::AddAsset(AssetContainer<assetType>::container_asset_type_t& asset)
{
	auto pair = this->mAssets.emplace(std::make_pair(asset.mUUID, std::move(asset)));

	if (pair.second == true)
	{
		mAssetsForIterating.push_back(pair.first->second);
	}
	else
	{
		D_DEBUG_LOG("UUID is already inserted", logger::LogType::D_ERROR);
	}
}

template <Asset::eAssetType assetType>
void AssetContainer<assetType>::AddAsset(AssetContainer<assetType>::container_imported_asset_future_t&& asset)
{
	ImportedAssetFutures.push_back(std::move(asset));
}

template <Asset::eAssetType assetType>
void AssetContainer<assetType>::AddAsset(std::vector<AssetContainer<assetType>::container_imported_asset_future_t>&& assets)
{
	ImportedAssetFutures.insert(ImportedAssetFutures.end(), std::make_move_iterator(assets.begin()), std::make_move_iterator(assets.end()));
}

template <Asset::eAssetType assetType>
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

template <Asset::eAssetType assetType>
std::optional<std::reference_wrapper<typename AssetContainer<assetType>::container_asset_type_t>> AssetContainer<assetType>::GetAsset(const D_UUID& UUID)
{
	auto iter = mAssets.find(UUID);
	if (iter != mAssets.end())
	{//find!!
		return iter->second;
	}
	else
	{//element containing UUID key doesn't exist
		return {};
	}
}

template <Asset::eAssetType assetType>
std::optional<std::reference_wrapper<const typename AssetContainer<assetType>::container_asset_type_t>> AssetContainer<assetType>::GetAsset_const(const D_UUID& UUID) const
{
	auto iter = mAssets.find(UUID);
	if (iter != mAssets.end())
	{//find!!
		return iter->second;
	}
	else
	{//element containing UUID key doesn't exist
		return {};
	}
}


template <Asset::eAssetType assetType>
std::optional<std::reference_wrapper<typename AssetContainer<assetType>::container_asset_type_t>> AssetContainer<assetType>::GetAsset(const unsigned int index)
{
	if (index >= 0 && index < this->mAssetsForIterating.size())
	{
		return this->mAssetsForIterating[index];
	}
	else
	{
		return {};
	}
}


template <Asset::eAssetType assetType>
std::optional<std::reference_wrapper<const typename AssetContainer<assetType>::container_asset_type_t>> AssetContainer<assetType>::GetAsset_const(const unsigned int index) const
{
	if (index >= 0 && index < this->mAssetsForIterating.size())
	{
		return this->mAssetsForIterating[index];
	}
	else
	{
		return {};
	}
}

template <doom::Asset::eAssetType assetType>
const std::vector<std::reference_wrapper<typename doom::assetimporter::AssetContainer<assetType>::container_asset_type_t>>& doom::assetimporter::AssetContainer<assetType>::GetAssets()
{
	return this->mAssetsForIterating;
}
