#pragma once

#include <Doom_Core.h>

namespace doom
{


	class BulletComponent : public PlainComponent
	{

	public:

		float mSpeed = 5;
		void InitComponent() override;
		void UpdateComponent() override;
	};
}

