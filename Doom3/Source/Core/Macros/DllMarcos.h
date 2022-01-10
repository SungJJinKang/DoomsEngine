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


//////////////////

#ifdef  DOOMS_ENGINE_DLL_EXPORT 
/*Enabled as "export" while compiling the dll project*/
#define DOOMS_ENGINE __declspec(dllexport)  
#else
/*Enabled as "import" in the Client side for using already created dll file*/
#define DOOMS_ENGINE __declspec(dllimport)  
#endif

