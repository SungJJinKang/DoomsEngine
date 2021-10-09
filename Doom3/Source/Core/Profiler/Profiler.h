#pragma once

#ifdef DEBUG_MODE


namespace doom
{
	class GameCore;
	namespace profiler
	{
		enum class eProfileLayers
		{
			CPU,
			Rendering,
			PHYSICS,
			UI,
			SOUND
		};


		class DOOM_API Profiler
		{
			friend class GameCore;

			class ProfilerPimpl;
			static inline ProfilerPimpl* mProfilerPimpl{ nullptr };
			
			static bool IsInitialized();
			static void InitProfiling() noexcept;
			
		public:
			
			static void StartElapsedTimeProfiling(const char* name, eProfileLayers layer) noexcept;
			static void EndElapsedTimeProfiling(const char* name) noexcept;

			static void StartAccumulationTimeProfiling(const char* name, eProfileLayers layer) noexcept;
			static void EndAccumulationTimeProfiling(const char* name) noexcept;
			static void EmitAcculationProfiling(const char* name) noexcept;
			static void SetActiveToggle();
		};

	}
}
using doom::profiler::eProfileLayers;


#endif