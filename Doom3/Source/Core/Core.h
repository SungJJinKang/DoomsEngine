#pragma once


#ifdef _DEBUG
#define DEBUG_MODE
#else
#define BUILD_MODE
#endif



// Never include HEAVY header.
// SEPERATE codes included in Core.h with implemation codes( use MACRO_IMPLEMENTATION for this )
// Use Forward declaration.
// And Define implemations in MACRO_IMPLEMENTATION

#include "Macros/Macros.h"
#include "../Helper/Singleton.h"
