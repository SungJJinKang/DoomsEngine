#include "AutoRotate.h"

void dooms::AutoRotate::InitComponent()
{

}

void dooms::AutoRotate::UpdateComponent()
{
	GetTransform()->Rotate({ static_cast<FLOAT32>(RotateSpeed.x * MainTimer::GetSingleton()->GetDeltaTime()), static_cast<FLOAT32>(RotateSpeed.y * MainTimer::GetSingleton()->GetDeltaTime()), static_cast<FLOAT32>(RotateSpeed.z * MainTimer::GetSingleton()->GetDeltaTime()) }, eSpace::World);

	
	//D_DEBUG_DRAW_3D_LINE(GetTransform()->GetPosition(), GetTransform()->GetPosition() + GetTransform()->forward() * 5, eColor::Red);
}

void dooms::AutoRotate::OnEndOfFrame_Component()
{

}

dooms::AutoRotate::AutoRotate()
	:RotateSpeed(nullptr)
{
}
