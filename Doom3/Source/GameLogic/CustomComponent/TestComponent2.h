#pragma once

#include <Doom_Core.h>
#include "TestComponent.h"

#include "TestComponent2.reflection.h"
namespace dooms
{
	class D_CLASS TestComponent2 : public TestComponent
	{
		GENERATE_BODY()
		
		

	private:

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
