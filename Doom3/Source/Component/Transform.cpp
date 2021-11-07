#include "Transform.h"

#include <sstream>

#include <Scene/Entity.h>

void dooms::Transform::InitComponent()
{
	
	SetPosition(mTransformCoreData.mPosition);
	SetRotation(mRotation);
	SetScale(mScale);
}

void dooms::Transform::UpdateComponent()
{

}

void dooms::Transform::OnEndOfFrame_Component()
{
	mLastFramePosition = mTransformCoreData.mPosition;
}

void dooms::Transform::OnDestroy()
{
	
}


bool dooms::Transform::IsEntityMobilityStatic() const
{
	return GetOwnerEntity()->mEntityMobility != Entity::eEntityMobility::Static;
}

dooms::Transform::Transform(): mLastFramePosition{ 0.0f }, mTransformCoreData()
{
	// 			SetPosition(mPosition);
	// 			SetRotation(mRotation);
	// 			SetScale(mScale);
}

std::string dooms::Transform::ToString()
{
	std::stringstream sStream;
	sStream << "Position : ";
	sStream << mTransformCoreData.mPosition.toString();
	sStream << '\n';
	sStream << "Rotation : ";
	auto rotEuler = math::Quaternion::QuaternionToEulerAngle(mRotation);
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


