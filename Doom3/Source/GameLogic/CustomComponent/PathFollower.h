#pragma once

#include <Doom_Core.h>

#include <vector>

#include "PathFollower.reflection.h"
namespace dooms
{
	class D_CLASS PathFollower : public Component
	{
		GENERATE_BODY()
	private:


	public:

		D_PROPERTY()
		std::vector<math::Vector3> WayPoints;
		D_PROPERTY()
		INT32 mTargetWayPointIndex = 0;
		D_PROPERTY()
		FLOAT32 mSpeed = 1.0f;

		void InitComponent() override;
		void UpdateComponent() override;
		void OnEndOfFrame_Component() override;

	};

}
