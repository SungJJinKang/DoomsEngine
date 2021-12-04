#pragma once

#include <Doom_Core.h>

#include "ButtonRotate.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS ButtonRotate : public Component
	{
		GENERATE_BODY()

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
