#include "Move_WASD.h"
#include "../IO/UserInput_Server.h"
#include <Transform.h>
#include <Vector3.h>
#include "Vector2.h"


void dooms::Move_WASD::InitComponent()
{
	//dooms::userinput::UserInput_Server::SetIsCursorLockedInScreen(true);
}

void dooms::Move_WASD::UpdateComponent()
{
	math::Vector3 translation{0.0f, 0.0f, 0.0f};
	bool isMove{ false };
	if (UserInput_Server::GetKey(eKEY_CODE::KEY_W))
	{
		translation.z -= 1;
		isMove = true;
	}
	else if (UserInput_Server::GetKey(eKEY_CODE::KEY_S))
	{
		translation.z += 1;
		isMove = true;
	}

	if (UserInput_Server::GetKey(eKEY_CODE::KEY_A))
	{
		translation.x -= 1;
		isMove = true;
	}
	else if (UserInput_Server::GetKey(eKEY_CODE::KEY_D))
	{
		translation.x += 1;
		isMove = true;
	}

	if (UserInput_Server::GetKey(eKEY_CODE::KEY_Q))
	{
		translation.y += 1;
		isMove = true;
	}
	else if (UserInput_Server::GetKey(eKEY_CODE::KEY_E))
	{
		translation.y -= 1;
		isMove = true;
	}

	auto delta = MainTimer::GetSingleton()->GetDeltaTime();
	if (isMove == true)
	{
		translation.Normalize();
		translation *= 100.0f * mSpeed;
		
		GetTransform()->Translate(translation * delta, dooms::eSpace::Self);
	}
	

	/////////

	//math::Vector3 rotation{ UserInput_Server::GetDeltaMouseScreenPositionY(), -UserInput_Server::GetDeltaMouseScreenPositionX(), 0.0f };
	math::Vector3 rotation{ 0.0f, 0.0f, 0.0f };
	
	if (UserInput_Server::GetKey(eKEY_CODE::KEY_UP))
	{
		rotation.x += 1;
	}
	else if (UserInput_Server::GetKey(eKEY_CODE::KEY_DOWN))
	{
		rotation.x -= 1;
	}

	if (UserInput_Server::GetKey(eKEY_CODE::KEY_LEFT))
	{
		rotation.y += 1;
	}
	else if (UserInput_Server::GetKey(eKEY_CODE::KEY_RIGHT))
	{
		rotation.y -= 1;
	}

	GetTransform()->Rotate(rotation.normalized() * delta * 2.0f, eSpace::Self);


}

void dooms::Move_WASD::OnEndOfFrame_Component()
{

}

void dooms::Move_WASD::OnDestroy()
{

}

void dooms::Move_WASD::OnActivated()
{

}

void dooms::Move_WASD::OnDeActivated()
{

}
