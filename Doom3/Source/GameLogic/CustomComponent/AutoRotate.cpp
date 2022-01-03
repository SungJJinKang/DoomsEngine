#include "AutoRotate.h"

void dooms::AutoRotate::InitComponent()
{

}

void dooms::AutoRotate::UpdateComponent()
{
	GetTransform()->Rotate({ RotateSpeed.x * MainTimer::GetSingleton()->GetDeltaTime(),  RotateSpeed.y * MainTimer::GetSingleton()->GetDeltaTime(), RotateSpeed.z * MainTimer::GetSingleton()->GetDeltaTime() }, eSpace::World);

	
	//D_DEBUG_DRAW_3D_LINE(GetTransform()->GetPosition(), GetTransform()->GetPosition() + GetTransform()->forward() * 5, eColor::Red);
}

void dooms::AutoRotate::OnEndOfFrame_Component()
{

}

dooms::AutoRotate::AutoRotate()
	:RotateSpeed(nullptr)
{
}
