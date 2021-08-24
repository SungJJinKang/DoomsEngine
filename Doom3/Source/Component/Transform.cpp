#include "Transform.h"

#include <sstream>
#include "../Core/Math/LightMath_Cpp/Matrix_utility.h"

#include "Graphics/Graphics_Server.h"


void doom::Transform::InitComponent()
{
	
	SetPosition(mPosition);
	SetRotation(mRotation);
	SetScale(mScale);
}

void doom::Transform::UpdateComponent()
{

}

void doom::Transform::OnEndOfFrame_Component()
{
	mLastFramePosition = mPosition;
}

void doom::Transform::OnDestroy()
{
	
}

std::string doom::Transform::ToString()
{
	std::stringstream sStream;
	sStream << "Position : ";
	sStream << mPosition.toString();
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

void doom::Transform::SetPosition(float x, float y, float z)
{
	SetPosition({ x, y, z });
}


void doom::Transform::SetPosition(const math::Vector3& position)
{
	mTranslationMatrix = math::translate(position);
	mPosition = position;

	SetDirtyTrueAtThisFrame();
	bmIsDirtyModelMatrix = true;
}



void doom::Transform::SetRotation(const math::Quaternion& rotation)
{
	mRotationMatrix = static_cast<math::Matrix4x4>(rotation);
	mRotation = rotation;
	SetDirtyTrueAtThisFrame();

	bmIsDirtyModelMatrix = true;
}

void doom::Transform::SetScale(const math::Vector3& scale)
{
	mScaleMatrix = math::scale(scale);
	mScale = scale;
	SetDirtyTrueAtThisFrame();
	bmIsDirtyModelMatrix = true;
}

void doom::Transform::SetScale(const float x, const float y, const float z)
{
	SetScale({ x,y,z });
}

void doom::Transform::SetRotation(const float eulerAngleX, const float eulerAngleY, const float eulerAngleZ)
{
	SetRotation({ eulerAngleX, eulerAngleY, eulerAngleZ });
}

void doom::Transform::SetRotation(const math::Vector3& eulerAngle)
{
	SetRotation(math::Quaternion(eulerAngle));
}

const math::Matrix4x4& doom::Transform::GetModelMatrix()
{
	if (bmIsDirtyModelMatrix.GetIsDirty(true))
	{
		mModelMatrixCache = mTranslationMatrix * mRotationMatrix * mScaleMatrix;
	}
	return mModelMatrixCache;
}

