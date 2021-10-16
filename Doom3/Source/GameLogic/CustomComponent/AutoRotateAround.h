#pragma once

#include <Doom_Core.h>

namespace doom
{
	class AutoRotateAround : public PlainComponent
	{
		DOBJECT_BODY(AutoRotateAround)
	protected:
		void InitComponent() override;


		void UpdateComponent() override;


		void OnEndOfFrame_Component() override;

	public:

		math::Vector3 mCenterPos;
		math::Vector3 mRotateAxis;
		FLOAT32 mRotateAngle;

	};


}

