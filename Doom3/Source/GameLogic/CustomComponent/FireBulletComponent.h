#pragma once


#include <Doom_Core.h>

#include "FireBulletComponent.reflection.h"
namespace dooms
{
	class BulletComponent;

	class DOOM_API D_CLASS FireBulletComponent : public PlainComponent
	{
		GENERATE_BODY()

		D_PROPERTY()
		INT32 BullterCount = 1;


		D_PROPERTY(MIN=10, MAX=5, VISIBLE = "true") // -> clcpp return attribute ( IntAttribute. have 10, 5 as value )
		FLOAT32 BullterSpeed = 2.0f;

	public:

		BulletComponent* mBullet = nullptr;

		void InitComponent() override;
		void UpdateComponent() override;

		D_FUNCTION()
		void Shoot();

		D_FUNCTION()
		void Shoot(const int count);

		D_FUNCTION()
		void ShootTenTimes();

		D_FUNCTION()
		void Shoot100Times();
	};
}

