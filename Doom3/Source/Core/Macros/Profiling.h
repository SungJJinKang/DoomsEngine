#pragma once

#include <CompilerMacros.h>
#include "MacrosHelper.h"

#include <iostream>
#include <chrono>

#include "Log.h"

#ifndef ALWAYS_PROFILING
//#define ALWAYS_PROFILING
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
static std::chrono::duration<FLOAT64, std::milli> CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) = std::chrono::duration<FLOAT64, std::milli>::zero();																		\
CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) += std::chrono::duration_cast<std::chrono::duration<FLOAT64, std::milli>>(CONCAT(PROFILING_TAG, _END) - CONCAT(PROFILING_TAG, _START));										\
																																																						\
static auto CONCAT(PROFILING_TAG, _EX_TICK_TIME) = std::chrono::high_resolution_clock::now();																															\
static std::chrono::duration<FLOAT64, std::milli> CONCAT(PROFILING_TAG, _ELAPSED_TIME) = std::chrono::duration<FLOAT64, std::milli>::zero();																				\
CONCAT(PROFILING_TAG, _ELAPSED_TIME) += std::chrono::duration_cast<std::chrono::duration<FLOAT64, std::milli>>(CONCAT(PROFILING_TAG, _END) - CONCAT(PROFILING_TAG, _EX_TICK_TIME));										\
CONCAT(PROFILING_TAG, _EX_TICK_TIME) = CONCAT(PROFILING_TAG, _END);																																						\
CONCAT(PROFILING_TAG, _EXECUTE_COUNT)++;																																												\
if (CONCAT(PROFILING_TAG, _ELAPSED_TIME).count() >= 1000.0)																																								\
{																																																						\
D_DEBUG_LOG(eLogType::D_LOG_TYPE15, "Profiler ( %s ) : %f (ms/s)", MAKE_STRING(PROFILING_TAG), CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME).count() / static_cast<FLOAT64>(CONCAT(PROFILING_TAG, _EXECUTE_COUNT)) );		\
CONCAT(PROFILING_TAG, _ELAPSED_TIME) = std::chrono::duration<FLOAT64, std::milli>::zero();																																\
CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) = std::chrono::duration<FLOAT64, std::milli>::zero();																														\
CONCAT(PROFILING_TAG, _EXECUTE_COUNT) = 0;																																												\
}																																																						\

#endif


#if ( defined(DEBUG_MODE) || defined(ALWAYS_PROFILING) )

#ifndef D_START_PROFILING
#define D_START_PROFILING(PROFILING_TAG, LAYER) D_START_PROFILING_INTERNAL(PROFILING_TAG)
#endif

#ifndef D_END_PROFILING
#define D_END_PROFILING(PROFILING_TAG) D_END_PROFILING_INTERNAL(PROFILING_TAG)
#endif

#else

#ifndef D_START_PROFILING
#define D_START_PROFILING(name, layer)
#endif

#ifndef D_END_PROFILING
#define D_END_PROFILING(name)
#endif

#endif




#ifndef D_START_PROFILING_IN_RELEASE

#define D_START_PROFILING_IN_RELEASE(PROFILING_TAG) D_START_PROFILING_INTERNAL(PROFILING_TAG)																																																			\
																																																					
#endif

#ifndef D_END_PROFILING_IN_RELEASE

#define D_END_PROFILING_IN_RELEASE(PROFILING_TAG) D_END_PROFILING_INTERNAL(PROFILING_TAG)																																																			\

#endif

