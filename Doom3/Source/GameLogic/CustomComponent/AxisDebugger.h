#pragma once

#include <Doom_Core.h>

namespace doom
{
	class AxisDebugger : public PlainComponent
	{

		DOBJECT_CLASS_BODY(AxisDebugger)
		DOBJECT_CLASS_BASE_CHAIN(PlainComponent)

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;
	};
}
