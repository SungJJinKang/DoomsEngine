#pragma once

#include <CompilerMacros.h>
#include "MacrosHelper.h"

#include <iostream>
#include <chrono>

#include <Profiler/ProfilingManager.h>

#ifndef PROFILING_RELEASE_MODE
#define PROFILING_RELEASE_MODE
#endif

// std::chrono::high_resolution_clock::now() has more resolution than OS GetTickCount API 

#ifndef D_START_PROFILING_INTERNAL

#define D_START_PROFILING_INTERNAL(PROFILING_TAG)													\
																									\
const auto CONCAT(PROFILING_TAG, _START) = std::chrono::high_resolution_clock::now();				\
static UINT32 CONCAT(PROFILING_TAG, _EXECUTE_COUNT) = 0										\

#endif


// TODO : implement gui for profiling datas
#ifndef D_END_PROFILING_INTERNAL

#define D_END_PROFILING_INTERNAL(PROFILING_TAG)																																									\
const auto CONCAT(PROFILING_TAG, _END) = std::chrono::high_resolution_clock::now();																																		\
thread_local static std::chrono::duration<FLOAT64, std::milli> CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) = std::chrono::duration<FLOAT64, std::milli>::zero();																		\
CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) += std::chrono::duration_cast<std::chrono::duration<FLOAT64, std::milli>>(CONCAT(PROFILING_TAG, _END) - CONCAT(PROFILING_TAG, _START));										\
																																																						\
thread_local static auto CONCAT(PROFILING_TAG, _EX_TICK_TIME) = std::chrono::high_resolution_clock::now();																															\
thread_local static std::chrono::duration<FLOAT64, std::milli> CONCAT(PROFILING_TAG, _ELAPSED_TIME) = std::chrono::duration<FLOAT64, std::milli>::zero();																				\
CONCAT(PROFILING_TAG, _ELAPSED_TIME) += std::chrono::duration_cast<std::chrono::duration<FLOAT64, std::milli>>(CONCAT(PROFILING_TAG, _END) - CONCAT(PROFILING_TAG, _EX_TICK_TIME));										\
CONCAT(PROFILING_TAG, _EX_TICK_TIME) = CONCAT(PROFILING_TAG, _END);																																						\
CONCAT(PROFILING_TAG, _EXECUTE_COUNT)++;																																												\
if (CONCAT(PROFILING_TAG, _ELAPSED_TIME).count() >= 1000.0)																																								\
{																																																						\
dooms::profiling::profilingManager::AddProfilingData(MAKE_STRING(PROFILING_TAG), static_cast<FLOAT32>(CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME).count()) / static_cast<FLOAT32>(CONCAT(PROFILING_TAG, _EXECUTE_COUNT)));					\
CONCAT(PROFILING_TAG, _ELAPSED_TIME) = std::chrono::duration<FLOAT64, std::milli>::zero();																																\
CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) = std::chrono::duration<FLOAT64, std::milli>::zero();																														\
CONCAT(PROFILING_TAG, _EXECUTE_COUNT) = 0;																																												\
}																																																						\

#endif

#undef D_PROFILING

#if ( defined(DEBUG_MODE) || defined(PROFILING_RELEASE_MODE) )

#ifndef D_START_PROFILING
#define D_START_PROFILING(PROFILING_TAG, LAYER) D_START_PROFILING_INTERNAL(PROFILING_TAG)
#endif

#ifndef D_END_PROFILING
#define D_END_PROFILING(PROFILING_TAG) D_END_PROFILING_INTERNAL(PROFILING_TAG)
#endif

#define D_PROFILING

#else

#ifndef D_START_PROFILING
#define D_START_PROFILING(name, layer)
#endif

#ifndef D_END_PROFILING
#define D_END_PROFILING(name)
#endif

#endif
