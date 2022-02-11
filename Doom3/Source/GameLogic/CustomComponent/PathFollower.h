#pragma once

#include <DoomsGameLogicCore.h>

#include <vector>

#include "PathFollower.reflection.h"
namespace dooms
{
	class D_CLASS PathFollower : public Component
	{
		GENERATE_BODY()
	private:

		INT32 mPreviousWayPointIndex = 0;

	public:

		D_PROPERTY()
		std::vector<math::Vector3> WayPoints;
		D_PROPERTY()
		INT32 mTargetWayPointIndex = 1;
		D_PROPERTY()
		FLOAT32 mMoveSpeed = 1.0f;


		D_PROPERTY()
		FLOAT32 mRotSpeed = 1.0f;

		void InitComponent() override;
		void UpdateComponent() override;
		void OnEndOfFrame_Component() override;

	};

}
