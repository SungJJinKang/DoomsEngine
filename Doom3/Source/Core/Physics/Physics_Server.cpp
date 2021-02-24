#include "Physics_Server.h"

#include "PhysicsComponent/Collider.h"
#include <Iterator/ComponentStaticIterater.h>

void doom::physics::Physics_Server::Init()
{

}

void doom::physics::Physics_Server::Update()
{
	this->UpdateColliders();
	this->mPicking.UpdatePicking();
}

void doom::physics::Physics_Server::UpdateColliders()

{
	auto componentPair = doom::ComponentStaticIterater<Collider>::GetAllComponents();
	for (unsigned int i = 0; i < componentPair.second; i++)
	{
		componentPair.first[i]->UpdateComponent();
	}
}

void doom::physics::Physics_Server::OnEndOfFrame()
{

}

