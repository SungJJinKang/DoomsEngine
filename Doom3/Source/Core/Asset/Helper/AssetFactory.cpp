#include "AssetFactory.h"

#include "../AssetHeaders.h"

doom::asset::Asset* doom::asset::AssetFactory::CreateNewAsset(const doom::asset::eAssetType eAssetType)
{
	doom::asset::Asset* newAsset = nullptr;

	switch (eAssetType)
	{

	case eAssetType::AUDIO:
		newAsset = new doom::asset::AudioAsset();
		break;

	case eAssetType::FONT:
		newAsset = new doom::asset::FontAsset();
		break;

	case eAssetType::TEXT:
		newAsset = new doom::asset::TextAsset();
		break;

	case eAssetType::TEXTURE:
		newAsset = new doom::asset::TextureAsset();
		break;

	case eAssetType::THREE_D_MODEL:
		newAsset = new doom::asset::ThreeDModelAsset();
		break;

	case eAssetType::SHADER:
		newAsset = new doom::asset::ShaderAsset();
		break;

	default: 
		NEVER_HAPPEN;
	}

	D_ASSERT(newAsset != nullptr);

	return newAsset;
}

doom::asset::Asset* doom::asset::AssetFactory::CreateNewAsset
(
	const std::filesystem::path& path,
	const doom::asset::eAssetType eAssetType
)
{

	::doom::asset::Asset* newAsset = doom::asset::AssetFactory::CreateNewAsset(eAssetType);

	D_UUID uuid = doom::GenerateUUID();
	newAsset->SetBaseMetaData(path, uuid);
	newAsset->SetAssetStatus(::doom::asset::Asset::AssetStatus::NotImported);

	return newAsset;



}

