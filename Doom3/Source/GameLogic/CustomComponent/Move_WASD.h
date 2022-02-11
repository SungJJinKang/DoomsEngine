#pragma once

#include <DoomsGameLogicCore.h>

#include "Move_WASD.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS Move_WASD : public Component
	{
		GENERATE_BODY()

		D_PROPERTY()
		FLOAT32 mMoveSpeed = 2.0f;

		D_PROPERTY()
		FLOAT32 mRotationSpeed = 2.0f;

	protected:

		void InitComponent() override;
		void UpdateComponent() override;
		void OnEndOfFrame_Component() override;
		void OnDestroy() override;
		void OnActivated() override;
		void OnDeActivated() override;
		
	};
}


