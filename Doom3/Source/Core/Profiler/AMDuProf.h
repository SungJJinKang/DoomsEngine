#pragma once

#include <Core.h>

#ifdef RELEASE_MODE
//#define D_DEBUG_AMD_U_PROF
#endif

#ifdef D_DEBUG_AMD_U_PROF

#include <AMDProfileController.h>

#ifndef CPU_VENDOR_PROFILER_RESUME
#define CPU_VENDOR_PROFILER_RESUME amdProfileResume(AMD_PROFILE_CPU)
#endif


#ifndef CPU_VENDOR_PROFILER_PAUSE
#define CPU_VENDOR_PROFILER_PAUSE amdProfilePause(AMD_PROFILE_CPU)
#endif


#else


#ifndef CPU_VENDOR_PROFILER_RESUME
#define CPU_VENDOR_PROFILER_RESUME
#endif

#ifndef CPU_VENDOR_PROFILER_PAUSE
#define CPU_VENDOR_PROFILER_PAUSE
#endif


#endif