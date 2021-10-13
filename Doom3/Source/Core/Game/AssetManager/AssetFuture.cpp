#include "AssetFuture.h"

#include <Asset/Asset.h>
#include "AssetManager.h"

doom::assetimporter::AssetFuture::AssetFuture
(
	doom::asset::Asset* const asset, 
	std::future<bool>&& future
) noexcept
	:	mAsset{asset}, mFuture(std::move(future)), isWaitingEnd{false}
{

}

doom::assetimporter::AssetFuture::~AssetFuture() = default;

void doom::assetimporter::AssetFuture::WaitAsset()
{
	if(isWaitingEnd == false)
	{
		mFuture.wait();
		mAsset->OnEndImportInMainThread();
		doom::assetimporter::AssetManager::GetSingleton()->AddAssetToAssetContainer(mAsset);

		isWaitingEnd = true;
	}
}

doom::asset::Asset* doom::assetimporter::AssetFuture::GetAsset()
{
	WaitAsset();
	return mAsset;
}
