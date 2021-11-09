#include "AutoRotate.h"

void dooms::AutoRotate::InitComponent()
{

}

void dooms::AutoRotate::UpdateComponent()
{
	GetTransform()->Rotate({0,  MainTimer::GetSingleton()->GetDeltaTime(), 0 }, eSpace::World);

	
	//D_DEBUG_DRAW_3D_LINE(GetTransform()->GetPosition(), GetTransform()->GetPosition() + GetTransform()->forward() * 5, eColor::Red);
}

void dooms::AutoRotate::OnEndOfFrame_Component()
{

}
