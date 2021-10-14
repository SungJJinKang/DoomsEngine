#pragma once

#include <string>
#include <filesystem>
#include "../API/UUID.h"

namespace doom
{
	struct AssetMetaData
	{
		//stem of path
		std::string mFileName;
		UINT64 mFileSize; // in byte
		std::filesystem::path mFileDirectory;
		D_UUID mUUID;
	};
}