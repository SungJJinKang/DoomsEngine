#pragma once

#include <Doom_Core.h>

namespace dooms
{
	class TestComponent : public PlainComponent
	{

		DOBJECT_CLASS_BODY(TestComponent)
		DOBJECT_CLASS_BASE_CHAIN(PlainComponent)

	private:

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
