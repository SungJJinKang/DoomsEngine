#pragma once
#include <string>

std::string _GetCurrentPath(const char* additional);

#ifdef DEBUG_MODE

#if defined(_WIN32) || defined(_WIN64)
#define CURRENTPATH _GetCurrentPath(nullptr)
#elif __APPLE__
#define CURRENTPATH _GetCurrentPath(nullptr)
#endif

#else
#endif

#define GET_RELATIVE_PATH(x) _GetCurrentPath(x)

#define ASSET_FOLDER_DIRECTORY GET_RELATIVE_PATH("Assets/")