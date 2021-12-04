#pragma once

#include <Doom_Core.h>

#include "AxisDebugger.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS AxisDebugger : public Component
	{
		GENERATE_BODY()
		
		

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;
	};
}
