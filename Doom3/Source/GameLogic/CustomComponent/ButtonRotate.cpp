#include "ButtonRotate.h"

void dooms::ButtonRotate::InitComponent()
{
	//Base::InitComponent();
	
}

void dooms::ButtonRotate::UpdateComponent()
{
	if (userinput::UserInput_Server::GetKeyDown(dooms::graphics::GraphicsAPIInput::eKEY_CODE::KEY_F1))
	{
		GetTransform()->Rotate({ 0,  90.0f, 0 }, eSpace::Self);
	}


	//D_DEBUG_DRAW_3D_LINE(GetTransform()->GetPosition(), GetTransform()->GetPosition() + GetTransform()->forward() * 5, eColor::Red);
}

void dooms::ButtonRotate::OnEndOfFrame_Component()
{

}
