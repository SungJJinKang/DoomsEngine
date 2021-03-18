#pragma once


#include "../Core.h"
#include <Vector3.h>
#include <Matrix4x4.h>
#include "Collider.h"
namespace doom
{
	namespace physics
	{
		class AABB3D;

		class Sphere : public Collider
		{

		public:
			using component_type = typename math::Vector3;

		private:

			// Inherited via RenderPhysics
			virtual void Render(eColor color, bool drawInstantly = false);

		public:
			Sphere();
			Sphere(const math::Vector3& center, float radius);
			Sphere(const AABB3D& aabb3D);
			
			math::Vector3 mCenter;
			float mRadius;

			constexpr void Expand(const math::Vector3& movedVector)
			{
				this->mRadius += movedVector.magnitude();
			}

			constexpr void SignedExpand(const math::Vector3& movedVector)
			{
				float distance = movedVector.magnitude();

				this->mCenter += movedVector * 0.5f;
				this->mRadius += distance * 0.5f;
			}

			ColliderType GetColliderType() const override;

			static constexpr float GetArea(const Sphere& A)
			{
				return A.mRadius;
			}
			/// <summary>
			/// https://stackoverflow.com/questions/33532860/merge-two-spheres-to-get-a-new-one
			/// </summary>
			/// <param name="A"></param>
			/// <param name="B"></param>
			/// <returns></returns>
			static Sphere Union(const Sphere& A, const Sphere& B)
			{
				math::Vector3 v = A.mCenter - B.mCenter;
				float distanceWithCenters = v.magnitude();
				if (distanceWithCenters + A.mRadius < B.mRadius)
				{
					return B;
				}
				else if (distanceWithCenters + B.mRadius < A.mRadius)
				{
					return A;
				}

				float newRadius = (A.mRadius + B.mRadius + distanceWithCenters) * 0.5f;
				math::Vector3 newCenter = math::lerp(A.mCenter, B.mCenter, (newRadius - A.mRadius) / distanceWithCenters);
				return Sphere(newCenter, newRadius);
			}
			static constexpr float GetUnionArea(const Sphere& A, const Sphere& B)
			{
				math::Vector3 v = A.mCenter - B.mCenter;
				float distanceWithCenters = v.magnitude();
				if (distanceWithCenters + A.mRadius < B.mRadius)
				{
					return B.mRadius;
				}
				else if (distanceWithCenters + B.mRadius < A.mRadius)
				{
					return A.mRadius;
				}

				return (A.mRadius + B.mRadius + distanceWithCenters) * 0.5f;
			}
			static Sphere EnlargeAABB(const Sphere& sphere);

			static void ApplyModelMatrix(const Sphere& localSphere, const math::Matrix4x4& modelMatrix, Sphere& resultSphere);
			/// <summary>
			/// This is different with IsOverlap
			/// This function check if innerAABB is completly enclosed by outerAABB
			/// </summary>
			/// <param name="innerAABB"></param>
			/// <param name="outerAABB"></param>
			/// <returns></returns>
			static bool CheckIsCompletlyEnclosed(const Sphere& innerSphere, const Sphere& outerSphere);
		};

		bool IsOverlapSphereAndSphere(const Sphere& sphere1, const Sphere& sphere2);
		bool IsOverlapSphereAndSphere(Collider* sphere1, Collider* sphere2);
	}
}

