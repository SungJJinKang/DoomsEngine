#pragma once
#include <Vector3.h>

namespace doom
{
	namespace graphics
	{
		struct Line
		{
			math::Vector3 startPoint;
			math::Vector3 endPoint;

			Line(const math::Vector3& sPoint, const math::Vector3& ePoint)
				: startPoint{ sPoint }, endPoint{ ePoint }
			{

			}
		};
	}
}

