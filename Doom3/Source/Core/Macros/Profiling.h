#pragma once

#include <CompilerMacros.h>
#include "MacrosHelper.h"

#include <iostream>
#include <chrono>

#ifndef ALWAYS_PROFILING
#define ALWAYS_PROFILING
#endif

// std::chrono::high_resolution_clock::now() has more resolution than OS GetTickCount API 

#ifndef D_START_PROFILING_INTERNAL

#define D_START_PROFILING_INTERNAL(PROFILING_TAG)													\
																									\
const auto CONCAT(PROFILING_TAG, _START) = std::chrono::high_resolution_clock::now();				\
static unsigned int CONCAT(PROFILING_TAG, _EXECUTE_COUNT) = 0										\

#endif

#ifndef D_END_PROFILING_INTERNAL

#define D_END_PROFILING_INTERNAL(PROFILING_TAG)																																									\
const auto CONCAT(PROFILING_TAG, _END) = std::chrono::high_resolution_clock::now();																																		\
static std::chrono::duration<double, std::milli> CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) = std::chrono::duration<double, std::milli>::zero();																		\
CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) += std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(CONCAT(PROFILING_TAG, _END) - CONCAT(PROFILING_TAG, _START));										\
																																																						\
static auto CONCAT(PROFILING_TAG, _EX_TICK_TIME) = std::chrono::high_resolution_clock::now();																															\
static std::chrono::duration<double, std::milli> CONCAT(PROFILING_TAG, _ELAPSED_TIME) = std::chrono::duration<double, std::milli>::zero();																				\
CONCAT(PROFILING_TAG, _ELAPSED_TIME) += std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(CONCAT(PROFILING_TAG, _END) - CONCAT(PROFILING_TAG, _EX_TICK_TIME));										\
CONCAT(PROFILING_TAG, _EX_TICK_TIME) = CONCAT(PROFILING_TAG, _END);																																						\
CONCAT(PROFILING_TAG, _EXECUTE_COUNT)++;																																												\
if (CONCAT(PROFILING_TAG, _ELAPSED_TIME).count() >= 1000.0)																																								\
{																																																						\
std::cout << "Profiler ( " MAKE_STRING(PROFILING_TAG) << " ) : " << ( CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME).count() / static_cast<double>(CONCAT(PROFILING_TAG, _EXECUTE_COUNT))) << " (ms/s)" << std::endl;		\
CONCAT(PROFILING_TAG, _ELAPSED_TIME) = std::chrono::duration<double, std::milli>::zero();																																\
CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) = std::chrono::duration<double, std::milli>::zero();																														\
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

