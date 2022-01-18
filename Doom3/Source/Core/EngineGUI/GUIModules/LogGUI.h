#pragma once

#include <string>
#include <atomic>
#include <mutex>

#include "Macros/Assert.h"

#define GUI_LOG_BUFFER_COUNT 100
#define GUI_LOG_MAX_LENGTH 50

namespace dooms
{
	namespace ui
	{
		class log
		{
		private:
			
			inline static std::atomic<long> LogIndex = 0;
			inline static bool isInitialized = false;
			inline static char LogBuffer[GUI_LOG_BUFFER_COUNT][GUI_LOG_MAX_LENGTH]{};
			inline static std::mutex LogBufferMutex[GUI_LOG_BUFFER_COUNT]{};
			static long IncrementLogIndex();
			

		public:

			inline static bool IsEnabled = true;

			static void Initialize();



			template<typename ... Args>
			static void LogOnGUI(const char* const format, Args ... args)
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

					std::scoped_lock<std::mutex> lock{ LogBufferMutex[currentLogIndex] };

					LogBuffer[currentLogIndex][GUI_LOG_MAX_LENGTH - 1] = '\0';
					
					snprintf(LogBuffer[currentLogIndex], size > (GUI_LOG_MAX_LENGTH - 1) ? (GUI_LOG_MAX_LENGTH - 1) : size, format, args ...);
				}
			}

			static void Render();
		};
		
	}
}
