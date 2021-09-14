#pragma once

#include <cstdio>
#include <type_traits>
#include <string>

namespace doom
{
	namespace ui
	{
		template<typename... Types>
		extern void PrintText(const char* const format, Types... args)
		{
			static_assert((!std::is_same_v<std::string, Types> && ...));
			printf(format, args...);
			printf("\n");
		}

	}
}


