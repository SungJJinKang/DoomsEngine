#pragma once

#include <string>
#include <filesystem>

#include <Core.h>
#include <UUID.h>

namespace dooms
{
	struct D_STRUCT AssetMetaData
	{
		//stem of path
		D_PROPERTY()
		std::string mFileName;
		
		D_PROPERTY()
		UINT64 mFileSize; // in byte
		
		D_PROPERTY()
		std::filesystem::path mFileDirectory;
		
		D_PROPERTY()
		D_UUID mUUID;
	};
}