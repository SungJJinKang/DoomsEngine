#include "FireBulletComponent.h"

#include "BulletComponent.h"

void doom::FireBulletComponent::InitComponent()
{
	PlainComponent::InitComponent();
}

void doom::FireBulletComponent::UpdateComponent()
{
	PlainComponent::UpdateComponent();

	if(
		mBullet != nullptr 
		&&
		(
			doom::userinput::UserInput_Server::GetMouseButtonRelease(eMouse_Button_Type::MOUST_BUTTON_LEFT)
			||
			doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_SPACE) == true
		)
	)
	{
		Entity* const newBulletEntity = doom::Scene::DuplicateEntityStatic(mBullet->GetOwnerEntity());
		mBullet = newBulletEntity->GetComponent<BulletComponent>();
		mBullet->GetTransform()->SetPosition(GetTransform()->GetPosition());
		mBullet->GetTransform()->SetRotation(GetTransform()->GetRotation());
	}
}
