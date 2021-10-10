#include "Time_Server.h"

#include "MainTimer.h"

void doom::time::Time_Server::Init() noexcept
{
	MainTimer::InitTimer();
}

void doom::time::Time_Server::Update() noexcept
{
}

void doom::time::Time_Server::OnEndOfFrame() noexcept
{
	
}
