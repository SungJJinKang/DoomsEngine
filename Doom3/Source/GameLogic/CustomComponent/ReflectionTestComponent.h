#pragma once

#include <Doom_Core.h>

#include "ReflectionTestComponent.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS ReflectionTestComponent : public PlainComponent
	{
		GENERATE_BODY()

		void InitComponent() override
		{
			auto TypeFullName = ReflectionTestComponent::TYPE_FULL_NAME;
			auto TypeShortName = ReflectionTestComponent::TYPE_SHORT_NAME;
			auto TypeHashValue = ReflectionTestComponent::TYPE_FULL_NAME_HASH_VALUE;
		}
	};


}
