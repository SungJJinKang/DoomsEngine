#include "AssetFactory.h"

#include "../AssetHeaders.h"

dooms::asset::Asset* dooms::asset::AssetFactory::CreateNewAsset(const dooms::asset::eAssetType eAssetType)
{
	dooms::asset::Asset* newAsset = nullptr;

	switch (eAssetType)
	{

	case eAssetType::AUDIO:
		newAsset = dooms::CreateDObject<dooms::asset::AudioAsset>();
		break;

	case eAssetType::FONT:
		newAsset = dooms::CreateDObject<dooms::asset::FontAsset>();
		break;

	case eAssetType::TEXT:
		newAsset = dooms::CreateDObject<dooms::asset::TextAsset>();
		break;

	case eAssetType::TEXTURE:
		newAsset = dooms::CreateDObject<dooms::asset::TextureAsset>();
		break;

	case eAssetType::THREE_D_MODEL:
		newAsset = dooms::CreateDObject<dooms::asset::ThreeDModelAsset>();
		break;

	case eAssetType::SHADER:
		newAsset = dooms::CreateDObject<dooms::asset::ShaderAsset>();
		break;

	default: 
		NEVER_HAPPEN;
	}

	D_ASSERT(newAsset != nullptr);

	return newAsset;
}

dooms::asset::Asset* dooms::asset::AssetFactory::CreateNewAsset
(
	const std::filesystem::path& path,
	const dooms::asset::eAssetType eAssetType
)
{

	::dooms::asset::Asset* newAsset = dooms::asset::AssetFactory::CreateNewAsset(eAssetType);

	D_UUID uuid = dooms::GenerateUUID();
	newAsset->SetBaseMetaData(path, uuid);
	newAsset->SetAssetStatus(::dooms::asset::Asset::AssetStatus::NotImported);

	return newAsset;



}

