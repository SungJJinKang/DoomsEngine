#pragma once

//Legacy
#ifdef DOOMS_DLL

#ifdef  DOOM_DLL_EXPORTS 

#define DOOM_API __declspec(dllexport)  

#else

#define DOOM_API __declspec(dllimport)   

#endif

#else

#define DOOM_API
#define EXPORT_IMP_TEMPLATE

#endif
//Legacy
