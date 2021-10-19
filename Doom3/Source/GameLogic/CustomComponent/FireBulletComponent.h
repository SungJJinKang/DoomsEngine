#pragma once


#include <Doom_Core.h>

namespace doom
{
	class BulletComponent;

	class FireBulletComponent : public PlainComponent
	{

		DOBJECT_CLASS_BODY(FireBulletComponent)
		DOBJECT_CLASS_BASE_CHAIN(PlainComponent)

	public:

		BulletComponent* mBullet = nullptr;

		void InitComponent() override;
		void UpdateComponent() override;
	};
}

