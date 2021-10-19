#pragma once

#include "PlainComponent.h"
#include "ServerComponent.h"

namespace doom
{
	template<typename T>
	FORCE_INLINE constexpr extern bool IsServerComponentStatic()
	{
		return std::is_base_of_v<ServerComponent, T>;
	}

	template<typename T>
	FORCE_INLINE constexpr extern bool IsPlainComponentStatic()
	{
		return std::is_base_of_v<PlainComponent, T>;
	}

	FORCE_INLINE extern bool IsServerComponent(const Component* const component)
	{
		D_ASSERT(IsValid(component));
		return component->IsChildOf<ServerComponent>();
	}

	FORCE_INLINE extern bool IsPlainComponent(const Component* const component)
	{
		D_ASSERT(IsValid(component));
		return component->IsChildOf<PlainComponent>();
	}
}
