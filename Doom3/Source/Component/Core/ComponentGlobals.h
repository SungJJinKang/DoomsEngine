#pragma once

#include <type_traits>

#include "ServerComponent.h"
#include "PlainComponent.h"

namespace doom
{
	template<typename T>
	constexpr static bool IsServerComponent()
	{
		return std::is_base_of_v<ServerComponent, T>;
	}

	template<typename T>
	constexpr static bool IsPlainComponent()
	{
		return std::is_base_of_v<PlainComponent, T>;
	}
}