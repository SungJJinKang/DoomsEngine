#include "FireBulletComponent.h"

#include "BulletComponent.h"

void dooms::FireBulletComponent::InitComponent()
{
	PlainComponent::InitComponent();
}

void dooms::FireBulletComponent::UpdateComponent()
{
	PlainComponent::UpdateComponent();

	if(
		mBullet != nullptr 
		&&
		(
			dooms::userinput::UserInput_Server::GetMouseButtonRelease(eMouse_Button_Type::MOUST_BUTTON_LEFT)
			||
			dooms::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_SPACE) == true
		)
	)
	{
		Entity* const newBulletEntity = dooms::Scene::DuplicateEntityStatic(mBullet->GetOwnerEntity());
		mBullet = newBulletEntity->GetComponent<BulletComponent>();
		mBullet->GetTransform()->SetPosition(GetTransform()->GetPosition());
		mBullet->GetTransform()->SetRotation(GetTransform()->GetRotation());
	}
}
