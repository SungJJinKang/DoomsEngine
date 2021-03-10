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

		/// <summary>
		/// Never Pass std::string, Do Pass Only literal string
		/// </summary>
		/// <param name="name"></param>
		/// <param name="layer"></param>
		/// <returns></returns>
		void StartProfiling(const char* name, eProfileLayers layer) noexcept;

		/// <summary>
		/// Never Pass std::string, Do Pass Only literal string
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		void EndProfiling(const char* name) noexcept;

	}
}
using doom::profiler::eProfileLayers;

