#include "Path.h"

#include <filesystem>
#include <Windows.h>

#include "OS.h"

#define ASSET_FOLDER_RELATIVE_DIRECTORY "\\Assets\\"

static std::string CURRENT_DIRECTORY{};
static std::string ASSET_FOLDER_DIRECTORY{};

std::string dooms::path::_GetCurrentPath()
{
	if (CURRENT_DIRECTORY.empty() == true)
	{
		CURRENT_DIRECTORY = dooms::os::_GetCurrentExecutableDirectory();
	}

	return CURRENT_DIRECTORY;
}
std::string dooms::path::_GetAssetFolderDirectory()
{
	if (ASSET_FOLDER_DIRECTORY.empty() == true)
	{
		ASSET_FOLDER_DIRECTORY = _GetCurrentPath() + ASSET_FOLDER_RELATIVE_DIRECTORY;
	}

	return ASSET_FOLDER_DIRECTORY;
}
std::string dooms::path::_GetCurrentPath(const char* additional)
{
	return (_GetCurrentPath() + '\\' + additional);
}

std::string dooms::path::_GetCurrentPath(const std::string& additional)
{
	return _GetCurrentPath(additional.c_str());
}

