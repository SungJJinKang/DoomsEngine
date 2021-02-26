#pragma once

#include "../Core.h"
#include <Vector3.h>
#include "RenderPhysics.h"
namespace doom
{
	namespace physics
	{
		class Ray : public RenderPhysics
		{
		private:
			math::Vector3 mNormal;

		protected:
			virtual void Render(eColor color) override;

		public:
			math::Vector3 mOrigin;

			Ray(const math::Vector3 & origin, const math::Vector3& normal);
			math::Vector3 GetNormal() const;
				
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
		};
	}
}