#include "ImportedAssetPort.h"

using namespace doom;
using namespace doom::assetimporter;

template class ImportedAssetPort<::doom::asset::eAssetType::AUDIO>;
template class ImportedAssetPort<::doom::asset::eAssetType::FONT>;
template class ImportedAssetPort<::doom::asset::eAssetType::SHADER>;
template class ImportedAssetPort<::doom::asset::eAssetType::TEXT>;
template class ImportedAssetPort<::doom::asset::eAssetType::TEXTURE>;
template class ImportedAssetPort<::doom::asset::eAssetType::THREE_D_MODEL>;


template <::doom::asset::eAssetType assetType>
constexpr ImportedAssetPort<assetType>::ImportedAssetPort() : mAssets{}, mAssetsForIterating{}, mAssetsForAssetName{}
{

}


template <::doom::asset::eAssetType assetType>
typename ::doom::asset::Asset::asset_type_t<assetType>* ImportedAssetPort<assetType>::AddNewAsset(const std::filesystem::path& assetFileDirectory)
{
	::doom::asset::Asset::asset_type_t<assetType> newAsset{};
	D_UUID uuid = doom::GenerateUUID();
	newAsset.SetBaseMetaData(assetFileDirectory, uuid);
	newAsset.mAssetStatus = ::doom::asset::Asset::AssetStatus::NotImported;

	auto pair = mAssets.emplace(std::make_pair(uuid, std::move(newAsset)));

	if (pair.second == true)
	{
		D_DEBUG_LOG({ "Asset is completely imported : ", pair.first->second.GetAssetFileName() }, eLogType::D_LOG);
		mAssetsForIterating.push_back(&(pair.first->second));
		std::string assetName = pair.first->second.GetAssetFileName();
		mAssetsForAssetName.emplace(std::make_pair(assetName, &(pair.first->second)));
		return &(pair.first->second);
	}
	else
	{
		D_DEBUG_LOG("UUID is already inserted", logger::eLogType::D_ERROR);
		return nullptr;
	}
}

