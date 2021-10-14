#include "Sphere.h"
#include <Graphics/DebugGraphics/DebugDrawer.h>

#include "AABB.h"

void doom::physics::Sphere::DrawCollider(eColor color, bool drawInstantly /*= false*/) const
{

#ifdef DEBUG_DRAWER
	auto debugGraphics = graphics::DebugDrawer::GetSingleton();

	const FLOAT32 intervalRadian = math::PI * 2 / 72.0f;


	FLOAT32 deltaTheta = math::PI / 12;
	FLOAT32 deltaPhi = 2 * math::PI / 10;

	

	math::Vector3 exVertex{ };
	math::Vector3 currentVertex{};
	
	FLOAT32 theta{ 0 };
	for (INT32 ring = 0 ; ring < 11; ring++) { //move to a new z - offset 
		FLOAT32 phi{ 0 };

		theta += deltaTheta;
		for (INT32 point = 0 ; point < 11; point++) { // draw a ring
			phi += deltaPhi;
			currentVertex.x = sin(theta) * cos(phi) * mRadius;
			currentVertex.y = sin(theta) * sin(phi) * mRadius;
			currentVertex.z = cos(theta) * mRadius;
			currentVertex += mCenter;

			if (point != 0)
			{
				debugGraphics->DebugDraw3DLine(exVertex, currentVertex, color, drawInstantly);
			}
			exVertex = currentVertex;
		}
	}

	theta = 0;
	for (INT32 ring = 0; ring < 11; ring++) { //move to a new z - offset 
		FLOAT32 phi{ 0 };

		theta += deltaTheta;
		for (INT32 point = 0; point < 11; point++) { // draw a ring
			phi += deltaPhi;
			currentVertex.z = sin(theta) * cos(phi) * mRadius;
			currentVertex.y = sin(theta) * sin(phi) * mRadius;
			currentVertex.x = cos(theta) * mRadius;
			currentVertex += mCenter;

			if (point != 0)
			{
				debugGraphics->DebugDraw3DLine(exVertex, currentVertex, color, drawInstantly);
			}
			exVertex = currentVertex;
		}
	}
#endif

}



doom::physics::ColliderType doom::physics::Sphere::GetColliderType() const
{
	return doom::physics::ColliderType::Sphere;
}

