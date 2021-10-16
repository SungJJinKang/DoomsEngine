#pragma once

#include <Doom_Core.h>

namespace doom
{
	class TestComponent : public PlainComponent
	{

		DOBJECT_BODY(TestComponent)

	private:

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
