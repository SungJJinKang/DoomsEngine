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

