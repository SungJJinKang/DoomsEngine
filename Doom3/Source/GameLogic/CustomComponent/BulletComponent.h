#pragma once

#include <Doom_Core.h>

namespace doom
{


	class BulletComponent : public PlainComponent
	{

		DOBJECT_CLASS_BODY(BulletComponent)


	public:

		FLOAT32 mSpeed = 5;
		void InitComponent() override;
		void UpdateComponent() override;
	};
}

