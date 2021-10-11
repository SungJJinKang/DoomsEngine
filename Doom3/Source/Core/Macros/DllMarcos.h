#pragma once

#include <CompilerMacros.h>


#define DISABLE_DLL_PROCESS


#ifndef DISABLE_DLL_PROCESS

#ifdef  DOOM_DLL_EXPORTS 

#define DOOM_API __declspec(dllexport)  
#define EXPORT_IMP_TEMPLATE

#else

#define DOOM_API __declspec(dllimport)  
#define EXPORT_IMP_TEMPLATE extern

#endif

#else

#define DOOM_API
#define EXPORT_IMP_TEMPLATE

#endif