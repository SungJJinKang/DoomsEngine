#include "Base_Asset.h"

using namespace doom;
using namespace doom::asset;

void Asset::SetBaseMetaData(const std::filesystem::path& path, const D_UUID& uuid)
{
	this->mAssetMetaData.mFileName = path.has_filename() ? path.filename().string() : "";
	this->mAssetMetaData.mFileDirectory = path;
	this->mAssetMetaData.mFileSize = std::filesystem::file_size(path);
	this->mAssetMetaData.mUUID = uuid;
}



Asset::Asset()
{

}


doom::D_UUID Asset::GetUUID()
{
	return this->mAssetMetaData.mUUID;
}

const D_UUID& Asset::GetUUID() const
{
	return this->mAssetMetaData.mUUID;
}

std::string Asset::GetAssetFileName()
{
	return this->mAssetMetaData.mFileName;
}

const std::string& Asset::GetAssetFileName() const
{
	return this->mAssetMetaData.mFileName;
}

std::filesystem::path Asset::GetAssetPath()
{
	return this->mAssetMetaData.mFileDirectory;
}

const std::filesystem::path& Asset::GetAssetPath() const
{
	return this->mAssetMetaData.mFileDirectory;
}

Asset::AssetStatus Asset::GetAssetStatus()
{
	return this->mAssetStatus;
}

unsigned long long Asset::GetAssetFileSize() const
{
	return this->mAssetMetaData.mFileSize;
}

void Asset::OnEndImportInMainThread()
{
	if (this->IsCalledEndImportInMainThread == false)
	{
		this->OnEndImportInMainThread_Internal();
		this->IsCalledEndImportInMainThread = true;
	}
}

