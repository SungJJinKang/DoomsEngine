#include "Base_Asset.h"

using namespace doom;

void Asset::SetBaseMetaData(const std::filesystem::path& path)
{
	mAssetFileName = path.has_filename() ? path.filename().string() : "";
	mAssetPath = path.string();
}

Asset::Asset() : mUUID{ GenerateUUID() }, bIsContainingData{ true }
{

}

Asset::Asset(bool isConatiningData) : bIsContainingData{ isConatiningData }
{
	if (isConatiningData == true)
	{
		this->mUUID = GenerateUUID();
	}
}

std::string Asset::GetAssetTypeString(const eAssetType& assetType)
{
	switch (assetType)
	{
	case eAssetType::AUDIO:
		return "AUDIO";
		break;

	case eAssetType::FONT:
		return "FONT";
		break;

	case eAssetType::TEXT:
		return "TEXT";
		break;

	case eAssetType::TEXTURE:
		return "TEXTURE";
		break;

	case eAssetType::THREE_D_MODEL:
		return "THREE_D_MODEL";
		break;

	case eAssetType::SHADER:
		return "SHADER";
		break;

	default:
		return "";
	}
	return "";
}

