#pragma once
#include <Vector3.h>
namespace doom
{
	namespace physics
	{
		/// <summary>
		/// reference : https://box2d.org/files/ErinCatto_DynamicBVH_GDC2019.pdf
		/// </summary>
		struct AABB
		{
			math::Vector3 mLowerBound;
			math::Vector3 mUpperBound;

			AABB(const math::Vector3& lowerBound, const math::Vector3& upperBound)
				:mLowerBound(lowerBound), mUpperBound(upperBound)
			{

			}
		};

		AABB Union(const AABB& A, const AABB& B)
		{
			return AABB(math::min(A.mLowerBound, B.mLowerBound), math::max(A.mUpperBound, B.mUpperBound));
		}

		/// <summary>
		/// ºÎÇÇ
		/// </summary>
		/// <param name="A"></param>
		/// <returns></returns>
		float Area(const AABB& A)
		{
			math::Vector3 d = A.mUpperBound - A.mLowerBound;
			return 2.0f * (d.x * d.y + d.y * d.z + d.z * d.x);
		}
	}
}

