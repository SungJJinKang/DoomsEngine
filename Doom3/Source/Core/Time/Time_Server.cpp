#include "Time_Server.h"

#include "MainTimer.h"

void dooms::time::Time_Server::Init(const int argc, char* const* const argv) noexcept
{
	mMainTimer.InitTimer();
}

void dooms::time::Time_Server::Update() noexcept
{
}

void dooms::time::Time_Server::OnEndOfFrame() noexcept
{
	
}
