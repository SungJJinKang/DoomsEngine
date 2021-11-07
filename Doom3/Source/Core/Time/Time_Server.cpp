#include "Time_Server.h"

#include "MainTimer.h"

void dooms::time::Time_Server::Init() noexcept
{
	MainTimer::InitTimer();
}

void dooms::time::Time_Server::Update() noexcept
{
}

void dooms::time::Time_Server::OnEndOfFrame() noexcept
{
	
}
