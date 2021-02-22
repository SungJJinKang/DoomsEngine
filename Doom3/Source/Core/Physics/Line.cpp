#include "Line.h"
#include "../Graphics/DebugGraphics.h"

void doom::physics::Line::_DebugRender()
{
	graphics::DebugGraphics::GetSingleton()->DebugDraw3DLine(this->mStartPoint, this->mEndPoint, eColor::White);
}

doom::physics::Line::Line(const math::Vector3& startPos, const math::Vector3& endPos)
	: mStartPoint{ startPos }, mEndPoint{ endPos }
{

}

math::Vector3 doom::physics::Line::ToVector()
{
	return this->mEndPoint - this->mStartPoint;
}

bool doom::physics::Line::IsPointOnLine(const Line& line, math::Vector3& point)
{
	float m = (line.mEndPoint.y - line.mStartPoint.y) / (line.mEndPoint.x - line.mStartPoint.x);
	float d = line.mEndPoint.y - m * line.mEndPoint.x;

	if (math::abs(m * point.x + d - point.y < math::epsilon<float>()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

math::Vector3 doom::physics::Line::GetClosestPoint(const Line& line, math::Vector3& point)
{
	auto lineVec = line.mEndPoint - line.mStartPoint;
	auto lineNormal = lineVec.normalized();
	auto vecToPoint = point - line.mStartPoint;
	float t = math::dot(lineVec, vecToPoint) / lineVec.magnitude();
	if (t <= 0)
	{
		return line.mStartPoint;
	}
	else if(t * t >= lineVec.sqrMagnitude())
	{
		return line.mEndPoint;
	}
	else
	{
		return line.mStartPoint + lineNormal * t;
	}
}
