#pragma once

#include <Doom_Core.h>

namespace dooms
{
	class D_CLASS AutoRotateAround : public PlainComponent
	{
		DOBJECT_CLASS_BODY(AutoRotateAround)
		DOBJECT_CLASS_BASE_CHAIN(PlainComponent)

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

