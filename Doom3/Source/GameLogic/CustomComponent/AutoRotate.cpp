#include "AutoRotate.h"

void doom::AutoRotate::InitComponent()
{

}

void doom::AutoRotate::UpdateComponent()
{

	this->GetTransform()->Rotate({Time_Server::GetDeltaTime(), 0, 0}, eSpace::World);
}

void doom::AutoRotate::OnEndOfFrame_Component()
{

}
