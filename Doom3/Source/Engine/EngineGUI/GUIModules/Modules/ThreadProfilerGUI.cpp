#include "ThreadProfilerGUI.h"

#include <vector>
#include <chrono>
#include "imgui.h"

#include <Time/MainTimer.h>
#include <ResourceManagement/Thread/ThreadManager.h>

#include "ResourceManagement/Thread/RunnableThread/RunnableThread.h"

#define THREAD_PROFILER_UPDATE_TIME_STEP 1.0f


void dooms::ui::ThreadProfilerGUI::UpdateThreadCycle()
{
	ElapsedTime += MainTimer::GetSingleton()->GetDeltaTime();
	if (ElapsedTime > THREAD_PROFILER_UPDATE_TIME_STEP)
	{
		std::vector<dooms::thread::RunnableThread*> ThreadList = dooms::thread::ThreadManager::GetSingleton()->GetRunnableThreadList();
		
		for (size_t Index = 0; Index < ThreadList.size(); Index++)
		{
			ThreadCycleCounter2[Index] = ThreadList[Index]->GetThreadCPUCycle();
		}

		for (size_t Index = 0; Index < ThreadCycleCounter1.size(); Index++)
		{
			ThreadCycleInSecond[Index] = (ThreadCycleCounter2[Index] - ThreadCycleCounter1[Index]) / ElapsedTime;
			ThreadCycleCounter1[Index] = ThreadCycleCounter2[Index];
		}

		ElapsedTime = 0.0f;
	}
}

void dooms::ui::ThreadProfilerGUI::Init()
{
	Base::Init();

	const size_t ThreadCount = dooms::thread::ThreadManager::GetSingleton()->GetRunnableThreadCount();
	ThreadCycleInSecond.resize(ThreadCount);
	ThreadCycleCounter1.resize(ThreadCount);
	ThreadCycleCounter2.resize(ThreadCount);
}

void dooms::ui::ThreadProfilerGUI::Render()
{
	UpdateThreadCycle();

	if (ImGui::Begin("Thread Profiler ( QueryThreadCycleTime ( /s ) )"))
	{
		ImGui::Text("Main Thread : %llu", ThreadCycleInSecond[0]);

		const size_t ThreadCount = dooms::thread::ThreadManager::GetSingleton()->GetRunnableThreadCount();
		for (size_t Index = 0; Index < ThreadCount; Index++)
		{
			ImGui::Text("Thread ( %d ) : %llu", Index, ThreadCycleInSecond[Index + 1]);
		}
	}

	ImGui::End();
}
