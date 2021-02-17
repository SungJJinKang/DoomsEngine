#include "AutoRotate.h"

void doom::AutoRotate::InitComponent()
{

}

void doom::AutoRotate::UpdateComponent()
{
	this->GetTransform()->Rotate({0, Time_Server::GetDeltaTime(), 0}, eSpace::World);

	D_DEBUG_DRAW_LINE(this->GetTransform()->GetPosition(), this->GetTransform()->GetPosition() + this->GetTransform()->forward() * 5, eColor::Red);
}

void doom::AutoRotate::OnEndOfFrame_Component()
{

}
