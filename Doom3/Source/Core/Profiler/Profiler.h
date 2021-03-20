#pragma once

namespace doom
{
	class GameCore;
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

		class Profiler
		{
			friend class GameCore;

			class ProfilerPimpl;
			static inline ProfilerPimpl* mProfilerPimpl{ nullptr };
			
			static bool IsInitialized();
			static void InitProfiling() noexcept;
			
		public:
			
			static void StartProfiling(const char* name, eProfileLayers layer) noexcept;
			static void EndProfiling(const char* name) noexcept;
		};

	}
}
using doom::profiler::eProfileLayers;

