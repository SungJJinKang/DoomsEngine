#pragma once

#include "../Core.h"
#include <Vector3.h>
#include "Collider.h"
namespace doom
{
	namespace physics
	{
		class Ray : public Collider
		{
		private:
			math::Vector3 mNormal;

		public:

			virtual void DrawCollider(eColor color, bool drawInstantly = false) override;
					
			math::Vector3 mOrigin;

			Ray();
			Ray(const math::Vector3 & origin, const math::Vector3& normal);

			FORCE_INLINE virtual void* data() final
			{
				return &(mOrigin);
			}

			FORCE_INLINE virtual const void* data() const final
			{
				return &(mOrigin);
			}

			math::Vector3 GetNormal() const;
			void SetNomral(const math::Vector3& normal);
			/// <summary>
			/// This don't check whether vector is normal vector
			/// </summary>
			/// <param name="normal"></param>
			void SetNomral_Unsafe(const math::Vector3& normal);
				
			bool IsPointOnRay(const math::Vector3& point);
			static math::Vector3 GetClosestPoint(const Ray& ray, const math::Vector3& point);

			/// <summary>
			/// https://gamedev.stackexchange.com/questions/67719/how-do-raymarch-shaders-work
			/// </summary>
			/// <param name="ray"></param>
			/// <param name="maxDistance"></param>
			/// <returns></returns>
			static float RayMarching(const Ray& ray, float maxDistance);
			static bool RayTracing(const Ray& ray);

			ColliderType GetColliderType() const override;

		};

	}
}