#include "PhysicsDebugger.h"

#include "Physics_Server.h"
#include "Collider/Ray.h"
#include <PhysicsComponent/ColliderComponent.h>
#include <Rendering/Camera.h>
#include <Scene/Entity.h>

void doom::physics::PhysicsDebugger::DrawMouseRayCast()
{
	doom::physics::Ray mouseRay = Physics_Server::GetSingleton()->mPicking.GetCurrentCursorPointWorldRay();
	mouseRay.DrawPhysicsDebugColor(eColor::Green);
}

void doom::physics::PhysicsDebugger::DrawPhysicsColliderBoundingBox()
{
	doom::physics::Ray mouseRay = Physics_Server::GetSingleton()->mPicking.GetCurrentCursorPointWorldRay();

	
	const std::vector<ColliderComponent*> colliderComponents = StaticContainer<ColliderComponent>::GetAllStaticComponents();
	for (ColliderComponent* col : colliderComponents)
	{
		col->GetWorldCollider()->DrawPhysicsDebugColor(eColor::Blue);
	}
	

	const ColliderComponent* const cameraCollider = Camera::GetMainCamera()->GetOwnerEntity()->GetComponent<ColliderComponent>();
	const doom::BVHAABB3D::node_type* cameraBVHNode = nullptr;
	if (cameraCollider != nullptr)
	{
		cameraBVHNode = cameraCollider->mBVH_Node_View.GetNode();
	}

	size_t stackReservationCount = 0;

	for (auto hitBVHNode : Physics_Server::GetSingleton()->GetCollideBVHNodes(&mouseRay, stackReservationCount))
	{
		if (cameraBVHNode != nullptr && hitBVHNode == cameraBVHNode)
		{
			continue;
		}

		while (hitBVHNode != nullptr && hitBVHNode->GetIsValid() == true)
		{
			hitBVHNode->GetBoundingCollider().DrawPhysicsDebugColor(eColor::Red);
			hitBVHNode = hitBVHNode->GetParentNode();
		}

		if (hitBVHNode != nullptr)
		{
			hitBVHNode->GetCollider()->DrawPhysicsDebugColor(eColor::Red);
		}
	}
}
