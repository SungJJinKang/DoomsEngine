#pragma once

#include "../Core.h"
#include <Utility.h>
#include <Vector2.h>
#include <Vector3.h>
#include "IRenderPhysics.h"
#include "Ray.h"

namespace doom
{
	namespace physics
	{
		

		/// <summary>
		/// reference : https://box2d.org/files/ErinCatto_DynamicBVH_GDC2019.pdf
		/// </summary>
		class AABB3D : public IRenderPhysics
		{
		public:
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

			math::Vector3 GetHalfExtent();

			virtual void _DebugRender() final;

		};

		/// <summary>
		/// ºÎÇÇ
		/// </summary>
		/// <param name="A"></param>
		/// <returns></returns>
		float GetArea(const AABB3D& A);
		AABB3D Union(const AABB3D& A, const AABB3D& B);

		bool IsOverlap(const AABB3D& aabb, const math::Vector3& Point);
		bool IsOverlap(const AABB3D& aabb, const AABB3D& B);

		math::Vector3 ClosestPointToPoint(const AABB3D& aabb, const math::Vector3& point);



		class AABB2D : public IRenderPhysics
		{
		public:
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

			math::Vector2 GetHalfExtent();

			virtual void _DebugRender() final;
		};

		
		float GetArea(const AABB2D& A);

		AABB2D Union(const AABB2D& A, const AABB2D& B);

		bool IsOverlap(const AABB2D& aabb, const math::Vector2& Point);
		bool IsOverlap(const AABB2D& aabb, const AABB2D& B);
		math::Vector2 ClosestPointToPoint(const AABB2D& aabb, const math::Vector2& point);
	
	}
}

