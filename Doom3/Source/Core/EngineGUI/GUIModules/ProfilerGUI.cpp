#include "ProfilerGUI.h"

#include <utility>
#include <mutex>
#include <shared_mutex>


#include "imgui.h"
#include <Time/MainTimer.h>
#include <Graphics/DebugGraphics/RenderingDebugger.h>

#define PROFILING_TEXT_RED_COLOR_DURATION_TIME 0.2f

namespace dooms::ui::profilerGUI
{
	//key : profiling tag ( string )
	//value : profiling time, text red color duration
	static std::unordered_map<std::string, std::pair<float, float>> mProfilingDataContainer{};
	static std::shared_mutex mProfilingMutex{};
}


void dooms::ui::profilerGUI::Render()
{
	if (ImGui::Begin("Profiler"))
	{
		for (auto& data : mProfilingDataContainer)
		{
			ImGui::Text("%s   :    ", data.first.c_str());

			if(data.second.second > 0.0f)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
			}
			ImGui::SameLine(0, 10);

			ImGui::Text("%f ( ms )", data.second.first);

			if (data.second.second > 0.0f)
			{
				ImGui::PopStyleColor();
				data.second.second -= dooms::time::MainTimer::GetSingleton()->GetDeltaTime();
			}
		}
	}

	ImGui::End();
}

void dooms::ui::profilerGUI::AddProfilingData(const char* const profilingTagName, const float time)
{
	std::string tag = profilingTagName;

	std::shared_lock<std::shared_mutex> sLock{ mProfilingMutex };

	auto iter = mProfilingDataContainer.find(tag);
	if(iter == mProfilingDataContainer.end())
	{
		sLock.unlock();
		std::unique_lock<std::shared_mutex> uLock{ mProfilingMutex };
		mProfilingDataContainer.emplace(tag, std::make_pair(time, PROFILING_TEXT_RED_COLOR_DURATION_TIME));
		uLock.unlock();
	}
	else
	{
		sLock.unlock();
		iter->second = std::make_pair(time, PROFILING_TEXT_RED_COLOR_DURATION_TIME);
	}

}
