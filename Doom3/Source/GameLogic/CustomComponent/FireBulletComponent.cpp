#include "FireBulletComponent.h"

#include "BulletComponent.h"

#include <Random.h>
#include <Reflection/ReflectionType/DClass.h>
#include <Rendering/Light/PointLight.h>

void dooms::FireBulletComponent::InitComponent()
{
	Component::InitComponent();
	

	dooms::reflection::DClass dClass = GetDClass();

	dooms::reflection::DField dField;
	auto dFsield = dClass.GetDField("BullterSpeed", dField);

	auto functionList = dClass.GetDFunctionList();
	//dField.g
}

void dooms::FireBulletComponent::UpdateComponent()
{
	Component::UpdateComponent();
	
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
		
		
	}
}

void dooms::FireBulletComponent::Shoot()
{
	D_ASSERT(IsValid(mBullet) == true);

	for (INT32 i = 0; i < BullterCount ; i++)
	{
		Entity* const newBulletEntity = dooms::Scene::DuplicateEntityStatic(mBullet->GetOwnerEntity());
		D_ASSERT(IsValid(newBulletEntity) == true);

		if(newBulletEntity != nullptr)
		{
			mBullet = newBulletEntity->GetComponent<BulletComponent>();
			mBullet->GetTransform()->SetPosition(GetTransform()->GetPosition());
			mBullet->GetTransform()->SetRotation(GetTransform()->GetRotation());
			mBullet->GetTransform()->Rotate
			(
				math::Vector3
				{
				Random::RandomFloatNumber(-0.5f, 0.5f),
				Random::RandomFloatNumber(-0.5f, 0.5f),
				0.0f
				}
				, eSpace::Self
			);

			mBullet->mSpeed = BullterSpeed;
			
		}
		
	}
}



