#pragma once

#ifdef  DOOMS_ENGINE_DLL_EXPORT 
/*Enabled as "export" while compiling the dll project*/
#define DOOMS_ENGINE __declspec(dllexport)  
#else
/*Enabled as "import" in the Client side for using already created dll file*/
#define DOOMS_ENGINE __declspec(dllimport)  
#endif

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

#ifndef DOOMS_ENGINE_GRAPHICS_API
#define DOOMS_ENGINE_GRAPHICS_API extern "C" DOOMS_ENGINE extern
#endif