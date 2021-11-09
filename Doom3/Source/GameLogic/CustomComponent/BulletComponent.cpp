#include "BulletComponent.h"

void dooms::BulletComponent::InitComponent()
{
	PlainComponent::InitComponent();
}

void dooms::BulletComponent::UpdateComponent()
{
	PlainComponent::UpdateComponent();

	GetTransform()->Translate(GetTransform()->forward() * mSpeed * dooms::time::MainTimer::GetSingleton()->GetDeltaTime());
}
