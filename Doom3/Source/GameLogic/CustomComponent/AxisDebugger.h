#pragma once

#include <Doom_Core.h>

namespace doom
{
	class AxisDebugger : public PlainComponent
	{

		DOBJECT_BODY(AxisDebugger)

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;
	};
}
