#pragma once

#include <unordered_map>
#include <string_view>

namespace dooms
{
	namespace ui
	{
		namespace profilerGUI
		{

			extern void Render();

			extern void AddProfilingData(const char* const profilingTagName, const float time);
		}
	}
}

