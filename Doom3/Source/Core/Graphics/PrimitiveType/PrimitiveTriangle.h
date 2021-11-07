#pragma once
#include <Vector3.h>

namespace dooms
{
	namespace graphics
	{
		struct PrimitiveTriangle
		{
			math::Vector3 PointA;
			math::Vector3 PointB;
			math::Vector3 PointC;

			PrimitiveTriangle(const math::Vector3& A, const math::Vector3& B, const math::Vector3& C)
				: PointA{ A }, PointB{ B }, PointC{ C }
			{

			}
		};
	}
}

