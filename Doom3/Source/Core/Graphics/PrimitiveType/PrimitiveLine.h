#pragma once
#include <Vector3.h>

namespace dooms
{
	namespace graphics
	{
		struct PrimitiveLine
		{
			math::Vector3 startPoint;
			math::Vector3 endPoint;

			PrimitiveLine(const math::Vector3& sPoint, const math::Vector3& ePoint)
				: startPoint{ sPoint }, endPoint{ ePoint }
			{

			}
		};
	}
}

