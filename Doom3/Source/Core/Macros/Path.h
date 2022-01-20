#pragma once

#include <CompilerMacros.h>


#include <string>

namespace dooms
{
	namespace path
	{
		/// <summary>
		/// this function return current exe directory not ending with "/"
		/// </summary>
		/// <returns></returns>
		std::string _GetCurrentPath();
		std::wstring _GetCurrentPathUnicode();
		std::string _GetAssetFolderDirectory();
		std::string _GetCurrentPath(const char* additional);
		std::wstring _GetCurrentPathUnicode(const wchar_t* additional);
		std::string _GetCurrentPath(const std::string& additional);
		std::wstring _GetCurrentPathUnicode(const std::wstring& additional);
	}
}


