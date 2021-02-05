#include "Transform.h"

#include "../Core/Math/LightMath_Cpp/Matrix_utility.h"

void doom::Transform::SetPosition(const math::Vector3& position)
{
	this->mPosition = position;
}

void doom::Transform::SetRotation(const math::Quaternion& rotation)
{
	this->mRotation = rotation;
}

void doom::Transform::SetScale(const math::Vector3& scale)
{
	this->mScale = scale;
}

math::Vector3 doom::Transform::GetPosition()
{
	return this->mPosition;
}

math::Quaternion doom::Transform::GetRotation()
{
	return this->mRotation;
}

math::Vector3 doom::Transform::GetScale()
{
	return this->mScale;
}

math::Matrix4x4 doom::Transform::GetModelMatrix()
{
	this->mModelMatrixCache = math::Matrix4x4::identify;
	this->mModelMatrixCache = math::translate(this->mModelMatrixCache, this->mPosition);
	this->mModelMatrixCache = this->mModelMatrixCache * static_cast<math::Matrix4x4>(this->mRotation);
	this->mModelMatrixCache = math::scale(this->mModelMatrixCache, this->mScale);
	this->mModelMatrixCache *= this->mLocalToWorldMatrix;
	return this->mModelMatrixCache;
}

math::Matrix4x4 doom::Transform::GetViewMatrix()
{
	return math::lookAt(this->mPosition, this->forward() + this->mPosition, this->up());
}

constexpr math::Vector3 doom::Transform::forward() const
{
	return this->mRotation * math::Vector3::forward;
}

constexpr math::Vector3 doom::Transform::right() const
{
	return this->mRotation * math::Vector3::right;
}

constexpr math::Vector3 doom::Transform::up() const
{
	return this->mRotation * math::Vector3::up;
}

constexpr void doom::Transform::LookAt(const Transform& target, const math::Vector3& up)
{
	this->mRotation = math::lookAt(this->mPosition, target.mPosition, up);
}

constexpr void doom::Transform::Rotate(const math::Vector3& eulerAngles, const eSpace& relativeTo)
{
	this->mRotation *= math::Quaternion(eulerAngles);
}

constexpr void doom::Transform::RotateAround(const math::Vector3& point, const math::Vector3& axis, float angle)
{

}

constexpr math::Vector3 doom::Transform::TransformDirection(const math::Vector3& direction) const
{
	return this->mRotation * direction;
}

constexpr math::Vector3 doom::Transform::TransformPoint(const math::Vector3& point) const
{
	return this->mRotation * point;
}

constexpr math::Vector3 doom::Transform::TransformVector(const math::Vector3& vector) const
{
	return this->mRotation * vector;
}

constexpr void doom::Transform::Translate(const math::Vector3& translation, const eSpace& relativeTo)
{

}
