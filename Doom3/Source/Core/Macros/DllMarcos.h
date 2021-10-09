#pragma once

#define DISABLE_DLL_PROCESS


#ifndef DISABLE_DLL_PROCESS

#ifdef  DOOM_DLL_EXPORTS 

#define DOOM_API __declspec(dllexport)  
#define EXPIMP_TEMPLATE

#else

#define DOOM_API __declspec(dllimport)  
#define EXPIMP_TEMPLATE extern

#endif

#else

#define DOOM_API
#define EXPIMP_TEMPLATE

#endif