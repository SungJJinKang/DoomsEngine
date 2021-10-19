#pragma once

#include <Doom_Core.h>

namespace doom
{
	class Move_WASD : public PlainComponent
	{

		DOBJECT_CLASS_BODY(Move_WASD)

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;


		void OnDestroy() override;


		void OnActivated() override;


		void OnDeActivated() override;

	};
}


