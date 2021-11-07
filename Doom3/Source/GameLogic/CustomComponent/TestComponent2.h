#pragma once

#include <Doom_Core.h>
#include "TestComponent.h"

namespace dooms
{
	class TestComponent2 : public TestComponent
	{

		DOBJECT_CLASS_BODY(TestComponent2)
		DOBJECT_CLASS_BASE_CHAIN(TestComponent)

	private:

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
