#include "Transform.h"

#include <sstream>

#include <Scene/Entity.h>

void dooms::Transform::SetPosition()
{
	SetPosition(mTransformCoreData.mPosition);
}

void dooms::Transform::SetRotation()
{
	SetRotation(mRotation);
}

void dooms::Transform::SetScale()
{
	SetScale(mScale);
}

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

void dooms::Transform::OnChangedByGUI(const dooms::reflection::DField& dFieldOfChangedField)
{
	Base::OnChangedByGUI(dFieldOfChangedField);

}


bool dooms::Transform::IsEntityMobilityStatic() const
{
	return GetOwnerEntity()->GetEntityMobility() != Entity::eEntityMobility::Static;
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
	sStream << mTransformCoreData.mPosition[0];
	sStream << ' ';
	sStream << mTransformCoreData.mPosition[1];
	sStream << ' ';
	sStream << mTransformCoreData.mPosition[2];
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
	sStream << mScale[0];
	sStream << ' ';
	sStream << mScale[1];
	sStream << ' ';
	sStream << mScale[2];
	sStream << '\n';
	return sStream.str();
}


