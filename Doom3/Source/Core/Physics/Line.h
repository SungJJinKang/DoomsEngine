#pragma once
#include <Vector3.h>
namespace doom
{
	namespace physics
	{
		class Line
		{
		public:
			math::Vector3 mStartPoint;
			math::Vector3 mEndPoint;

			Line(const math::Vector3& startPos, const math::Vector3& endPos);

			math::Vector3 ToVector();

			static bool IsPointOnLine(const Line& line, math::Vector3& point);
			static math::Vector3 GetClosestPoint(const Line& line, math::Vector3& point);
		};

		
	}
}

