#include "Base_Asset.h"

using namespace doom;

void Asset::SetBaseMetaData(const std::filesystem::path& path)
{
	mAssetName = path.has_filename() ? path.filename().string() : "";
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

