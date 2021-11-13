#pragma once

#include <Doom_Core.h>

#include "TestComponent.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS TestComponent : public PlainComponent
	{
		GENERATE_BODY()
		
		

	private:

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
