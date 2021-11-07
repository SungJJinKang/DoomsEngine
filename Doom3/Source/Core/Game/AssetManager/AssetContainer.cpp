#include "AssetContainer.h"

#include <Asset/Helper/AssetFactory.h>
#include <Asset/Asset.h>


dooms::asset::AssetContainer::AssetContainer(const dooms::asset::eAssetType assetTypeOfContainer)
	: mAssetTypeOfContainer(assetTypeOfContainer)
{
}

void dooms::asset::AssetContainer::ClearAssets()
{
	for(dooms::asset::Asset* const asset : mAssetsForIterating)
	{
		delete asset;
	}
	mAssetsForIterating.clear();

	mAssets.clear();
	mAssetsForAssetName.clear();
}

void dooms::asset::AssetContainer::AddNewAsset(dooms::asset::Asset* const newAsset)
{
	mAssets.emplace(newAsset->GetUUID(), newAsset);
	mAssetsForIterating.push_back(newAsset);
	mAssetsForAssetName.emplace(newAsset->GetAssetFileName(), newAsset);
}


dooms::asset::AssetContainer::~AssetContainer()
{
	ClearAssets();
}

