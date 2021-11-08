#pragma once

#include <Core.h>

namespace dooms
{
	namespace physics
	{
		enum class D_ENUM ColliderType : UINT32
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
		inline constexpr UINT32 TWO_D_COLLIDER_TYPE{ static_cast<UINT32>(ColliderType::AABB2D) | static_cast<UINT32>(ColliderType::Circle2D) };
		inline constexpr UINT32 THREE_D_COLLIDER_TYPE{ 
			static_cast<UINT32>(ColliderType::AABB3D) | static_cast<UINT32>(ColliderType::CapsuleCollider) | 
			static_cast<UINT32>(ColliderType::Line) | static_cast<UINT32>(ColliderType::Plane) | 
			static_cast<UINT32>(ColliderType::Ray) | static_cast<UINT32>(ColliderType::Sphere) | 
			static_cast<UINT32>(ColliderType::TwoDTriangle)
		};
		*/

		inline constexpr extern size_t COLLIDER_TYPE_COUNT = 9;
	}
}