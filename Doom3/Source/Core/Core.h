#pragma once


#ifdef _DEBUG
#define DEBUG_MODE
#else
#define BUILD_MODE
#endif

#ifdef DEBUG_MODE

#if defined(_WIN32) || defined(_WIN64)
#define CURRENTPATH "C:/Doom3FromScratch/Doom3/"

#elif __APPLE__
#define CURRENTPATH "/Users/sungjinkang/openglstudy/glfwStudys/"


#endif

#else

#endif

#define  GET_RALATIVE_PATH(path) CURRENTPATH path
#include "Assert.h"



#include "Log/Logger.h"
#ifdef DEBUG_MODE
#define DEBUG_LOG(...)  Doom::Logger.Log(##__VA_ARGS__)
#else
#define DEBUG_LOG(...)
#endif