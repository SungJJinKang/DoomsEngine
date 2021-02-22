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
		struct AABB3D : public IRenderPhysics
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

			virtual void _DebugRender() final;

			/// <summary>
			/// ºÎÇÇ
			/// </summary>
			/// <param name="A"></param>
			/// <returns></returns>
			float GetArea(const AABB3D& A);
			static AABB3D Union(const AABB3D& A, const AABB3D& B);

			bool IsOverlap(const math::Vector3& Point);
			bool IsOverlap(const AABB3D& B);

			math::Vector3 ClosestPointToPoint(const math::Vector3& point);

			static float Raycast(Ray ray, AABB3D aabb);
		};

		struct AABB2D : public IRenderPhysics
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

			virtual void _DebugRender() final;

			float GetArea(const AABB2D& A);
			
			static AABB2D Union(const AABB2D& A, const AABB2D& B);

			bool IsOverlap(const math::Vector2& Point);
			bool IsOverlap(const AABB2D& B);

			math::Vector2 ClosestPointToPoint(const math::Vector2& point);

		
		};

		
		
	
	}
}

