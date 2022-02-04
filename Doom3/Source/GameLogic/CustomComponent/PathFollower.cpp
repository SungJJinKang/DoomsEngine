#include "PathFollower.h"

void dooms::PathFollower::InitComponent()
{
	Component::InitComponent();

	mTargetWayPointIndex = 0;
}

void dooms::PathFollower::UpdateComponent()
{
	Component::UpdateComponent();

	if(mTargetWayPointIndex < WayPoints.size())
	{
		const math::Vector3& dest = WayPoints[mTargetWayPointIndex];

		const math::Vector3 vecToDest = dest - GetTransform()->GetPosition();

		if (vecToDest.sqrMagnitude() < 1.0f)
		{// arrive at destination
			mTargetWayPointIndex++;
			if(mTargetWayPointIndex >= WayPoints.size())
			{
				mTargetWayPointIndex = 0;
			}
		}
		else
		{
			GetTransform()->Translate(vecToDest.normalized() * MainTimer::GetSingleton()->GetDeltaTime() * mSpeed);
			const math::Quaternion lookAtQuat = math::Quaternion::quatLookAt(vecToDest.normalized(), math::Vector3::up);
			GetTransform()->SetRotation((lookAtQuat - GetTransform()->GetRotation()) * MainTimer::GetSingleton()->GetDeltaTime() * mSpeed);
		}
	}

	
}

void dooms::PathFollower::OnEndOfFrame_Component()
{
	Component::OnEndOfFrame_Component();
}


