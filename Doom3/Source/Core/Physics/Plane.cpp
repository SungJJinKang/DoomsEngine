#include "Plane.h"
#include "Graphics/DebugGraphics.h"
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

bool doom::physics::IsOverlap(const Plane& plane1, const Plane& plane2)
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
	//auto up = math::cross()
	//auto center = this->mNormal * this->mDistance;
	
	//graphics::DebugGraphics::GetSingleton()->DebugDraw3DTriangle(center - center.right - center.up, eColor::White);
}
