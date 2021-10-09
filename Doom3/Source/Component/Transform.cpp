#include "Transform.h"

#include <sstream>

#include <Scene/Entity.h>

void doom::Transform::InitComponent()
{
	
	SetPosition(mTransformCoreData.mPosition);
	SetRotation(mTransformCoreData.mRotation);
	SetScale(mScale);
}

void doom::Transform::UpdateComponent()
{

}

void doom::Transform::OnEndOfFrame_Component()
{
	mLastFramePosition = mTransformCoreData.mPosition;
}

void doom::Transform::OnDestroy()
{
	
}

bool doom::Transform::IsEntityMobilityStatic() const
{
	return GetOwnerEntity()->mEntityMobility != Entity::eEntityMobility::Static;
}

std::string doom::Transform::ToString()
{
	std::stringstream sStream;
	sStream << "Position : ";
	sStream << mTransformCoreData.mPosition.toString();
	sStream << '\n';
	sStream << "Rotation : ";
	auto rotEuler = math::Quaternion::QuaternionToEulerAngle(mTransformCoreData.mRotation);
	sStream << math::RADIAN_TO_DEGREE * rotEuler.x;
	sStream << ' ';
	sStream << math::RADIAN_TO_DEGREE * rotEuler.y;
	sStream << ' ';
	sStream << math::RADIAN_TO_DEGREE * rotEuler.z;
	sStream << ' ';
	sStream << '\n';
	sStream << "Scale : ";
	sStream << mScale.toString();
	sStream << '\n';
	return sStream.str();
}


