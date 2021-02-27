#pragma once


#ifdef _DEBUG
#define DEBUG_MODE
#else
#define RELEASE_MODE
#endif

#ifdef _WIN64 // Only WIn 64
#define WINDOW64

#elif _WIN32 // Win 32 And Win 64
#define WINDOW32

#elif __APPLE__
#define APPLE

#elif __ANDROID__
#define ANDROID
#endif


// Never include HEAVY header.
// SEPERATE codes included in Core.h with implemation codes( use MACRO_IMPLEMENTATION for this )
// Use Forward declaration.
// And Define implemations in MACRO_IMPLEMENTATION

#include "Macros/Macros.h"
#include "../Helper/Singleton.h"


