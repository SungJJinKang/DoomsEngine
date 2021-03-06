#include "Profiler.h"

#include <iostream>
#include <thread>

#include <chrono>
#include <unordered_map>
#include <mutex>

#include <type_traits>

namespace doom
{
	namespace profiler
	{

		template <char* a, char* b>
		struct LiteralStringOverlapCheck
		{
			constexpr operator bool() const noexcept 
			{ 
				return a == b; 
			}
		};

		class Profiler
		{
			/// <summary>
			/// Why use this?
			/// 
			/// </summary>
			using key_type = typename std::conditional_t<"TEST LITEAL STRING" == "TEST LITEAL STRING", const char*, std::string>;
		private:
			static inline std::unordered_map<std::thread::id, std::unordered_map<key_type, std::chrono::time_point<std::chrono::high_resolution_clock>>> _ProfilingData{};

			static inline std::mutex mProfilerMutex{};
			static inline bool bIsInitProfiling{ false };
			static void _InitProfiling() noexcept;
			static std::unordered_map<key_type, std::chrono::time_point<std::chrono::high_resolution_clock>>& GetCurrentThreadData(const std::thread::id& thread_id);
		public:
			static void _StartProfiling(const char* name, eProfileLayers layer) noexcept;
			static void _EndProfiling(const char* name) noexcept;
		};

		void Profiler::_InitProfiling() noexcept
		{
		}

		std::unordered_map<const char*, std::chrono::time_point<std::chrono::high_resolution_clock>>& Profiler::GetCurrentThreadData(const std::thread::id& thread_id)
		{
			//TODO : don't need to lock mutex every time.
			//TODO : mutex lock is required only when insert new key
			std::scoped_lock lock{ Profiler::mProfilerMutex };
			return Profiler::_ProfilingData[thread_id];
		}


		//
		void Profiler::_StartProfiling(const char* name, eProfileLayers layer) noexcept
		{
			auto& currentThreadData = Profiler::GetCurrentThreadData(std::this_thread::get_id());
			
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



		void StartProfiling(const char* name, eProfileLayers layer) noexcept
		{
			Profiler::_StartProfiling(name, layer);
		}
		void EndProfiling(const char* name) noexcept
		{
			Profiler::_EndProfiling(name);
		}
	}
}
