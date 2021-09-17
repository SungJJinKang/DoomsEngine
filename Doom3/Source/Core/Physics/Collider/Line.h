#pragma once
#include <Vector3.h>
#include "Ray.h"
namespace doom
{
	namespace physics
	{
		class Line : public Ray
		{
	
		public:

			virtual void Render(eColor color, bool drawInstantly = false) override;
					
			math::Vector3 mEndPoint;

			Line(const math::Vector3& startPos, const math::Vector3& endPos);

			math::Vector3 ToVector();

			

			ColliderType GetColliderType() const override;

		};

		bool IsPointOnLine(const Line& line, math::Vector3& point);
		math::Vector3 GetClosestPoint(const Line& line, math::Vector3& point);

	}
}

