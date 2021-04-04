#include "Transform.h"

#include <sstream>
#include "../Core/Math/LightMath_Cpp/Matrix_utility.h"

#include "Graphics/Graphics_Server.h"


void doom::Transform::InitComponent()
{
	
	this->SetPosition(this->mPosition);
	this->SetRotation(this->mRotation);
	this->SetScale(this->mScale);
}

void doom::Transform::UpdateComponent()
{

}

void doom::Transform::OnEndOfFrame_Component()
{
	this->mLastFramePosition = this->mPosition;
}

void doom::Transform::OnDestroy()
{
	
}

std::string doom::Transform::ToString()
{
	std::stringstream sStream;
	sStream << "Position : ";
	sStream << this->mPosition.toString();
	sStream << '\n';
	sStream << "Rotation : ";
	auto rotEuler = math::Quaternion::QuaternionToEulerAngle(this->mRotation);
	sStream << math::RADIAN_TO_DEGREE * rotEuler.x;
	sStream << ' ';
	sStream << math::RADIAN_TO_DEGREE * rotEuler.y;
	sStream << ' ';
	sStream << math::RADIAN_TO_DEGREE * rotEuler.z;
	sStream << ' ';
	sStream << '\n';
	sStream << "Scale : ";
	sStream << this->mScale.toString();
	sStream << '\n';
	return sStream.str();
}
