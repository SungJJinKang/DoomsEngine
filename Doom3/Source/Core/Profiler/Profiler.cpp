#define MACRO_IMPLEMENTATION

#include "Profiler.h"

#include <iostream>
#include <thread>

namespace doom
{
	namespace profiler
	{
		std::unordered_map<std::thread::id, std::unordered_map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>>> Profiler::_ProfilingData{};
		bool Profiler::bIsInitProfiling{ false };
		std::mutex Profiler::mProfilerMutex{};

		void Profiler::_InitProfiling() noexcept
		{
		}

		std::unordered_map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>>& Profiler::GetCurrentThreadData(const std::thread::id& thread_id)
		{
			//TODO : don't need to lock mutex every time.
			//TODO : mutex lock is required only when insert new key
			std::scoped_lock lock{ Profiler::mProfilerMutex };
			return Profiler::_ProfilingData[thread_id];
		}

		void Profiler::_StartProfiling(const char* name, eProfileLayers layer) noexcept
		{
			std::thread::id currentThread = std::this_thread::get_id();
			auto& currentThreadData = Profiler::GetCurrentThreadData(currentThread);
			currentThreadData[name] = std::chrono::high_resolution_clock::now();
		}

		void Profiler::_EndProfiling(const char* name) noexcept
		{
			std::thread::id currentThread = std::this_thread::get_id();
			auto& currentThreadData = Profiler::GetCurrentThreadData(currentThread);
			long long consumedTimeInMS = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - currentThreadData[name]).count();
	

			// used time in microseconds
			if (consumedTimeInMS > 1000000)
			{
				std::cout << '\n' << "Profiler ( " << currentThread << " ) : " << name << "  -  " << 0.000001 * consumedTimeInMS << " seconds  =  " << consumedTimeInMS << " microseconds" << std::endl;
			}
			else
			{
				std::cout << '\n' << "Profiler ( " << currentThread << " ) : " << name << "  -  " << consumedTimeInMS << " microseconds" << std::endl;
			}
			
		}
	}
}
