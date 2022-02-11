#include "Line.h"
#include <Rendering/RenderingDebugger/RenderingDebuggerModules/DebugDrawer.h>

void dooms::physics::Line::DrawCollider(eColor color, bool drawInstantly /*= false*/) const
{
#ifdef DEBUG_DRAWER
	graphics::DebugDrawer::GetSingleton()->DebugDraw3DLine(mOrigin, mEndPoint, color);
#endif
}

dooms::physics::Line::Line(const math::Vector3& startPos, const math::Vector3& endPos)
	: Ray(startPos, endPos - startPos), mEndPoint{ endPos }
	//You don't need to pass normalized vector to Ray constructor
{

}

math::Vector3 dooms::physics::Line::ToVector()
{
	return mEndPoint - mOrigin;
}

dooms::physics::ColliderType dooms::physics::Line::GetColliderType() const
{
	return dooms::physics::ColliderType::Line;
}

bool dooms::physics::IsPointOnLine(const Line& line, math::Vector3& point)
{
	FLOAT32 m = (line.mEndPoint.y - line.mOrigin.y) / (line.mEndPoint.x - line.mOrigin.x);
	FLOAT32 d = line.mEndPoint.y - m * line.mEndPoint.x;

	if (std::abs(m * point.x + d - point.y < math::epsilon_FLOAT32()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

math::Vector3 dooms::physics::GetClosestPoint(const Line& line, math::Vector3& point)
{
	auto lineVec = line.mEndPoint - line.mOrigin;
	auto lineNormal = lineVec.normalized();
	auto vecToPoint = point - line.mOrigin;
	FLOAT32 t = math::dot(lineVec, vecToPoint) / lineVec.magnitude();
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
