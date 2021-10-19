#include "PhysicsDebugger.h"

#include "Physics_Server.h"
#include "Collider/Ray.h"
#include <PhysicsComponent/ColliderComponent.h>
#include <PhysicsComponent/Rigidbody/Rigidbody.h>
#include <Rendering/Camera.h>
#include <Scene/Entity.h>
#include "PhysicsSolver.h"

void doom::physics::PhysicsDebugger::DrawMouseRayCast()
{
	doom::physics::Ray mouseRay = Picking::GetCurrentCursorPointWorldRay();
	mouseRay.DrawPhysicsDebugColor(eColor::Green);
}

void doom::physics::PhysicsDebugger::DrawPhysicsColliderBoundingBox()
{
	doom::physics::Ray mouseRay = Picking::GetCurrentCursorPointWorldRay();

	
	const std::vector<ColliderComponent*> colliderComponents = StaticContainer<ColliderComponent>::GetAllStaticComponents();
	for (ColliderComponent* colComponent : colliderComponents)
	{
		doom::physics::Collider* const col = colComponent->GetWorldCollider();
		col->DrawPhysicsDebugColor(eColor::Blue);
		
	}
	
	const std::vector<Rigidbody*>& rigidbodyComponents = doom::StaticContainer<Rigidbody>::GetAllStaticComponents();
	for (Rigidbody* const rigidbodyComponent : rigidbodyComponents)
	{
		const std::vector<ColliderComponent*>& attachedColliderComponents = rigidbodyComponent->GetAttachedColliderComponents();
		for (ColliderComponent* const colliderComponent : attachedColliderComponents)
		{
			Collider* const testedCollider = colliderComponent->GetWorldCollider();
			testedCollider->DrawPhysicsDebugColor(eColor::Red);
		}

		const std::vector<doom::physics::Collider*>& collideColliders = rigidbodyComponent->GetCollideCollidersAtFrame();
		for (doom::physics::Collider* const collideCollider : collideColliders)
		{
			collideCollider->DrawPhysicsDebugColor(eColor::Red);
		}
	}
}

void doom::physics::PhysicsDebugger::UpdateDebugger()
{
	DrawMouseRayCast();
	DrawPhysicsColliderBoundingBox();
}
