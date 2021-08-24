#pragma once
#include <Vector3.h>

namespace doom
{
	namespace graphics
	{
		struct Triangle
		{
			math::Vector3 PointA;
			math::Vector3 PointB;
			math::Vector3 PointC;

			Triangle(const math::Vector3& A, const math::Vector3& B, const math::Vector3& C)
				: PointA{ A }, PointB{ B }, PointC{ C }
			{

			}
		};
	}
}

