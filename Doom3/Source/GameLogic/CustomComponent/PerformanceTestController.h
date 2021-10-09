#pragma once

#include <Doom_Core.h>

namespace doom
{
	class PerformanceTestController : public PlainComponent
	{
	private:

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};

}
