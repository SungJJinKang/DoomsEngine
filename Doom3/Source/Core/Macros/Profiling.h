#pragma once

#include <CompilerMacros.h>
#include "MacrosHelper.h"

#include <iostream>
#include <chrono>

// std::chrono::high_resolution_clock::now() has more resolution than OS GetTickCount API 
#ifndef D_START_PROFILING_INTERNAL

#define D_START_PROFILING_INTERNAL(PROFILING_TAG)											\
																							\
const auto CONCAT(PROFILING_TAG, _START) = std::chrono::high_resolution_clock::now();		\

#endif

#ifndef D_END_PROFILING_INTERNAL

#define D_END_PROFILING_INTERNAL(PROFILING_TAG, layer)																														\
																																											\
const auto CONCAT(PROFILING_TAG, _END) = std::chrono::high_resolution_clock::now();																							\
std::cout << "Profiler ( " MAKE_STRING(PROFILING_TAG) << " ) : " << ( CONCAT(PROFILING_TAG, _END) - CONCAT(PROFILING_TAG, _START) ).count() << " (ms)" << std::endl;		\

#endif



#ifndef D_START_PROFILING_PER_SECOND_INTERNAL

#define D_START_PROFILING_PER_SECOND_INTERNAL(PROFILING_TAG)										\
																									\
const auto CONCAT(PROFILING_TAG, _CURRENT_TICK_TIME) = std::chrono::high_resolution_clock::now();	\
const auto CONCAT(PROFILING_TAG, _START) = CONCAT(PROFILING_TAG, _CURRENT_TICK_TIME);				\

#endif

#ifndef D_END_PROFILING_PER_SECOND_INTERNAL

#define D_END_PROFILING_PER_SECOND_INTERNAL(PROFILING_TAG, layer)																																							\
const auto CONCAT(PROFILING_TAG, _END) = std::chrono::high_resolution_clock::now();																																			\
static std::chrono::duration<double, std::milli> CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) = std::chrono::duration<double, std::milli>::zero();																			\
CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) += std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(CONCAT(PROFILING_TAG, _END) - CONCAT(PROFILING_TAG, _START));											\
																																																							\
static auto CONCAT(PROFILING_TAG, _EX_TICK_TIME) = std::chrono::high_resolution_clock::now();																																\
static std::chrono::duration<double, std::milli> CONCAT(PROFILING_TAG, _ELAPSED_TIME) = std::chrono::duration<double, std::milli>::zero();																					\
CONCAT(PROFILING_TAG, _ELAPSED_TIME) += std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(CONCAT(PROFILING_TAG, _CURRENT_TICK_TIME) - CONCAT(PROFILING_TAG, _EX_TICK_TIME));							\
CONCAT(PROFILING_TAG, _EX_TICK_TIME) = CONCAT(PROFILING_TAG, _CURRENT_TICK_TIME);																																			\
if (CONCAT(PROFILING_TAG, _ELAPSED_TIME).count() >= 1000.0)																																									\
{																																																							\
std::cout << "Profiler ( " MAKE_STRING(PROFILING_TAG) << " ) : " << (CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME).count() / (CONCAT(PROFILING_TAG, _ELAPSED_TIME).count() / 1000.0)) << " (ms/s)" << std::endl;				\
CONCAT(PROFILING_TAG, _ELAPSED_TIME) = std::chrono::duration<double, std::milli>::zero();																																	\
CONCAT(PROFILING_TAG, _PROFILE_ELAPSED_TIME) = std::chrono::duration<double, std::milli>::zero();																															\
}

#endif


#ifdef DEBUG_MODE

#ifndef D_START_PROFILING
#define D_START_PROFILING(PROFILING_TAG) D_START_PROFILING_INTERNAL(PROFILING_TAG)
#endif

#ifndef D_END_PROFILING
#define D_END_PROFILING(PROFILING_TAG) D_END_PROFILING_INTERNAL(PROFILING_TAG)
#endif

#ifndef D_START_PROFILING_PER_SECOND
#define D_START_PROFILING_PER_SECOND(PROFILING_TAG) D_START_PROFILING_PER_SECOND_INTERNAL(PROFILING_TAG)
#endif

#ifndef D_END_PROFILING_PER_SECOND
#define D_END_PROFILING_PER_SECOND(PROFILING_TAG) D_END_PROFILING_PER_SECOND_INTERNAL(PROFILING_TAG)
#endif

#else

#ifndef D_START_PROFILING
#define D_START_PROFILING(name, layer)
#endif

#ifndef D_END_PROFILING
#define D_END_PROFILING(name)
#endif

#ifndef D_START_PROFILING_PER_SECOND
#define D_START_PROFILING_PER_SECOND(PROFILING_TAG)
#endif

#ifndef D_END_PROFILING_PER_SECOND
#define D_END_PROFILING_PER_SECOND(PROFILING_TAG)
#endif

#endif




#ifndef D_START_PROFILING_IN_RELEASE

#define D_START_PROFILING_IN_RELEASE(PROFILING_TAG) D_START_PROFILING_INTERNAL(PROFILING_TAG)																																																			\
																																																					
#endif

#ifndef D_END_PROFILING_IN_RELEASE

#define D_END_PROFILING_IN_RELEASE(PROFILING_TAG) D_END_PROFILING_INTERNAL(PROFILING_TAG)																																																			\

#endif


#ifndef D_START_PROFILING_PER_SECOND_IN_RELEASE

#define D_START_PROFILING_PER_SECOND_IN_RELEASE(PROFILING_TAG) D_START_PROFILING_PER_SECOND_INTERNAL(PROFILING_TAG)																																																			\

#endif

#ifndef D_END_PROFILING_PER_SECOND_IN_RELEASE

#define D_END_PROFILING_PER_SECOND_IN_RELEASE(PROFILING_TAG) D_END_PROFILING_PER_SECOND_INTERNAL(PROFILING_TAG)																																																			\

#endif