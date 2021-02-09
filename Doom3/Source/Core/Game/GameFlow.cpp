#include "GameFlow.h"

using namespace doom;

void doom::GameFlow::Init_Internal()
{
}

void doom::GameFlow::Update_Internal()
{
}

void doom::GameFlow::OnEndOfFrame_Internal()
{
	this->FrameDirtyChecker_EndOfFrame();
}

doom::GameFlow::~GameFlow()
{
}
