#include "PhysicsDebugger.h"

#include "Physics_Server.h"
#include "Collider/Ray.h"
#include <PhysicsComponent/ColliderComponent.h>
#include <PhysicsComponent/Rigidbody/Rigidbody.h>
#include <Rendering/Camera.h>
#include <Scene/Entity.h>
#include "PhysicsSolver.h"

void dooms::physics::PhysicsDebugger::DrawMouseRayCast()
{
	dooms::physics::Ray mouseRay = Picking::GetCurrentCursorPointWorldRay();
	mouseRay.DrawPhysicsDebugColor(eColor::Green);
}

void dooms::physics::PhysicsDebugger::DrawPhysicsColliderBoundingBox()
{
	dooms::physics::Ray mouseRay = Picking::GetCurrentCursorPointWorldRay();

	
	const std::vector<ColliderComponent*> colliderComponents = StaticContainer<ColliderComponent>::GetAllStaticComponents();
	for (ColliderComponent* colComponent : colliderComponents)
	{
		dooms::physics::Collider* const col = colComponent->GetWorldCollider();
		col->DrawPhysicsDebugColor(eColor::Blue);
		
	}
	
	const std::vector<Rigidbody*>& rigidbodyComponents = dooms::StaticContainer<Rigidbody>::GetAllStaticComponents();
	for (Rigidbody* const rigidbodyComponent : rigidbodyComponents)
	{
		const std::vector<ColliderComponent*>& attachedColliderComponents = rigidbodyComponent->GetAttachedColliderComponents();
		for (ColliderComponent* const colliderComponent : attachedColliderComponents)
		{
			Collider* const testedCollider = colliderComponent->GetWorldCollider();
			testedCollider->DrawPhysicsDebugColor(eColor::Red);
		}

		const std::vector<dooms::physics::Collider*>& collideColliders = rigidbodyComponent->GetCollideCollidersAtFrame();
		for (dooms::physics::Collider* const collideCollider : collideColliders)
		{
			collideCollider->DrawPhysicsDebugColor(eColor::Red);
		}
	}
}

void dooms::physics::PhysicsDebugger::UpdateDebugger()
{
	DrawMouseRayCast();
	DrawPhysicsColliderBoundingBox();
}
