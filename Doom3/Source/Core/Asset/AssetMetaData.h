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
		unsigned long long mFileSize; // in byte
		std::filesystem::path mFileDirectory;
		D_UUID mUUID;
	};
}