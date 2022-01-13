#pragma once

#include <CompilerMacros.h>

#if defined(_WIN32) && !defined(DOOMS_ENGINE_API_ENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#define DOOMS_ENGINE_API_ENTRY __stdcall
#endif

#ifndef DOOMS_ENGINE_API_ENTRY
#define DOOMS_ENGINE_API_ENTRY
#endif
#ifndef DOOMS_ENGINE_API_ENTRY_P
#define DOOMS_ENGINE_API_ENTRY_P DOOMS_ENGINE_API_ENTRY *
#endif

#ifndef GRAPHICS_API_ENTRY
#define GRAPHICS_API_ENTRY DOOMS_ENGINE_API_ENTRY
#endif

#ifdef DOOMS_ENGINE_DLL_EXPORT


#ifndef DOOMS_ENGINE_GRAPHICS_API
#define DOOMS_ENGINE_GRAPHICS_API extern "C" DOOMS_ENGINE extern
#endif

#else

// This is for easy development
// API function pointers isn't used from graphis api dll.
#ifndef DOOMS_ENGINE_GRAPHICS_API
#define DOOMS_ENGINE_GRAPHICS_API extern
#endif

#endif