#include "Plane.h"
#include "Graphics/DebugGraphics.h"
#include <Quaternion.h>
#include <Utility.h>


doom::physics::Plane::Plane(float distance, const math::Vector3& normal)
	:mDistance{ distance }, mNormal{ normal.normalized() }
{
}

doom::physics::Plane::Plane(const math::Vector3& A, const math::Vector3& B, const math::Vector3& C)
{
	this->mNormal = math::cross(A - C, B - C).normalized();
	this->mDistance = math::dot(this->mNormal, A);
}


math::Vector3 doom::physics::Plane::GetNormal() const
{
	return this->mNormal;
}

doom::physics::ColliderType doom::physics::Plane::GetColliderType() const
{
	return doom::physics::ColliderType::Plane;
}

bool doom::physics::IsOverlapPlaneAndPlane(const Plane& plane1, const Plane& plane2)
{
	auto cross = math::cross(plane1.GetNormal(), plane2.GetNormal());

	if (math::dot(cross, cross) < math::epsilon<float>())
	{
		//if parallel
		return false;
	}
	else
	{
		return true;
	}
}

bool doom::physics::IsOverlapPlaneAndPlane(Collider* plane1, Collider* plane2)
{
	return IsOverlapPlaneAndPlane(*static_cast<Plane*>(plane1), *static_cast<Plane*>(plane2));
}

bool doom::physics::IsPointOnPlane(const doom::physics::Plane& plane, const math::Vector3& point)
{
	return math::dot(plane.GetNormal(), point) - plane.mDistance < math::epsilon<float>();
}

bool doom::physics::IsPointOnPositiveSide(const doom::physics::Plane& plane, const math::Vector3& point)
{
	return math::dot(plane.GetNormal(), point) - plane.mDistance > 0.0f;
}

math::Vector3 doom::physics::GetClosestPoint(const doom::physics::Plane& plane, const math::Vector3& point)
{
	return point - (math::dot(plane.GetNormal(), point) - plane.mDistance) * plane.GetNormal();
}

void doom::physics::Plane::Render(eColor color)
{
	/*
	math::lookat
	math::Quaternion quat{ this->mNormal };
	auto center = this->mNormal * this->mDistance;
	
	graphics::DebugGraphics::GetSingleton()->DebugDraw3DTriangle(center - center.right - center.up, eColor::White);
	*/
}
