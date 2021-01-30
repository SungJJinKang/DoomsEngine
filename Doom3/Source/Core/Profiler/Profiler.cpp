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
			Profiler::bIsInitProfiling = true;
		}

		void Profiler::_StartProfiling(const char* name, eProfileLayers layer) noexcept
		{
			if (Profiler::bIsInitProfiling == false)
			{
				Profiler::_InitProfiling();
			}

			std::unordered_map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>>* this_thread_data;
			{
				std::scoped_lock lock{ Profiler::mProfilerMutex };
				this_thread_data = &(Profiler::_ProfilingData[std::this_thread::get_id()]);
			}
			this_thread_data->operator[](name) = std::chrono::high_resolution_clock::now();
		}

		void Profiler::_EndProfiling(const char* name) noexcept
		{
			long long consumedTimeInMS;
			auto this_thread = std::this_thread::get_id();
			{
				std::scoped_lock lock{ Profiler::mProfilerMutex };
				consumedTimeInMS = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - Profiler::_ProfilingData[this_thread][name]).count();
			}

			// used time in microseconds
			if (consumedTimeInMS > 1000000)
			{
				std::cout << '\n' << "Profiler ( " << this_thread << " ) : " << name << "  -  " << 0.000001 * consumedTimeInMS << " seconds  =  " << consumedTimeInMS << " microseconds" << std::endl;
			}
			else
			{
				std::cout << '\n' << "Profiler ( " << this_thread << " ) : " << name << "  -  " << consumedTimeInMS << " microseconds" << std::endl;
			}
			
		}
	}
}
