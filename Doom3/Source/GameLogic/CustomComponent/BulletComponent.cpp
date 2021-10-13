#include "BulletComponent.h"

void doom::BulletComponent::InitComponent()
{
	PlainComponent::InitComponent();
}

void doom::BulletComponent::UpdateComponent()
{
	PlainComponent::UpdateComponent();

	GetTransform()->Translate(GetTransform()->forward() * mSpeed * doom::time::MainTimer::GetDeltaTime());
}
