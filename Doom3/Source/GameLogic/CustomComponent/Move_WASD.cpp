#include "Move_WASD.h"
#include "../IO/UserInput_Server.h"
#include <Transform.h>
#include <Vector3.h>
#include "Vector2.h"


void doom::Move_WASD::InitComponent()
{
	
}

void doom::Move_WASD::UpdateComponent()
{
	math::Vector3 translation{};
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

	auto delta = Time_Server::GetDeltaTime();
	if (isMove == true)
	{
		translation.Normalize();

		
		this->GetTransform()->Translate(translation * delta, doom::eSpace::Self);
	}
	

	/////////

	math::Vector3 vec3{ UserInput_Server::GetDeltaMouseScreenPositionY(), UserInput_Server::GetDeltaMouseScreenPositionX(), 0.0f };
	
	this->GetTransform()->Rotate(vec3.normalized() * delta, eSpace::Self);
}

void doom::Move_WASD::OnEndOfFrame_Component()
{

}

void doom::Move_WASD::OnDestroy()
{

}

void doom::Move_WASD::OnActivated()
{

}

void doom::Move_WASD::OnDeActivated()
{

}
