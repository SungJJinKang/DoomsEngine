#pragma once


/*
* HOW TO USE D_START_PROFILING, D_END_PROFILING
*
* void function()
* {
*
*	~~~~~~~
*
* }
*
* vod main()
* {
*
*	function();
*
* }
*
*
* BAD :
*
* void function()
* {
*	D_START_PROFILING("Function");
*	~~~~~~~ HEAVY WORKS ~~~~~~~
*	D_END_PROFILING("Function");
* }
*
* vod main()
* {
*	function();
* }
*
*
* GOOD :
*
* void function()
* {
*
*	~~~~~~~ HEAVY WORKS ~~~~~~~
*
* }
*
* vod main()
* {
*	D_START_PROFILING("Function");
*	function();
*	D_END_PROFILING("Function");
* }
*/

#define DISABLE_PROFILING
#ifdef RELEASE_MODE
#define DISABLE_PROFILING
#endif

#if defined(DEBUG_MODE) && !defined(DISABLE_PROFILING)
#include "../Profiler/Profiler.h"
#define D_START_PROFILING(name, layer) doom::profiler::StartProfiling(name, layer)
#define D_END_PROFILING(name) doom::profiler::EndProfiling(name)
#else
#define D_START_PROFILING(name, layer)
#define D_END_PROFILING(name)
#endif
