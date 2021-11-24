#pragma once

#include <string>
#include <type_traits>

#include "Macros/Assert.h"

#define LOG_BUFFER_COUNT 100
#define LOG_MAX_LENGTH 150

namespace dooms
{
	namespace ui
	{
		class log
		{
		private:

			
			inline static int LogIndex = -1;
			inline static bool isInitialized = false;
			inline static char LogBuffer[LOG_BUFFER_COUNT][LOG_MAX_LENGTH]{};
			static int IncrementLogIndex();
			

		public:

			inline static bool IsEnabled = true;

			static void Initialize();



			template<typename ... Args>
			static void LogOnGUI(const char* const format, Args ... args)
			{
				static_assert((!std::is_same_v<std::string, Args> && ...), "Don't pass std::string, Please use string::c_str()");

				if(IsEnabled == true)
				{
					size_t size = snprintf(nullptr, 0, format, args ...) + 1; // Extra space for '\0'
					if (size <= 0)
					{
						return;
					}

					const int currentLogIndex = IncrementLogIndex();
					LogBuffer[currentLogIndex][LOG_MAX_LENGTH - 1] = '\0';


					snprintf(LogBuffer[currentLogIndex], size > (LOG_MAX_LENGTH - 1) ? (LOG_MAX_LENGTH - 1) : size, format, args ...);
				}
			}

			static void Render();
		};
		
	}
}
