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

//why use MACRO_IMPLEMENTATION
// below codes never included in Core.h file
// All Game Sources Codes include Core.h file,
// So I should make files included in core.h LIGHT!!
// 
// Codes enclosed by MACRO_IMPLEMENTATION isn't included in Core.h File, This will decrease build time
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
			static std::unordered_map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>>& GetCurrentThreadData(const std::thread::id& thread_id);
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