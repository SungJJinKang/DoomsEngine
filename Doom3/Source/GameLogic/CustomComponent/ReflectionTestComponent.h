#pragma once

#include <DoomsGameLogicCore.h>

#include "ReflectionTestComponent.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS ReflectionTestComponent : public Component
	{
		GENERATE_BODY()

		void InitComponent() override
		{
			auto TypeFullName = ReflectionTestComponent::TYPE_FULL_NAME;
			auto TypeShortName = ReflectionTestComponent::TYPE_SHORT_NAME;
			auto TypeHashValue = ReflectionTestComponent::TYPE_FULL_NAME_HASH_VALUE;
		}

		void UpdateComponent() override;
	};


}
