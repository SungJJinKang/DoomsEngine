#include "FireBulletComponent.h"

#include "BulletComponent.h"

void doom::FireBulletComponent::InitComponent()
{
	PlainComponent::InitComponent();
}

void doom::FireBulletComponent::UpdateComponent()
{
	PlainComponent::UpdateComponent();

	if(mBullet != nullptr && doom::userinput::UserInput_Server::GetMouseButtonRelease(eMouse_Button_Type::MOUST_BUTTON_LEFT))
	{
		mBullet->GetTransform()->SetPosition(GetTransform()->GetPosition());
		mBullet->GetTransform()->SetRotation(GetTransform()->GetRotation());
	}
}
