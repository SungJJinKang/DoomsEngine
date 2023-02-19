#pragma once

#include <string>
#include <atomic>
#include <mutex>

#include "../EngineGUIModule.h"
#include <SingleTon/Singleton.h>
#include "Macros/Assert.h"

#define GUI_LOG_BUFFER_COUNT 1000
#define GUI_LOG_MAX_LENGTH 200

#include "LogGUI.reflection.h"
namespace dooms
{
	namespace ui
	{
		class D_CLASS LogGUI : public EngineGUIModule, public ISingleton<LogGUI>
		{
			GENERATE_BODY()

		private:
			
			std::atomic<long> LogIndex = 0;
			char LogBuffer[GUI_LOG_BUFFER_COUNT][GUI_LOG_MAX_LENGTH]{};
			std::mutex LogBufferMutex[GUI_LOG_BUFFER_COUNT]{};

			long IncrementLogIndex();
			void RenderMenuBar();


		public:

			bool IsEnabled = true;

			void Init() override;
			void Render() override;

			template<typename ... Args>
			void LogOnGUI(const char* const format, Args ... args)
			{
				static_assert((!std::is_same_v<std::string, Args> && ...), "Don't pass std::string, Please use string::c_str()");

				if(IsEnabled == true)
				{
					//snprintf is thread-safe ( https://stackoverflow.com/questions/13386352/is-sprintf-thread-safe )
					size_t size = snprintf(nullptr, 0, format, args ...) + 1; // Extra space for '\0'
					if (size <= 0)
					{
						return;
					}

					const long currentLogIndex = IncrementLogIndex();
					D_ASSERT(currentLogIndex < GUI_LOG_BUFFER_COUNT);

					// @todo : remove mutex lock. implement lock free log
					// use thread local buffer. merge them when show logs
					std::scoped_lock<std::mutex> lock{ LogBufferMutex[currentLogIndex] };

					LogBuffer[currentLogIndex][GUI_LOG_MAX_LENGTH - 1] = '\0';
					
					snprintf(LogBuffer[currentLogIndex], size > (GUI_LOG_MAX_LENGTH - 1) ? (GUI_LOG_MAX_LENGTH - 1) : size, format, args ...);
				}
			}
			
		};
		
	}
}
