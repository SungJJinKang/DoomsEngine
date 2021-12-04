#include "BulletComponent.h"

void dooms::BulletComponent::InitComponent()
{
	Component::InitComponent();
}

void dooms::BulletComponent::UpdateComponent()
{
	Component::UpdateComponent();

	GetTransform()->Translate(GetTransform()->forward() * mSpeed * dooms::time::MainTimer::GetSingleton()->GetDeltaTime());
}
