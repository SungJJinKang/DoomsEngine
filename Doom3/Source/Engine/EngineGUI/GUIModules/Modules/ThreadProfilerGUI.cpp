#include "ThreadProfilerGUI.h"

#include <vector>
#include <chrono>
#include "imgui.h"

#include <Time/MainTimer.h>
#include <ResourceManagement/JobSystem_cpp/JobSystem.h>

#define THREAD_PROFILER_UPDATE_TIME_STEP 1.0f


void dooms::ui::ThreadProfilerGUI::UpdateThreadCycle()
{
	ElapsedTime += MainTimer::GetSingleton()->GetDeltaTime();
	if (ElapsedTime > THREAD_PROFILER_UPDATE_TIME_STEP)
	{
		const size_t threadCount = resource::JobSystem::GetSingleton()->GetSubThreadCount();

		ThreadCycleCounter2[0] = dooms::os::_GetThreadCpuCycle(dooms::resource::JobSystem::GetSingleton()->GetMainThreadPlatformHandle());
		for (size_t i = 0; i < threadCount; i++)
		{
			ThreadCycleCounter2[i + 1] = resource::JobSystem::GetSingleton()->GetThread(i).GetThreadCPUCycle();
		}

		for (size_t i = 0; i < ThreadCycleCounter1.size(); i++)
		{
			ThreadCycleInSecond[i] = (ThreadCycleCounter2[i] - ThreadCycleCounter1[i]) / ElapsedTime;
			ThreadCycleCounter1[i] = ThreadCycleCounter2[i];
		}

		ElapsedTime = 0.0f;
	}
}

void dooms::ui::ThreadProfilerGUI::Init()
{
	Base::Init();

	const size_t threadCount = resource::JobSystem::GetSingleton()->GetSubThreadCount();
	ThreadCycleInSecond.resize(threadCount + 1);
	ThreadCycleCounter1.resize(threadCount + 1);
	ThreadCycleCounter2.resize(threadCount + 1);
}

void dooms::ui::ThreadProfilerGUI::Render()
{
	UpdateThreadCycle();

	if (ImGui::Begin("Thread Profiler ( QueryThreadCycleTime ( /s ) )"))
	{
		ImGui::Text("Main Thread : %llu", ThreadCycleInSecond[0]);

		const size_t threadCount = resource::JobSystem::GetSingleton()->GetSubThreadCount();
		for (size_t i = 0; i < threadCount; i++)
		{
			ImGui::Text("Thread ( %d ) : %llu", i, ThreadCycleInSecond[i + 1]);
		}
	}

	ImGui::End();
}
