#include "AutoRotateAround.h"

void doom::AutoRotateAround::InitComponent()
{
}

void doom::AutoRotateAround::UpdateComponent()
{
	GetTransform()->RotateAround(mCenterPos, mRotateAxis, MainTimer::GetDeltaTime() * mRotateAngle);
}

void doom::AutoRotateAround::OnEndOfFrame_Component()
{
}
