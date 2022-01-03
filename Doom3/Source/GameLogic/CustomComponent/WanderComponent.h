#pragma once

#include <Doom_Core.h>

#include "WanderComponent.reflection.h"
namespace dooms
{
	class D_CLASS WanderComponent : public Component
	{
		GENERATE_BODY()



	private:

		D_PROPERTY(INVISIBLE)
		bool mDestinationToggle;

	protected:

		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	public:

		D_PROPERTY()
		bool mLookAtDestination;

		D_PROPERTY()
		float mSpeed = 1.0f;

		D_PROPERTY()
		math::Vector3 mPoint1{nullptr};

		D_PROPERTY()
		math::Vector3 mPoint2{nullptr};
		
		D_PROPERTY()
		math::Vector3 mRotationEulerOffset{ nullptr };
	};

}

