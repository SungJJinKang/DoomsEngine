#include "DPrimitive.h"

#include <string_view>

const char* dPrimitiveHelper::GetShortNamePointer(const char* const name)
{
	const std::string_view nameStringView = name;
	const size_t lastTypeDivider = nameStringView.find_last_of("::");

	if (lastTypeDivider != std::string::npos)
	{
		return name + lastTypeDivider;
	}
	else
	{
		return name;
	}
}
