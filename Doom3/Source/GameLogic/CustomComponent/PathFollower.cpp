#include "PathFollower.h"

void dooms::PathFollower::InitComponent()
{
	Component::InitComponent();

	mPreviousWayPointIndex = 0;
	mTargetWayPointIndex = 1;
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
			mPreviousWayPointIndex = mTargetWayPointIndex - 1;
			if(mTargetWayPointIndex >= WayPoints.size())
			{
				mTargetWayPointIndex = 0;
				mPreviousWayPointIndex = WayPoints.size() - 1;
			}
		}
		else
		{
			GetTransform()->Translate(vecToDest.normalized() * MainTimer::GetSingleton()->GetDeltaTime() * mMoveSpeed);
			auto upVector = math::cross(math::cross(vecToDest.normalized(), math::Vector3::up), vecToDest.normalized());
			const math::Quaternion lookAtQuat = math::Quaternion::quatLookAt(vecToDest.normalized(), upVector);
			GetTransform()->SetRotation
			(
				math::lerp
				(
					GetTransform()->GetRotation(),
					lookAtQuat,
					math::clamp01( (WayPoints[mTargetWayPointIndex] - WayPoints[mPreviousWayPointIndex]).magnitude() / (WayPoints[mTargetWayPointIndex] - GetTransform()->GetPosition()).magnitude())
				)
			);

		}
	}

	
}

void dooms::PathFollower::OnEndOfFrame_Component()
{
	Component::OnEndOfFrame_Component();
}


