#include "AssetContainer.h"


using namespace doom;




template <Asset::eAssetType assetType>
std::optional<typename AssetContainer<assetType>::this_asset_type_t&> AssetContainer<assetType>::GetAsset(const D_UUID& mUUID)
{
	try
	{
		return mAssets.at(mUUID);
	}
	catch (const std::out_of_range& e)
	{
		DEBUG_LOG("Can't find asset");
		return {};
	}
	catch (...)
	{
		DEBUG_LOG("Unknown Error", log::LogType::D_ERROR);
		return {};
	}
}

template <Asset::eAssetType assetType>
std::optional<const typename AssetContainer<assetType>::this_asset_type_t&> AssetContainer<assetType>::GetAsset_const(const D_UUID& mUUID) const
{
	try
	{
		return mAssets.at(mUUID);
	}
	catch (const std::out_of_range& e)
	{
		DEBUG_LOG("Can't find asset");
		return {};
	}
	catch (...)
	{
		DEBUG_LOG("Unknown Error", log::LogType::D_ERROR);
		return {};
	}
}

template <doom::Asset::eAssetType assetType>
const std::vector<typename doom::AssetContainer<assetType>::this_asset_type_t&>& doom::AssetContainer<assetType>::GetAssets()
{
	return mAssetsForIterating;
}
