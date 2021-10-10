#include "Profiler.h"

#ifdef DEBUG_MODE

#include <iostream>
#include <thread>

#include <chrono>
#include <unordered_map>

#include <sstream>

#include <type_traits>

#include "Game/ConfigData.h"

#ifdef RELEASE_MODE
#define DISABLE_PROFILING
#endif

#ifndef THREAD_SAFE
//#define THREAD_SAFE
#endif

#ifdef THREAD_SAFE
#include <mutex>
#endif

namespace doom
{
	namespace profiler
	{
		class Profiler::ProfilerPimpl
		{
			friend class Profiler;
			friend class GameCore;

			using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;
			struct AvgElapsedTime
			{
				float mAvg;
				unsigned long long mElementCount;
			};

			using key_type = typename std::conditional_t<"TEST LITEAL STRING" == "TEST LITEAL STRING", const char*, std::string>;
			
		
			using elapsed_time_data_container_type = std::unordered_map<key_type, time_point>;
			using accumulated_time_data_container_type = std::unordered_map<key_type, std::pair<time_point, long long>>;

			using elapsed_time_thread_container_type_with = std::unordered_map<std::thread::id, elapsed_time_data_container_type>;
			using accumulated_time_thread_container_type_with = std::unordered_map<std::thread::id, accumulated_time_data_container_type>;
	
		private:

			static constexpr time_point time_point_zero{};

			elapsed_time_thread_container_type_with mElapsedTimeProfilingData{};
			elapsed_time_data_container_type::iterator mRecentElapsedTimeUpdatedNodeIterator;
			accumulated_time_thread_container_type_with mAccumulatedTimeProfilingData{};

			bool mIsRecentElapsedUpdatedNodeValid{ false };
#ifdef THREAD_SAFE
			std::mutex mProfilerMutex{};
#endif
			bool bmIsProfilerActivated{ false };
			bool bmIsActive{ true };

			elapsed_time_data_container_type& GetCurrentThreadElapsedTimeData(const std::thread::id& thread_id)
			{
				//TODO : don't need to lock mutex every time.
				//TODO : mutex lock is required only when insert new key
#ifdef THREAD_SAFE 
				std::scoped_lock lock{ mProfilerMutex };
#endif
				return mElapsedTimeProfilingData[thread_id];
			}

			accumulated_time_data_container_type& GetCurrentThreadAccumulatedTimeData(const std::thread::id& thread_id)
			{
				//TODO : don't need to lock mutex every time.
				//TODO : mutex lock is required only when insert new key
#ifdef THREAD_SAFE 
				std::scoped_lock lock{ mProfilerMutex };
#endif
				return mAccumulatedTimeProfilingData[thread_id];
			}

			ProfilerPimpl()
			{
				InitProfiling();
			}

			void InitProfiling() noexcept
			{
#ifdef DISABLE_PROFILING
				return;
#endif
				bmIsProfilerActivated = !(ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("SYSTEM", "DISABLE_PROFILER"));
			}

			FORCE_INLINE float CummulativeAverage(float prevAvg, float newNum, unsigned int elementCount)
			{
				const float oldWeight = (elementCount - 1) / elementCount;
				const float newWeight = 1 / elementCount;
				return (prevAvg * oldWeight) + (newNum * newWeight);
			}

			FORCE_INLINE void LogDuration(const std::thread::id& thread, const char* name, unsigned int elapsedTimeCountInMs)
			{
				std::ostringstream sstream;
				// used time in microseconds
				if (elapsedTimeCountInMs > 1000000)
				{
					sstream << '\n' << "Profiler ( " << thread << " ) : " << name << "  -  " << 0.000001 * elapsedTimeCountInMs << " seconds  =  " << elapsedTimeCountInMs << " microseconds";
				}
				else
				{
					sstream << '\n' << "Profiler ( " << thread << " ) : " << name << "  -  " << elapsedTimeCountInMs << " microseconds";
				}

				D_DEBUG_LOG(sstream.str(), eLogType::D_ALWAYS);
			}

			//

