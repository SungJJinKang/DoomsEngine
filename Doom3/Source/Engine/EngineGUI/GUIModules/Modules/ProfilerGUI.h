#pragma once

#include <shared_mutex>
#include <unordered_map>
#include <string>
#include <utility>

#include "../EngineGUIModule.h"
#include <SingleTon/Singleton.h>

#include "ProfilerGUI.reflection.h"
namespace dooms
{
	namespace ui
	{
		class D_CLASS ProfilerGUI : public EngineGUIModule, public ISingleton<ProfilerGUI>
		{
			GENERATE_BODY()
		private:

			std::unordered_map<std::string, std::pair<float, float>> mProfilingDataContainer{};
			std::shared_mutex mProfilingMutex{};

		public:

			void Init() override;
			void Render() override;
			void AddProfilingData(const char* const profilingTagName, const float time);
			
		};
	}
}

