#include "AutoRotateAround.h"

void doom::AutoRotateAround::InitComponent()
{
}

void doom::AutoRotateAround::UpdateComponent()
{
	if (doom::userinput::UserInput_Server::GetKey(eKEY_CODE::KEY_SPACE))
	{
		GetTransform()->RotateAround(mCenterPos, mRotateAxis, MainTimer::GetDeltaTime() * mRotateAngle);
	}

}

void doom::AutoRotateAround::OnEndOfFrame_Component()
{
}
