#pragma once

#include <Doom_Core.h>

#include "AutoRotate.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS AutoRotate : public Component
	{
		GENERATE_BODY()
		

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	public:

		AutoRotate();

		D_PROPERTY()
		math::Vector3 RotateSpeed;
	};

}
