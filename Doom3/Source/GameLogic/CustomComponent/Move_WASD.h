#pragma once

#include <Doom_Core.h>

#include "Move_WASD.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS Move_WASD : public PlainComponent
	{
		GENERATE_BODY()
		
		

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;


		void OnDestroy() override;


		void OnActivated() override;


		void OnDeActivated() override;

	};
}


