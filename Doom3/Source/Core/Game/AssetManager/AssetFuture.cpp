#include "AssetFuture.h"

#include <Asset/Asset.h>
#include "AssetManager.h"

doom::assetImporter::AssetFuture::AssetFuture
(
	doom::asset::Asset* const asset, 
	std::future<bool>&& future
) noexcept
	:	mAsset{asset}, mFuture(std::move(future)), isWaitingEnd{false}
{

}

doom::assetImporter::AssetFuture::~AssetFuture() = default;

void doom::assetImporter::AssetFuture::WaitAsset()
{
	if(isWaitingEnd == false)
	{
		mFuture.wait();
		mAsset->OnEndImportInMainThread();
		doom::assetImporter::AssetManager::GetSingleton()->AddAssetToAssetContainer(mAsset);

		isWaitingEnd = true;
	}
}

doom::asset::Asset* doom::assetImporter::AssetFuture::GetAsset()
{
	WaitAsset();
	return mAsset;
}
