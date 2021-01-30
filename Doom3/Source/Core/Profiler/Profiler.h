#pragma once


namespace doom
{
	namespace profiler
	{
		enum class eProfileLayers
		{
			CPU,
			GPU,
			PHYSICS,
			UI,
			SOUND
		};

		void StartProfiling(const char* name, eProfileLayers layer) noexcept;
		void EndProfiling(const char* name) noexcept;

	}
}
using doom::profiler::eProfileLayers;

#ifdef MACRO_IMPLEMENTATION
#include <chrono>
#include <unordered_map>
#include <mutex>
namespace doom
{
	namespace profiler
	{

		class Profiler
		{
		private:
			static std::unordered_map<std::thread::id, std::unordered_map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>>> _ProfilingData;

			static std::mutex mProfilerMutex;
			static bool bIsInitProfiling;
			static void _InitProfiling() noexcept;

		public:
			static void _StartProfiling(const char* name, eProfileLayers layer) noexcept;
			static void _EndProfiling(const char* name) noexcept;
		};

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
#endif