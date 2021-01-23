#include "AssetContainer.h"


using namespace Doom;




template <Asset::AssetType assetType>
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

template <Asset::AssetType assetType>
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

template <Doom::Asset::AssetType assetType>
const std::vector<typename Doom::AssetContainer<assetType>::asset_type&>& Doom::AssetContainer<assetType>::GetAssets()
{
	return AssetsForIterating;
}
