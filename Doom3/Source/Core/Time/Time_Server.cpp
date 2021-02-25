#include "Time_Server.h"

#include <utility>

#include "MainTimer.h"

void doom::time::Time_Server::Init() noexcept
{
	MainTimer::InitTimer();
}

void doom::time::Time_Server::Update() noexcept
{
	MainTimer::UpdateTimer();
}

void doom::time::Time_Server::OnEndOfFrame() noexcept
{
	
}
