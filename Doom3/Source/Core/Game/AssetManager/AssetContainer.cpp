#include "AssetContainer.h"

#include <Asset/Helper/AssetFactory.h>
#include <Asset/Asset.h>


doom::asset::AssetContainer::AssetContainer(const doom::asset::eAssetType assetTypeOfContainer)
	: mAssetTypeOfContainer(assetTypeOfContainer)
{
}

void doom::asset::AssetContainer::ClearAssets()
{
	for(doom::asset::Asset* const asset : mAssetsForIterating)
	{
		delete asset;
	}
	mAssetsForIterating.clear();

	mAssets.clear();
	mAssetsForAssetName.clear();
}

void doom::asset::AssetContainer::AddNewAsset(doom::asset::Asset* const newAsset)
{
	mAssets.emplace(newAsset->GetUUID(), newAsset);
	mAssetsForIterating.push_back(newAsset);
	mAssetsForAssetName.emplace(newAsset->GetAssetFileName(), newAsset);
}


doom::asset::AssetContainer::~AssetContainer()
{
	ClearAssets();
}

