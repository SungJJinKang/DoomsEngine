#include "Plane.h"
#include <Rendering/RenderingDebugger/RenderingDebuggerModules/DebugDrawer.h>
#include <Quaternion.h>
#include <Utility.h>


dooms::physics::Plane::Plane(FLOAT32 distance, const math::Vector3& normal)
	:mDistance{ distance }, mNormal{ normal.normalized() }
{
}

dooms::physics::Plane::Plane(const math::Vector3& A, const math::Vector3& B, const math::Vector3& C)
	:mNormal(nullptr)
{
	mNormal = math::cross(A - C, B - C).normalized();
	mDistance = math::dot(mNormal, A);
}

math::Vector3 dooms::physics::Plane::GetNormal()
{
	return mNormal;
}

const math::Vector3& dooms::physics::Plane::GetNormal() const
{
	return mNormal;
}

dooms::physics::ColliderType dooms::physics::Plane::GetColliderType() const
{
	return dooms::physics::ColliderType::Plane;
}

bool dooms::physics::IsOverlapPlaneAndPlane(const Plane& plane1, const Plane& plane2)
{
	auto cross = math::cross(plane1.GetNormal(), plane2.GetNormal());

	if (math::dot(cross, cross) < math::epsilon_FLOAT32())
	{
		//if parallel
		return false;
	}
	else
	{
		return true;
	}
}

bool dooms::physics::IsOverlapPlaneAndPlane(const Collider* const plane1, const Collider* const plane2)
{
	return IsOverlapPlaneAndPlane(*static_cast<const Plane*>(plane1), *static_cast<const Plane*>(plane2));
}

bool dooms::physics::IsPointOnPlane(const dooms::physics::Plane& plane, const math::Vector3& point)
{
	return math::dot(plane.GetNormal(), point) - plane.mDistance < math::epsilon_FLOAT32();
}

bool dooms::physics::IsPointOnPositiveSide(const dooms::physics::Plane& plane, const math::Vector3& point)
{
	return math::dot(plane.GetNormal(), point) - plane.mDistance > 0.0f;
}

math::Vector3 dooms::physics::GetClosestPoint(const dooms::physics::Plane& plane, const math::Vector3& point)
{
	return point - (math::dot(plane.GetNormal(), point) - plane.mDistance) * plane.GetNormal();
}

void dooms::physics::Plane::DrawCollider(eColor color, bool drawInstantly /*= false*/) const
{
#ifdef DEBUG_DRAWER
	auto debugGraphics = graphics::DebugDrawer::GetSingleton();

	math::Vector3 arbitaryVector =
		std::abs(mNormal.y) > math::epsilon_FLOAT32() || std::abs(mNormal.z) > math::epsilon_FLOAT32() ?
		math::Vector3::right : math::Vector3::up;
	
	math::Vector3 Parallel1VectorToPlane = math::cross(mNormal, arbitaryVector);
	math::Vector3 Parallel2VectorToPlane = math::cross(mNormal, Parallel1VectorToPlane);

	FLOAT32 halfExtent = 10;
	math::Vector3 center = mNormal * mDistance;


	math::Vector3 a = center + Parallel1VectorToPlane * halfExtent + Parallel2VectorToPlane * halfExtent;
	math::Vector3 b = center - Parallel1VectorToPlane * halfExtent + Parallel2VectorToPlane * halfExtent;
	math::Vector3 c = center - Parallel1VectorToPlane * halfExtent - Parallel2VectorToPlane * halfExtent;
	math::Vector3 d = center + Parallel1VectorToPlane * halfExtent - Parallel2VectorToPlane * halfExtent;
	
	debugGraphics->DebugDraw3DTriangle(a, b, c, color);
	debugGraphics->DebugDraw3DTriangle(c, d, a, color);

// 	debugGraphics->DebugDraw3DLine(a, b, color);
// 	debugGraphics->DebugDraw3DLine(b, c, color);
// 	debugGraphics->DebugDraw3DLine(c, d, color);
// 	debugGraphics->DebugDraw3DLine(d, a, color);


	/*
	math::lookat
	math::Quaternion quat{ mNormal };
	auto center = mNormal * mDistance;
	
	graphics::DebugDrawer::GetSingleton()->DebugDraw3DTriangle(center - center.right - center.up, eColor::White);
	*/
#endif

}
