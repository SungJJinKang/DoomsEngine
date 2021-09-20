#pragma once

#include <Doom_Core.h>

namespace doom
{
	class BoxAdder : public PlainComponent
	{
	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	};
}

