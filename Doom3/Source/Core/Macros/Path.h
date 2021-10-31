#pragma once

#include <CompilerMacros.h>


#include <string>

namespace doom
{
	namespace path
	{
		/// <summary>
		/// this function return current exe directory not ending with "/"
		/// </summary>
		/// <returns></returns>
		std::string _GetCurrentPath();
		std::string _GetAssetFolderDirectory();
		std::string _GetCurrentPath(const char* additional);
	}
}


