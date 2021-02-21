#include "Ray.h"

doom::physics::Ray::Ray(const math::Vector3& pos, const math::Vector3& normal)
	: mPosition{ pos }, mNormal{ normal.normalized() }
{

}

math::Vector3 doom::physics::Ray::GetNormal() const
{
	return this->mNormal;
}

bool doom::physics::Ray::IsPointOnRay(const math::Vector3& point)
{
	return math::dot((point - this->mPosition).normalized(), this->mNormal) < math::epsilon<float>();
}

math::Vector3 doom::physics::Ray::GetClosestPoint(const Ray& ray, const math::Vector3& point)
{
	auto vecToPoint = point - ray.mPosition;
	float t = math::dot(ray.mNormal, vecToPoint);
	if (t <= 0)
	{
		return ray.mPosition;
	}
	else
	{
		return ray.mPosition + ray.mNormal * t;
	}
}
