#include "WanderComponent.h"

#include <Graphics/DebugGraphics/DebugDrawer.h>
#include <Graphics/GraphicsAPI/graphicsAPIHelper.h>

#define ARRIVE_DISTANCE 0.5f

void dooms::WanderComponent::InitComponent()
{
	Component::InitComponent();

}

void dooms::WanderComponent::UpdateComponent()
{
	Component::UpdateComponent();

	const math::Vector3& dest = (mDestinationToggle == true) ? mPoint2 : mPoint1;

	const math::Vector3 vecToDest = dest - GetTransform()->GetPosition();

	if(vecToDest.sqrMagnitude() < ARRIVE_DISTANCE * ARRIVE_DISTANCE)
	{// arrive at destination
		mDestinationToggle = !mDestinationToggle;
	}
	else
	{
		GetTransform()->Translate(vecToDest.normalized() * MainTimer::GetSingleton()->GetDeltaTime() * mSpeed);
		if(mLookAtDestination == true)
		{
			auto upVector = math::cross(vecToDest.normalized(), -math::cross(vecToDest.normalized(), math::Vector3::up));
			const math::Quaternion lookAtQuat = math::Quaternion::quatLookAt(vecToDest.normalized(), upVector);
			GetTransform()->SetRotation(math::Quaternion::EulerAngleToQuaternion(mRotationEulerOffset * math::DEGREE_TO_RADIAN) * lookAtQuat);
		}		
	}
}

void dooms::WanderComponent::OnEndOfFrame_Component()
{
	Component::OnEndOfFrame_Component();

}
