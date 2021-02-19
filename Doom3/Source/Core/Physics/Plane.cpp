#include "Plane.h"

doom::physics::Plane::Plane(float distance, const math::Vector3& normal)
	:mDistance(distance), mNormal(normal)
{
	D_ASSERT(normal.sqrMagnitude() == 1.0); // valid check
}

doom::physics::Plane::Plane(const math::Vector3& A, const math::Vector3& B, const math::Vector3& C)
{
	this->mNormal = math::cross(A - C, B - C).normalized();
	this->mDistance = math::dot(this->mNormal, A);
}

float doom::physics::Plane::GetDistance()
{
	return this->mDistance;
}

math::Vector3 doom::physics::Plane::GetNormal()
{
	return this->mNormal;
}

bool doom::physics::Plane::IsPointOnPlane(const math::Vector3& point)
{
	return math::dot(this->mNormal, point) - this->mDistance < math::epsilon<float>();
}

bool doom::physics::Plane::IsPointOnPositiveSide(const math::Vector3& point)
{
	return math::dot(this->mNormal, point) - this->mDistance > 0.0f;
}
