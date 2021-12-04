#pragma once

#include <Doom_Core.h>

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

		math::Vector3 mCenterPos{nullptr};
		math::Vector3 mRotateAxis{ nullptr };
		FLOAT32 mRotateAngle;

	};


}