			FORCE_INLINE void StartElapsedTimeProfiling(const char* name, eProfileLayers layer) noexcept
			{
#ifdef DISABLE_PROFILING
				return;
#endif
				if (bmIsProfilerActivated == false || bmIsActive == false)
				{
					return;
				}

				time_point currentTime = std::chrono::high_resolution_clock::now();
				auto& currentThreadData = GetCurrentThreadElapsedTimeData(std::this_thread::get_id());

				mRecentElapsedTimeUpdatedNodeIterator = currentThreadData.insert_or_assign(name, currentTime).first;
				mIsRecentElapsedUpdatedNodeValid = true;
			}

		
			FORCE_INLINE void EndElapsedTimeProfiling(const char* name) noexcept
			{
#ifdef DISABLE_PROFILING
				return;
#endif

				if (bmIsProfilerActivated == false || bmIsActive == false)
				{
					return;
				}

				time_point currentTime = std::chrono::high_resolution_clock::now();
				std::thread::id currentThread = std::this_thread::get_id();
				auto& currentThreadData = GetCurrentThreadElapsedTimeData(currentThread);

				elapsed_time_data_container_type::iterator timeDataNode;
				if (mIsRecentElapsedUpdatedNodeValid == true && mRecentElapsedTimeUpdatedNodeIterator->first == name)
				{//passed key is same with key of mRecentElapsedTimeUpdatedNodeIterator!
					timeDataNode = mRecentElapsedTimeUpdatedNodeIterator;
				}
				else
				{
					timeDataNode = currentThreadData.find(name);
					if(timeDataNode == currentThreadData.end())
					{
						return;
					}
				}
				std::chrono::microseconds consumedTimeInMS = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - timeDataNode->second);
				LogDuration(currentThread, name, consumedTimeInMS.count());
				mIsRecentElapsedUpdatedNodeValid = false;


			}

	

			FORCE_INLINE void EmitAccumulationProfiling(const char* name) noexcept
			{
#ifdef DISABLE_PROFILING
				return;
#endif
				if (bmIsProfilerActivated == false || bmIsActive == false)
				{
					return;
				}

				std::thread::id currentThread = std::this_thread::get_id();
				auto& currentThreadData = GetCurrentThreadAccumulatedTimeData(currentThread);

				auto nodeIter = currentThreadData.find(name);
				if (nodeIter != currentThreadData.end())
				{
					LogDuration(currentThread, name, nodeIter->second.second);
					nodeIter->second.second = 0;
				}
			}

			FORCE_INLINE void StartAccumulationTimeProfiling(const char* name, eProfileLayers layer) noexcept
			{
#ifdef DISABLE_PROFILING
				return;
#endif
				if (bmIsProfilerActivated == false || bmIsActive == false)
				{
					return;
				}

				time_point currentTime = std::chrono::high_resolution_clock::now();
				auto& currentThreadData = GetCurrentThreadAccumulatedTimeData(std::this_thread::get_id());

			
				auto [iter, isInserted] = currentThreadData.try_emplace(name, currentTime, 0);
				iter->second.first = currentTime;
			}

			FORCE_INLINE void EndAccumulationTimeProfiling(const char* name) noexcept
			{
#ifdef DISABLE_PROFILING
				return;
#endif

				if (bmIsProfilerActivated == false || bmIsActive == false)
				{
					return;
				}

				time_point currentTime = std::chrono::high_resolution_clock::now();

				std::thread::id currentThread = std::this_thread::get_id();
				auto& currentThreadData = GetCurrentThreadAccumulatedTimeData(currentThread);

				accumulated_time_data_container_type::iterator timeDataNode = currentThreadData.find(name);
				if (timeDataNode != currentThreadData.end())
				{
					std::chrono::microseconds consumedTimeInMS = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - timeDataNode->second.first);
					timeDataNode->second.first = currentTime;
					timeDataNode->second.second = 0;

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


		void Profiler::StartElapsedTimeProfiling(const char* name, eProfileLayers layer) noexcept
		{
			if (Profiler::IsInitialized() == true)
			{
				mProfilerPimpl->StartElapsedTimeProfiling(name, layer);
			}
		}

		void Profiler::EndElapsedTimeProfiling(const char* name) noexcept
		{
			if (Profiler::IsInitialized() == true)
			{
				mProfilerPimpl->EndElapsedTimeProfiling(name);
			}
		}

		void Profiler::StartAccumulationTimeProfiling(const char* name, eProfileLayers layer) noexcept
		{
			if (Profiler::IsInitialized() == true)
			{
				mProfilerPimpl->StartAccumulationTimeProfiling(name, layer);
			}
		}

		void Profiler::EndAccumulationTimeProfiling(const char* name) noexcept
		{
			if (Profiler::IsInitialized() == true)
			{
				mProfilerPimpl->EndAccumulationTimeProfiling(name);
			}
		}

		void Profiler::EmitAcculationProfiling(const char* name) noexcept
		{
			if (Profiler::IsInitialized() == true)
			{
				mProfilerPimpl->EmitAccumulationProfiling(name);
			}
		}

		void Profiler::SetActiveToggle()
		{
			if (Profiler::IsInitialized() == true)
			{
				mProfilerPimpl->bmIsActive = !(mProfilerPimpl->bmIsActive);
			}
		}

	}
}


#endif