#include "ImportedAssetPort.h"

using namespace doom;
using namespace doom::assetimporter;

template class ImportedAssetPort<eAssetType::AUDIO>;
template class ImportedAssetPort<eAssetType::FONT>;
template class ImportedAssetPort<eAssetType::SHADER>;
template class ImportedAssetPort<eAssetType::TEXT>;
template class ImportedAssetPort<eAssetType::TEXTURE>;
template class ImportedAssetPort<eAssetType::THREE_D_MODEL>;


template <eAssetType assetType>
constexpr ImportedAssetPort<assetType>::ImportedAssetPort() : mAssets{}, mAssetsForIterating{}, mAssetsForAssetName{}, GetFutureWaitingAssets{}
{

}

template <eAssetType assetType>
typename ImportedAssetPort<assetType>::container_asset_type_t::asset_type* ImportedAssetPort<assetType>::AddAsset(asset_type&& asset)
{
	
	auto pair = this->mAssets.emplace(std::make_pair(asset.GetUUID(), AssetContainer<assetType>(std::move(asset))));

	if (pair.second == true)
	{
		D_DEBUG_LOG({ "Asset is completely imported : ", pair.first->second.GetImportedAsset()->GetAssetFileName() }, eLogType::D_LOG);
		this->mAssetsForIterating.emplace_back(pair.first->second);
		this->mAssetsForAssetName.emplace(std::make_pair(pair.first->second.GetImportedAsset()->GetAssetFileName(), std::ref(pair.first->second)));
		return pair.first->second.GetImportedAsset();
	}
	else
	{
		D_DEBUG_LOG("UUID is already inserted", logger::eLogType::D_ERROR);
		return nullptr;
	}
}

template <eAssetType assetType>
AssetContainer<assetType>& ImportedAssetPort<assetType>::AddAssetFuture(doom::assetimporter::imported_asset_future_t<assetType>&& assetFuture, const std::filesystem::path& path)
{
	D_UUID reservedUUID = GenerateUUID();
	auto pair = this->mAssets.emplace(std::make_pair(reservedUUID, AssetContainer<assetType>(std::move(assetFuture), path, reservedUUID)));

	if (pair.second == true)
	{
		D_DEBUG_LOG({ "Asset is completely imported : ", path.filename().string() }, eLogType::D_LOG);
		this->mAssetsForIterating.emplace_back(pair.first->second);
		this->mAssetsForAssetName.emplace(std::make_pair(path.filename().string(), std::ref(pair.first->second)));
	}
	else
	{
		D_DEBUG_LOG("UUID is already inserted", logger::eLogType::D_ERROR);
		NEVER_HAPPEN;
	}

	this->GetFutureWaitingAssets.emplace_back(pair.first->second);
	return pair.first->second;
}

template <eAssetType assetType>
std::vector<std::reference_wrapper<AssetContainer<assetType>>> ImportedAssetPort<assetType>::AddAssetFutures(std::vector<doom::assetimporter::imported_asset_future_t<assetType>>&& assetFutures, const std::vector<std::filesystem::path>& paths)
{
	std::vector<std::reference_wrapper<AssetContainer<assetType>>> waitingGetFutureAssets{};
	for (size_t i = 0 ; i < assetFutures.size() ; i++)
	{
		auto& getAssetWaitingAsset = this->AddAssetFuture(std::move(assetFutures[i]), paths[i]);
		waitingGetFutureAssets.emplace_back(getAssetWaitingAsset);
	}

	return waitingGetFutureAssets;
}

template <eAssetType assetType>
void ImportedAssetPort<assetType>::GetAssetFutures()
{
	CHECK_IS_EXECUTED_ON_MAIN_THREAD; // TODO: 나중에 다른 스레드도 가능하게 바꾸자

	for (auto& getFutureWaitingAsset : this->GetFutureWaitingAssets)
	{
		auto completelyImportedAsset = getFutureWaitingAsset.get().GetFuture();
		this->PostProcessWaitingAssets.push_back(completelyImportedAsset);
	}
	this->GetFutureWaitingAssets.clear();
}
