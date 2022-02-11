#include "Ray.h"
#include <Graphics/RenderingDebugger/RenderingDebuggerModules/DebugDrawer.h>
dooms::physics::Ray::Ray()
	: mOrigin{ nullptr }, mNormal{0, 0, -1}
{
}
dooms::physics::Ray::Ray(const math::Vector3 & origin, const math::Vector3& normal)
	: mOrigin{ origin }, mNormal{ normal.normalized() }
{

}

void dooms::physics::Ray::DrawCollider(eColor color, bool drawInstantly /*= false*/) const
{
#ifdef DEBUG_DRAWER
	graphics::DebugDrawer::GetSingleton()->DebugDraw3DLine(mOrigin, mOrigin + mNormal * 100000000.0f, color);
#endif
}

math::Vector3 dooms::physics::Ray::GetNormal() const
{
	return mNormal;
}

void dooms::physics::Ray::SetNomral(const math::Vector3& normal)
{
	mNormal = normal.normalized();
}

void dooms::physics::Ray::SetNomral_Unsafe(const math::Vector3& normal)
{
	mNormal = normal;
}

bool dooms::physics::Ray::IsPointOnRay(const math::Vector3& point)
{
	return math::dot((point - mOrigin).normalized(), mNormal) < math::epsilon_FLOAT32();
}

math::Vector3 dooms::physics::Ray::GetClosestPoint(const Ray& ray, const math::Vector3& point)
{
	auto vecToPoint = point - ray.mOrigin;
	FLOAT32 t = math::dot(ray.mNormal, vecToPoint);
	if (t <= 0)
	{
		return ray.mOrigin;
	}
	else
	{
		return ray.mOrigin + ray.mNormal * t;
	}
}

dooms::physics::ColliderType dooms::physics::Ray::GetColliderType() const
{
	return dooms::physics::ColliderType::Ray;
}
