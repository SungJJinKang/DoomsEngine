#include "Asset.h"


void dooms::asset::Asset::SetBaseMetaData(const std::filesystem::path& path, const D_UUID& uuid)
{
	mAssetMetaData.mFileName = path.has_filename() ? path.filename().generic_u8string() : "";
	mAssetMetaData.mFileDirectory = path;
	mAssetMetaData.mFileSize = std::filesystem::file_size(path);
	mAssetMetaData.mUUID = uuid;
}



dooms::asset::Asset::Asset()
{
}

dooms::asset::Asset::Asset(Asset&&) noexcept = default;
dooms::asset::Asset& dooms::asset::Asset::operator=(Asset&&) noexcept = default;
dooms::asset::Asset::~Asset() = default;

void dooms::asset::Asset::OnSetPendingKill()
{
	DObject::OnSetPendingKill();

}


dooms::D_UUID dooms::asset::Asset::GetUUID() const
{
	return mAssetMetaData.mUUID;
}

std::string dooms::asset::Asset::GetAssetExtension() const
{
	const std::string sourceExtention = GetAssetPath().extension().generic_u8string();
	return sourceExtention;
}

std::string dooms::asset::Asset::GetAssetFileName()
{
	return mAssetMetaData.mFileName;
}

const std::string& dooms::asset::Asset::GetAssetFileName() const
{
	return mAssetMetaData.mFileName;
}

const std::filesystem::path& dooms::asset::Asset::GetAssetPath() const
{
	return mAssetMetaData.mFileDirectory;
}

dooms::asset::Asset::AssetStatus dooms::asset::Asset::GetAssetStatus()
{
	return mAssetStatus;
}

void dooms::asset::Asset::SetAssetStatus(const AssetStatus assetStatus)
{
	mAssetStatus = assetStatus;
}

UINT64 dooms::asset::Asset::GetAssetFileSize() const
{
	return mAssetMetaData.mFileSize;
}

std::string dooms::asset::Asset::GetAssetPathAsStr() const
{
	return GetAssetPath().generic_string();
}

std::string dooms::asset::Asset::GetAssetPathAsUTF8Str() const
{
	return GetAssetPath().generic_u8string();
}

std::wstring dooms::asset::Asset::GetAssetPathAsWideStr() const
{
	return GetAssetPath().generic_wstring();
}

void dooms::asset::Asset::OnEndImportInMainThread()
{
	if (IsCalledEndImportInMainThread == false)
	{
		OnEndImportInMainThread_Internal();
		IsCalledEndImportInMainThread = true;
	}
}

