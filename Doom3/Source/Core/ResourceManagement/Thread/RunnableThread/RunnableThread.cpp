#include "RunnableThread.h"

dooms::thread::RunnableThread::RunnableThread(const char* const _BeautifulThreadName)
	: BeautifulThreadName(_BeautifulThreadName)
{
}

void dooms::thread::RunnableThread::Init()
{
	bInitialized = true;

	D_DEBUG_LOG(eLogType::D_LOG, "Thread ( %s ) is initialized", BeautifulThreadName.c_str());
}

void dooms::thread::RunnableThread::Loop()
{
}

void dooms::thread::RunnableThread::Tick()
{
	if(bInitialized == false)
	{
		Init();
	}

	Loop();
}

std::string dooms::thread::RunnableThread::GetBeautifulThreadName() const
{
	return BeautifulThreadName;
}
