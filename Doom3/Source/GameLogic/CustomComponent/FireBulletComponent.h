#pragma once


#include <Doom_Core.h>

namespace doom
{
	class BulletComponent;

	class FireBulletComponent : public PlainComponent
	{

		DOBJECT_BODY(FireBulletComponent)

	public:

		BulletComponent* mBullet = nullptr;

		void InitComponent() override;
		void UpdateComponent() override;
	};
}

