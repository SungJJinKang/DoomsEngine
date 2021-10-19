#pragma once

#include <Doom_Core.h>

namespace doom
{
	class ButtonRotate : public PlainComponent
	{

		DOBJECT_CLASS_BODY(ButtonRotate)

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
