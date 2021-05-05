#pragma once

#include <magic_enum.hpp>

namespace doom
{
	namespace physics
	{
		enum class ColliderType : unsigned int
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

		/*
		inline constexpr unsigned int TWO_D_COLLIDER_TYPE{ static_cast<unsigned int>(ColliderType::AABB2D) | static_cast<unsigned int>(ColliderType::Circle2D) };
		inline constexpr unsigned int THREE_D_COLLIDER_TYPE{ 
			static_cast<unsigned int>(ColliderType::AABB3D) | static_cast<unsigned int>(ColliderType::CapsuleCollider) | 
			static_cast<unsigned int>(ColliderType::Line) | static_cast<unsigned int>(ColliderType::Plane) | 
			static_cast<unsigned int>(ColliderType::Ray) | static_cast<unsigned int>(ColliderType::Sphere) | 
			static_cast<unsigned int>(ColliderType::TwoDTriangle)
		};
		*/

		inline constexpr size_t COLLIDER_TYPE_COUNT{ static_cast<size_t>(magic_enum::enum_count<ColliderType>()) };
	}
}