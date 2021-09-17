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
	mNormal = math::cross(A - C, B - C).normalized();
	mDistance = math::dot(mNormal, A);
}

math::Vector3 doom::physics::Plane::GetNormal()
{
	return mNormal;
}

const math::Vector3& doom::physics::Plane::GetNormal() const
{
	return mNormal;
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

void doom::physics::Plane::Render(eColor color, bool drawInstantly /*= false*/)
{
#ifdef DEBUG_MODE
	auto debugGraphics = graphics::DebugGraphics::GetSingleton();

	math::Vector3 arbitaryVector =
		math::abs(mNormal.y) > math::epsilon<float>() || math::abs(mNormal.z) > math::epsilon<float>() ?
		math::Vector3::right : math::Vector3::up;
	
	math::Vector3 Parallel1VectorToPlane = math::cross(mNormal, arbitaryVector);
	math::Vector3 Parallel2VectorToPlane = math::cross(mNormal, Parallel1VectorToPlane);

	float halfExtent = 10;
	math::Vector3 center = mNormal * mDistance;


	math::Vector3 a = center + Parallel1VectorToPlane * halfExtent + Parallel2VectorToPlane * halfExtent;
	math::Vector3 b = center - Parallel1VectorToPlane * halfExtent + Parallel2VectorToPlane * halfExtent;
	math::Vector3 c = center - Parallel1VectorToPlane * halfExtent - Parallel2VectorToPlane * halfExtent;
	math::Vector3 d = center + Parallel1VectorToPlane * halfExtent - Parallel2VectorToPlane * halfExtent;
	
	debugGraphics->DebugDraw3DTriangle(a, b, c, color, drawInstantly);
	debugGraphics->DebugDraw3DTriangle(c, d, a, color, drawInstantly);

// 	debugGraphics->DebugDraw3DLine(a, b, color);
// 	debugGraphics->DebugDraw3DLine(b, c, color);
// 	debugGraphics->DebugDraw3DLine(c, d, color);
// 	debugGraphics->DebugDraw3DLine(d, a, color);


	/*
	math::lookat
	math::Quaternion quat{ mNormal };
	auto center = mNormal * mDistance;
	
	graphics::DebugGraphics::GetSingleton()->DebugDraw3DTriangle(center - center.right - center.up, eColor::White);
	*/
#endif

}
