#pragma once
namespace doom
{
	namespace physics
	{
		enum class ColliderType
		{
			AABB2D,
			AABB3D,
			Circle2D,
			CapsuleCollider,
			Line,
			Plane,
			Ray,
			Sphere,
			Triangle
		};
		inline constexpr int COLLIDER_TYPE_COUNT{ 9 };
	}
}