#pragma once

#include <magic_enum.hpp>

namespace doom
{
	namespace physics
	{
		enum class ColliderType : unsigned int
		{
			AABB2D = 1,
			AABB3D = 1 < 1,
			Circle2D = 1 < 2,
			CapsuleCollider = 1 < 3,
			Line = 1 < 4,
			Plane = 1 < 5,
			Ray = 1 < 6,
			Sphere = 1 < 7,
			Triangle = 1 < 8
		};

		inline constexpr unsigned int TWO_D_COLLIDER_TYPE{ static_cast<unsigned int>(ColliderType::AABB2D) | static_cast<unsigned int>(ColliderType::Circle2D) };
		inline constexpr unsigned int THREE_D_COLLIDER_TYPE{ 
			static_cast<unsigned int>(ColliderType::AABB3D) | static_cast<unsigned int>(ColliderType::CapsuleCollider) | 
			static_cast<unsigned int>(ColliderType::Line) | static_cast<unsigned int>(ColliderType::Plane) | 
			static_cast<unsigned int>(ColliderType::Ray) | static_cast<unsigned int>(ColliderType::Sphere) | 
			static_cast<unsigned int>(ColliderType::Triangle)
		};

		inline constexpr unsigned int COLLIDER_TYPE_COUNT{ static_cast<unsigned int>(magic_enum::enum_count<ColliderType>()) };
	}
}