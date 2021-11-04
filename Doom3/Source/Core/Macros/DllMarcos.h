#pragma once

#include <CompilerMacros.h>

#include <DObject/Reflection/Reflection.h>

#define DISABLE_DLL_PROCESS


#ifndef DISABLE_DLL_PROCESS

#ifdef  DOOM_DLL_EXPORTS 

#define DOOM_API __declspec(dllexport) D_CLASS  
#define EXPORT_IMP_TEMPLATE

#else

#define DOOM_API __declspec(dllimport) D_CLASS   
#define EXPORT_IMP_TEMPLATE extern

#endif

#else

#define DOOM_API D_CLASS
#define EXPORT_IMP_TEMPLATE

#endif