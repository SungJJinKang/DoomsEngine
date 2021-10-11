#pragma once

#include <CompilerFlags.h>


#include <string>

namespace doom
{
	namespace path
	{
		std::string _GetCurrentPath();
		std::string _GetAssetFolderDirectory();
		std::string _GetCurrentPath(const char* additional);
	}
}


