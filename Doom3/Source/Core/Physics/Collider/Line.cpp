#include "Line.h"
#include <Graphics/DebugGraphics/DebugDrawer.h>

void doom::physics::Line::DrawCollider(eColor color, bool drawInstantly /*= false*/) const
{
#ifdef DEBUG_DRAWER
	graphics::DebugDrawer::GetSingleton()->DebugDraw3DLine(mOrigin, mEndPoint, color, drawInstantly);
#endif
}

doom::physics::Line::Line(const math::Vector3& startPos, const math::Vector3& endPos)
	: Ray(startPos, endPos - startPos), mEndPoint{ endPos }
	//You don't need to pass normalized vector to Ray constructor
{

}

math::Vector3 doom::physics::Line::ToVector()
{
	return mEndPoint - mOrigin;
}

doom::physics::ColliderType doom::physics::Line::GetColliderType() const
{
	return doom::physics::ColliderType::Line;
}

bool doom::physics::IsPointOnLine(const Line& line, math::Vector3& point)
{
	float m = (line.mEndPoint.y - line.mOrigin.y) / (line.mEndPoint.x - line.mOrigin.x);
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

math::Vector3 doom::physics::GetClosestPoint(const Line& line, math::Vector3& point)
{
	auto lineVec = line.mEndPoint - line.mOrigin;
	auto lineNormal = lineVec.normalized();
	auto vecToPoint = point - line.mOrigin;
	float t = math::dot(lineVec, vecToPoint) / lineVec.magnitude();
	if (t <= 0)
	{
		return line.mOrigin;
	}
	else if(t * t >= lineVec.sqrMagnitude())
	{
		return line.mEndPoint;
	}
	else
	{
		return line.mOrigin + lineNormal * t;
	}
}
