#include "AutoRotate.h"

void doom::AutoRotate::InitComponent()
{

}

void doom::AutoRotate::UpdateComponent()
{
	this->GetTransform()->Rotate({0, Time_Server::GetDeltaTime(), 0}, eSpace::World);

	Debug::DrawLine(this->GetTransform()->GetPosition(), this->GetTransform()->GetPosition() + this->GetTransform()->forward() * 5, math::Vector4{ 1.0f, 0.0, 0.0, 1.0f });
}

void doom::AutoRotate::OnEndOfFrame_Component()
{

}
