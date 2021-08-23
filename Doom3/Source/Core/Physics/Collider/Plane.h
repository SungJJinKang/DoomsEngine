#pragma once

#include "../Core.h"
#include <Vector3.h>
#include "Collider.h"
namespace doom
{
	namespace physics
	{
		class Plane : public Collider
		{
		private:
			math::Vector3 mNormal;

		protected:
			virtual void Render(eColor color, bool drawInstantly = false);

		public:
			/// <summary>
			/// can be negative value
			/// </summary>
			float mDistance;

			FORCE_INLINE virtual void* data() final
			{
				return &(mNormal);
			}

			FORCE_INLINE virtual const void* data() const final
			{
				return &(mNormal);
			}

			Plane(float distance, const math::Vector3& normal);
			Plane(const math::Vector3& A, const math::Vector3& B, const math::Vector3& C);

			math::Vector3 GetNormal();
			const math::Vector3& GetNormal() const;

			ColliderType GetColliderType() const override;

		};

		bool IsOverlapPlaneAndPlane(const Plane& plane1, const Plane & plane2);
		bool IsOverlapPlaneAndPlane(Collider* plane1, Collider* plane2);
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

