#include "Time_Server.h"

#include <utility>

void doom::time::Time_Server::Init() noexcept
{
}

void doom::time::Time_Server::Update() noexcept
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	doom::time::Time_Server::mCurrentTime = currentTime.time_since_epoch().count();

	doom::time::Time_Server::mDeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - doom::time::Time_Server::mLastTime).count() * 0.000001;
	doom::time::Time_Server::mLastTime = std::move(currentTime);

	
}

void doom::time::Time_Server::OnEndOfFrame() noexcept
{
	
}
