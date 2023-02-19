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

		if (ThreadCycleContainerList.size() != ThreadList.size())
		{
			ThreadCycleContainerList.resize(ThreadList.size());
		}
		
		for (size_t Index = 0; Index < ThreadList.size(); Index++)
		{
			ThreadCycleContainerList[Index].ThreadName = ThreadList[Index]->GetThreadName();
			ThreadCycleContainerList[Index].ThreadCycleCounter2 = ThreadList[Index]->GetThreadCPUCycle();
		}

		for (size_t Index = 0; Index < ThreadCycleContainerList.size(); Index++)
		{
			ThreadCycleContainerList[Index].ThreadCycleInSecond = (ThreadCycleContainerList[Index].ThreadCycleCounter2 - ThreadCycleContainerList[Index].ThreadCycleCounter1) / ElapsedTime;
			ThreadCycleContainerList[Index].ThreadCycleCounter1 = ThreadCycleContainerList[Index].ThreadCycleCounter2;
		}

		ElapsedTime = 0.0f;
	}
}

void dooms::ui::ThreadProfilerGUI::Init()
{
	Base::Init();

}

void dooms::ui::ThreadProfilerGUI::Render()
{
	UpdateThreadCycle();

	if (ImGui::Begin("Thread Profiler ( QueryThreadCycleTime ( /s ) )"))
	{
		for (size_t Index = 0; Index < ThreadCycleContainerList.size(); Index++)
		{
			ImGui::Text("%s (%d) : %llu", ThreadCycleContainerList[Index].ThreadName, Index, ThreadCycleContainerList[Index].ThreadCycleInSecond);
		}
	}

	ImGui::End();
}
