#include "Plane.h"
doom::physics::Plane::Plane(float distance, const math::Vector3& normal)
	:mDistance{ distance }, mNormal{ normal.normalized() }
{
}

doom::physics::Plane::Plane(const math::Vector3& A, const math::Vector3& B, const math::Vector3& C)
{
	this->mNormal = math::cross(A - C, B - C).normalized();
	this->mDistance = math::dot(this->mNormal, A);
}

float doom::physics::Plane::GetDistance() const
{
	return this->mDistance;
}

math::Vector3 doom::physics::Plane::GetNormal() const
{
	return this->mNormal;
}

bool doom::physics::Plane::IsPointOnPlane(const doom::physics::Plane& plane, const math::Vector3& point)
{
	return math::dot(plane.GetNormal(), point) - plane.GetDistance() < math::epsilon<float>();
}

bool doom::physics::Plane::IsPointOnPositiveSide(const doom::physics::Plane& plane, const math::Vector3& point)
{
	return math::dot(plane.GetNormal(), point) - plane.GetDistance() > 0.0f;
}

math::Vector3 doom::physics::Plane::GetClosestPoint(const doom::physics::Plane& plane, const math::Vector3& point)
{
	return point - (math::dot(plane.GetNormal(), point) - plane.GetDistance()) * plane.GetNormal();
}
