#include "AutoRotate.h"

void doom::AutoRotate::InitComponent()
{

}

void doom::AutoRotate::UpdateComponent()
{
	this->GetTransform()->Rotate({0, 0, MainTimer::GetDeltaTime() }, eSpace::World);

	D_DEBUG_DRAW_3D_LINE(this->GetTransform()->GetPosition(), this->GetTransform()->GetPosition() + this->GetTransform()->forward() * 5, eColor::Red);
}

void doom::AutoRotate::OnEndOfFrame_Component()
{

}
