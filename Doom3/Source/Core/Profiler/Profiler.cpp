#include "Profiler.h"

#include <iostream>
#include <thread>

#include <chrono>
#include <unordered_map>
#include <mutex>

#include <type_traits>

#include "Game/ConfigData.h"

#ifdef RELEASE_MODE
#define DISABLE_PROFILING
#endif

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


		class Profiler::ProfilerPimpl
		{
			friend class Profiler;

			using key_type = typename std::conditional_t<"TEST LITEAL STRING" == "TEST LITEAL STRING", const char*, std::string>;

		private:
			std::unordered_map<std::thread::id, std::unordered_map<key_type, std::chrono::time_point<std::chrono::high_resolution_clock>>> _ProfilingData{};
			std::mutex mProfilerMutex{};
			bool bmIsProfilerActivated{ false };

			 std::unordered_map<key_type, std::chrono::time_point<std::chrono::high_resolution_clock>>& GetCurrentThreadData(const std::thread::id& thread_id)
			{
				//TODO : don't need to lock mutex every time.
				//TODO : mutex lock is required only when insert new key
				std::scoped_lock lock{ this->mProfilerMutex };
				return this->_ProfilingData[thread_id];
			}

			 ProfilerPimpl()
			 {
				 this->InitProfiling();
			 }

			 void InitProfiling() noexcept
			{
#ifdef DISABLE_PROFILING
				return;
#endif
				bmIsProfilerActivated = !(ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("SYSTEM", "DISABLE_PROFILER"));
			}

			//
			 void StartProfiling(const char* name, eProfileLayers layer) noexcept
			{
#ifdef DISABLE_PROFILING
				return;
#endif
				if (bmIsProfilerActivated == false)
				{
					return;
				}

				auto& currentThreadData = this->GetCurrentThreadData(std::this_thread::get_id());

				currentThreadData[name] = std::chrono::high_resolution_clock::now();
			}

			 void EndProfiling(const char* name) noexcept
			{
#ifdef DISABLE_PROFILING
				return;
#endif

				if (bmIsProfilerActivated == false)
				{
					return;
				}

				std::thread::id currentThread = std::this_thread::get_id();
				auto& currentThreadData = this->GetCurrentThreadData(currentThread);
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
		};

		bool Profiler::IsInitialized()
		{
			return mProfilerPimpl != nullptr;
		}

		void Profiler::InitProfiling() noexcept
		{
			mProfilerPimpl = new ProfilerPimpl();
		}
		

		void Profiler::StartProfiling(const char* name, eProfileLayers layer) noexcept
		{
			if (Profiler::IsInitialized() == true)
			{
				mProfilerPimpl->StartProfiling(name, layer);
			}
		}

		void Profiler::EndProfiling(const char* name) noexcept
		{
			if (Profiler::IsInitialized() == true)
			{
				mProfilerPimpl->EndProfiling(name);
			}
		}

	}
}
