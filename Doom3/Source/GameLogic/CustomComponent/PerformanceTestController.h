#pragma once

#include <Doom_Core.h>

namespace doom
{
	class PerformanceTestController : public PlainComponent
	{

		DOBJECT_CLASS_BODY(PerformanceTestController)

	private:

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
