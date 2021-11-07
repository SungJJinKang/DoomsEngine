#include "Asset.h"


void dooms::asset::Asset::SetBaseMetaData(const std::filesystem::path& path, const D_UUID& uuid)
{
	mAssetMetaData.mFileName = path.has_filename() ? path.filename().string() : "";
	mAssetMetaData.mFileDirectory = path;
	mAssetMetaData.mFileSize = std::filesystem::file_size(path);
	mAssetMetaData.mUUID = uuid;
}



dooms::asset::Asset::Asset() = default;

dooms::asset::Asset::Asset(Asset&&) noexcept = default;
dooms::asset::Asset& dooms::asset::Asset::operator=(Asset&&) noexcept = default;
dooms::asset::Asset::~Asset() = default;


dooms::D_UUID dooms::asset::Asset::GetUUID() const
{
	return mAssetMetaData.mUUID;
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

void dooms::asset::Asset::OnEndImportInMainThread()
{
	if (IsCalledEndImportInMainThread == false)
	{
		OnEndImportInMainThread_Internal();
		IsCalledEndImportInMainThread = true;
	}
}

