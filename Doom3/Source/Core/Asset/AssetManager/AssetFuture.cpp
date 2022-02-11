#include "AssetFuture.h"

#include <Asset/Asset.h>
#include "AssetManager.h"

dooms::assetImporter::AssetFuture::AssetFuture
(
	dooms::asset::Asset* const asset, 
	std::future<bool>&& future
) noexcept
	:	mAsset{asset}, mFuture(std::move(future)), isWaitingEnd{false}
{

}

dooms::assetImporter::AssetFuture::~AssetFuture() = default;

void dooms::assetImporter::AssetFuture::WaitAsset()
{
	if(isWaitingEnd == false)
	{
		mFuture.wait();
		mAsset->OnEndImportInMainThread();
		dooms::assetImporter::AssetManager::GetSingleton()->AddAssetToAssetContainer(mAsset);

		isWaitingEnd = true;
	}
}

dooms::asset::Asset* dooms::assetImporter::AssetFuture::GetAsset()
{
	WaitAsset();
	return mAsset;
}
