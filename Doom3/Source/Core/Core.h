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
#define CURRENTPATH /Users/sungjinkang/openglstudy/glfwStudys/


#endif

#else

#endif

#define GET_RELATIVE_PATH(x) CURRENTPATH x

#define ASSET_FOLDER_DIRECTORY GET_RELATIVE_PATH("Assets/")



#include "Log/Logger.h"
#ifdef DEBUG_MODE
#define DEBUG_LOG(...)  Doom::Logger.Log(##__VA_ARGS__)
#else
#define DEBUG_LOG(...)
#endif



#ifndef DEBUG_MODE // if not debug mode, don't throw assert
#define NDEBUG 
#endif
#include <cassert>

#ifndef NDEBUG
#define D_ASSERT(condition) assert(condition)
#endif
/*
#ifndef NDEBUG
#   define D_ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif
*/