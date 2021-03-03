#include "Base_Asset.h"

using namespace doom;

void Asset::SetBaseMetaData(const std::filesystem::path& path)
{
	this->mAssetFileName = path.has_filename() ? path.filename().string() : "";
	this->mAssetPath = path;
	this->mAssetFileSize = std::filesystem::file_size(path);
}

Asset::Asset() : mUUID{ GenerateUUID() }, bmIsDataLoaded{ true }
{

}

Asset::Asset(bool isConatiningData) : bmIsDataLoaded{ isConatiningData }
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

doom::D_UUID Asset::GetUUID()
{
	return this->mUUID;
}

doom::D_UUID Asset::GetUUID() const
{
	return this->mUUID;
}

std::string Asset::GetAssetFileName()
{
	return this->mAssetFileName;
}

const std::string& Asset::GetAssetFileName() const
{
	return this->mAssetFileName;
}

std::filesystem::path Asset::GetAssetPath()
{
	return this->mAssetPath;
}



bool Asset::GetIsDataLoaded()
{
	return this->bmIsDataLoaded;
}

unsigned long long Asset::GetAssetFileSize() const
{
	return this->mAssetFileSize;
}

