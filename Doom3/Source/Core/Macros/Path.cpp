#include "Path.h"

#include <filesystem>
#include <Windows.h>

#include "OS.h"

#define ASSET_FOLDER_RELATIVE_DIRECTORY "\\Assets\\"

static std::string CURRENT_DIRECTORY{};
static std::wstring CURRENT_DIRECTORY_UNICODE{};
static std::string ASSET_FOLDER_DIRECTORY{};

std::string dooms::path::_GetCurrentPath()
{
	if (CURRENT_DIRECTORY.empty() == true)
	{
		// if UNICODE macros defined, return utf8 multibyte string
		CURRENT_DIRECTORY = dooms::os::_GetCurrentExecutableDirectory();
	}

	return CURRENT_DIRECTORY;
}

std::wstring dooms::path::_GetCurrentPathUnicode()
{
	if (CURRENT_DIRECTORY_UNICODE.empty() == true)
	{
		// if UNICODE macros defined, return utf8 multibyte string
		CURRENT_DIRECTORY_UNICODE = dooms::os::_GetCurrentExecutableDirectoryUnicode();
	}

	return CURRENT_DIRECTORY_UNICODE;
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

std::wstring dooms::path::_GetCurrentPathUnicode(const wchar_t* additional)
{
	return (_GetCurrentPathUnicode() + L'\\' + additional);
}

std::string dooms::path::_GetCurrentPath(const std::string& additional)
{
	return _GetCurrentPath(additional.c_str());
}

std::wstring dooms::path::_GetCurrentPathUnicode(const std::wstring& additional)
{
	return _GetCurrentPathUnicode(additional.c_str());
}

