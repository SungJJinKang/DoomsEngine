#pragma once

#include "../Core.h"
#include <Vector3.h>
#include "Collider.h"

#include "Plane.reflection.h"
namespace dooms
{
	namespace physics
	{
		class DOOM_API D_CLASS Plane : public Collider
		{
			GENERATE_BODY()

		private:
			
			math::Vector3 mNormal;

		public:

			virtual void DrawCollider(eColor color, bool drawInstantly = false) const;

			/// <summary>
			/// can be negative value
			/// </summary>
			FLOAT32 mDistance;

			FORCE_INLINE virtual void* data() final
			{
				return &(mNormal);
			}

			FORCE_INLINE virtual const void* data() const final
			{
				return &(mNormal);
			}

			Plane(FLOAT32 distance, const math::Vector3& normal);
			Plane(const math::Vector3& A, const math::Vector3& B, const math::Vector3& C);

			math::Vector3 GetNormal();
			const math::Vector3& GetNormal() const;

			ColliderType GetColliderType() const override;

		};

		bool IsOverlapPlaneAndPlane(const Plane& plane1, const Plane & plane2);
		bool IsOverlapPlaneAndPlane(const Collider* const plane1, const Collider* const plane2);
		bool IsPointOnPlane(const Plane& plane, const math::Vector3& point);
		/// <summary>
		/// return if point is in front of plane ( is at half space where normal vector forward )
		/// </summary>
		/// <param name="point"></param>
		/// <returns></returns>
		bool IsPointOnPositiveSide(const Plane& plane, const math::Vector3& point);
		/// <summary>
		/// Get Closest Point To Point
		/// </summary>
		/// <param name="point"></param>
		/// <returns></returns>
		math::Vector3 GetClosestPoint(const Plane& plane, const math::Vector3& point);
	}
}

