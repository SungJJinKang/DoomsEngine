#pragma once


#include <Doom_Core.h>

#include "FireBulletComponent.reflection.h"
namespace dooms
{
	class BulletComponent;

	class DOOM_API D_CLASS FireBulletComponent : public PlainComponent
	{
		GENERATE_BODY()

		FLOAT32 elpasedTime;

		D_PROPERTY()
		FLOAT32 fireTime = 1.0f;


		D_PROPERTY()
		INT32 BulltetCount = 1;


		D_PROPERTY()
		INT32 Bulltetaaaa = 1;

		D_PROPERTY()
		INT32 Bulltetaaa555a = 1;


		D_PROPERTY()
		INT32 good = 1;

	public:

		BulletComponent* mBullet = nullptr;

		void InitComponent() override;
		void UpdateComponent() override;
	};
}

