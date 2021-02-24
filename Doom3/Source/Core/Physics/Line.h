#pragma once
#include <Vector3.h>
#include "RenderPhysics.h"
#include "Ray.h"
namespace doom
{
	namespace physics
	{
		class Line : public Ray
		{
		protected:

			virtual void Render(eColor color) override;

		public:
			math::Vector3 mEndPoint;

			Line(const math::Vector3& startPos, const math::Vector3& endPos);

			math::Vector3 ToVector();

			
		};

		bool IsPointOnLine(const Line& line, math::Vector3& point);
		math::Vector3 GetClosestPoint(const Line& line, math::Vector3& point);

	}
}

