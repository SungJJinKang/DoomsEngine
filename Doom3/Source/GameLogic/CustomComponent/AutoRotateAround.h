#pragma once

#include <DoomsGameLogicCore.h>

#include "AutoRotateAround.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS AutoRotateAround : public Component
	{
		GENERATE_BODY()
		

	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	public:

		D_PROPERTY()
		math::Vector3 mCenterPos{nullptr};
		D_PROPERTY()
		math::Vector3 mRotateAxis{ nullptr };
		D_PROPERTY()
		FLOAT32 mRotateAngle;

	};


}

