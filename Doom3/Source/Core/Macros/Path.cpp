#include "Path.h"

#include <filesystem>

#define ASSET_FOLDER_RELATIVE_DIRECTORY "/Assets/"

static std::string CURRENT_DIRECTORY{};
static std::string ASSET_FOLDER_DIRECTORY{};

std::string doom::path::_GetCurrentPath()
{
	if (CURRENT_DIRECTORY.empty() == true)
	{
		CURRENT_DIRECTORY = std::filesystem::current_path().string();
		CURRENT_DIRECTORY.reserve(CURRENT_DIRECTORY.capacity() + 1);
	}

	return CURRENT_DIRECTORY;
}
std::string doom::path::_GetAssetFolderDirectory()
{
	if (ASSET_FOLDER_DIRECTORY.empty() == true)
	{
		ASSET_FOLDER_DIRECTORY = _GetCurrentPath() + ASSET_FOLDER_RELATIVE_DIRECTORY;
	}

	return ASSET_FOLDER_DIRECTORY;
}
std::string doom::path::_GetCurrentPath(const char* additional)
{
	return (_GetCurrentPath() + "/" + additional);
}

