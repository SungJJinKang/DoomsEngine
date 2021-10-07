#include "AutoRotate.h"

void doom::AutoRotate::InitComponent()
{

}

void doom::AutoRotate::UpdateComponent()
{
	GetTransform()->Rotate({0,  MainTimer::GetDeltaTime(), 0 }, eSpace::World);

	
	//D_DEBUG_DRAW_3D_LINE(GetTransform()->GetPosition(), GetTransform()->GetPosition() + GetTransform()->forward() * 5, eColor::Red);
}

void doom::AutoRotate::OnEndOfFrame_Component()
{

}
