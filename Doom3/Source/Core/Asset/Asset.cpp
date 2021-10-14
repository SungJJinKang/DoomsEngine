#include "Asset.h"


void doom::asset::Asset::SetBaseMetaData(const std::filesystem::path& path, const D_UUID& uuid)
{
	mAssetMetaData.mFileName = path.has_filename() ? path.filename().string() : "";
	mAssetMetaData.mFileDirectory = path;
	mAssetMetaData.mFileSize = std::filesystem::file_size(path);
	mAssetMetaData.mUUID = uuid;
}



doom::asset::Asset::Asset() = default;

doom::asset::Asset::Asset(Asset&&) noexcept = default;
doom::asset::Asset& doom::asset::Asset::operator=(Asset&&) noexcept = default;
doom::asset::Asset::~Asset() = default;


doom::D_UUID doom::asset::Asset::GetUUID() const
{
	return mAssetMetaData.mUUID;
}

std::string doom::asset::Asset::GetAssetFileName()
{
	return mAssetMetaData.mFileName;
}

const std::string& doom::asset::Asset::GetAssetFileName() const
{
	return mAssetMetaData.mFileName;
}

const std::filesystem::path& doom::asset::Asset::GetAssetPath() const
{
	return mAssetMetaData.mFileDirectory;
}

doom::asset::Asset::AssetStatus doom::asset::Asset::GetAssetStatus()
{
	return mAssetStatus;
}

void doom::asset::Asset::SetAssetStatus(const AssetStatus assetStatus)
{
	mAssetStatus = assetStatus;
}

UINT64 doom::asset::Asset::GetAssetFileSize() const
{
	return mAssetMetaData.mFileSize;
}

void doom::asset::Asset::OnEndImportInMainThread()
{
	if (IsCalledEndImportInMainThread == false)
	{
		OnEndImportInMainThread_Internal();
		IsCalledEndImportInMainThread = true;
	}
}

