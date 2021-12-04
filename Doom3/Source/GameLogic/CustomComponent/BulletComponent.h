#pragma once

#include <Doom_Core.h>

#include "BulletComponent.reflection.h"
namespace dooms
{


	class DOOM_API D_CLASS BulletComponent : public Component
	{
		GENERATE_BODY()
		
		

	public:

		FLOAT32 mSpeed = 5;
		void InitComponent() override;
		void UpdateComponent() override;
	};
}

