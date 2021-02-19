#pragma once

#include "../Core.h"
#include <Utility.h>
#include <Vector2.h>
#include <Vector3.h>
namespace doom
{
	namespace physics
	{
		struct Ray
		{
			math::Vector3 mPosition;
			math::Vector3 mNormal;
		};

		/// <summary>
		/// reference : https://box2d.org/files/ErinCatto_DynamicBVH_GDC2019.pdf
		/// </summary>
		struct AABB3D 
		{
			math::Vector3 mLowerBound; // minimum extent
			math::Vector3 mUpperBound; // maximum extent

			AABB3D(const math::Vector3& lowerBound, const math::Vector3& upperBound)
				:mLowerBound(lowerBound), mUpperBound(upperBound)
			{
#ifdef DEBUG_MODE
				this->Validate();
#endif
			}

			bool IsValid();
			void Validate();

			void Render();
		};

		struct AABB2D 
		{
			math::Vector2 mLowerBound; // minimum extent
			math::Vector2 mUpperBound; // maximum extent

			AABB2D(const math::Vector2& lowerBound, const math::Vector2& upperBound)
				:mLowerBound(lowerBound), mUpperBound(upperBound)
			{
#ifdef DEBUG_MODE
				this->Validate();
#endif
			}

			bool IsValid();
			void Validate();

			void Render();
		};

		AABB2D Union(const AABB2D& A, const AABB2D& B);
		AABB3D Union(const AABB3D& A, const AABB3D& B);

		/// <summary>
		/// ºÎÇÇ
		/// </summary>
		/// <param name="A"></param>
		/// <returns></returns>
		float Area(const AABB3D& A);
		float Area(const AABB2D& A);

		bool IsOverlap(const AABB2D& A, const math::Vector2& Point);
		bool IsOverlap(const AABB2D& A, const AABB2D& B);
		bool IsOverlap(const AABB3D& A, const math::Vector3& Point);
		bool IsOverlap(const AABB3D& A, const AABB3D& B);

		math::Vector2 ClosestPointToPoint(const AABB2D& A, const math::Vector2& point);
		math::Vector3 ClosestPointToPoint(const AABB3D& A, const math::Vector3& point);

		float Raycast(Ray ray, AABB3D aabb);
	}
}

