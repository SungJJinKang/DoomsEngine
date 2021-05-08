#include "ButtonRotate.h"

void doom::ButtonRotate::InitComponent()
{

}

void doom::ButtonRotate::UpdateComponent()
{
	if (userinput::UserInput_Server::GetKeyDown(eKEY_CODE::KEY_F1))
	{
		this->GetTransform()->Rotate({ 0,  90.0f, 0 }, eSpace::Self);
	}


	//D_DEBUG_DRAW_3D_LINE(this->GetTransform()->GetPosition(), this->GetTransform()->GetPosition() + this->GetTransform()->forward() * 5, eColor::Red);
}

void doom::ButtonRotate::OnEndOfFrame_Component()
{

}
