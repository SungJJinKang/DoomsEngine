#pragma once

#include <cstdio>
#include <string>

#include <Core.h>

namespace doom
{
	namespace ui
	{
		template<typename... Types>
		extern void PrintText(const char* const format, Types... args)
		{
			static_assert((!std::is_same_v<std::string, Types> && ...), "Don't pass std::string, Please use string::c_str()");
			printf(format, args...);
			printf("\n");
		}

	}
}


