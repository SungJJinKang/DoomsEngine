#pragma once
#include <string>

std::string _GetCurrentPath(const char* additional);

#ifdef DEBUG_MODE

#if defined(_WIN32) || defined(_WIN64)

#ifndef CURRENTPATH
#define CURRENTPATH _GetCurrentPath(nullptr)
#endif

#elif __APPLE__

#ifndef CURRENTPATH
#define CURRENTPATH _GetCurrentPath(nullptr)
#endif

#endif

#else
#endif

#ifndef GET_RELATIVE_PATH
#define GET_RELATIVE_PATH(x) _GetCurrentPath(x)
#endif

#ifndef ASSET_FOLDER_DIRECTORY
#define ASSET_FOLDER_DIRECTORY GET_RELATIVE_PATH("Assets/")
#endif