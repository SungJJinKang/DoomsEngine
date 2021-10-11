#include "Base_Asset.h"

using namespace doom;
using namespace doom::asset;

void Asset::SetBaseMetaData(const std::filesystem::path& path, const D_UUID& uuid)
{
	mAssetMetaData.mFileName = path.has_filename() ? path.filename().string() : "";
	mAssetMetaData.mFileDirectory = path;
	mAssetMetaData.mFileSize = std::filesystem::file_size(path);
	mAssetMetaData.mUUID = uuid;
}



Asset::Asset() = default;

Asset::Asset(Asset&&) noexcept = default;
Asset& Asset::operator=(Asset&&) noexcept = default;
doom::asset::Asset::~Asset() = default;

doom::D_UUID Asset::GetUUID()
{
	return mAssetMetaData.mUUID;
}

const D_UUID& Asset::GetUUID() const
{
	return mAssetMetaData.mUUID;
}

std::string Asset::GetAssetFileName()
{
	return mAssetMetaData.mFileName;
}

const std::string& Asset::GetAssetFileName() const
{
	return mAssetMetaData.mFileName;
}

const std::filesystem::path& Asset::GetAssetPath() const
{
	return mAssetMetaData.mFileDirectory;
}

Asset::AssetStatus Asset::GetAssetStatus()
{
	return mAssetStatus;
}

unsigned long long Asset::GetAssetFileSize() const
{
	return mAssetMetaData.mFileSize;
}

void Asset::OnEndImportInMainThread()
{
	if (IsCalledEndImportInMainThread == false)
	{
		OnEndImportInMainThread_Internal();
		IsCalledEndImportInMainThread = true;
	}
}

