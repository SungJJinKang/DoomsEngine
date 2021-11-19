#pragma once

#include <string>
#include <unordered_map>

#include <Core.h>

namespace dooms
{
	namespace reflection
	{
		using TO_STRING_FUNC = std::string(*)(const void* const);

		extern void InitReflectionToString();
		extern std::string GetStringFromReflectionData(const UINT32 typeHashValue, const void* const object);
	}
}