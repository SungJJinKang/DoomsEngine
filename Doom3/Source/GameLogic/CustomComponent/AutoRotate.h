#pragma once

#include <Doom_Core.h>

namespace dooms
{
	class AutoRotate : public PlainComponent
	{
		DOBJECT_CLASS_BODY(AutoRotate)
		DOBJECT_CLASS_BASE_CHAIN(PlainComponent)

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
