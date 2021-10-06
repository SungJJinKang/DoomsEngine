#pragma once


#ifdef _DEBUG
#define DEBUG_MODE
#else
#define RELEASE_MODE
#endif



// Never include HEAVY header.
// SEPERATE codes included in Core.h with implemation codes( use MACRO_IMPLEMENTATION for this )
// Use Forward declaration.
// And Define implemations in MACRO_IMPLEMENTATION

#include "Macros/Macros.h"

#include <DObject/DObject.h>
#include <DObject/DObjectManager.h>
#include <DObject/DObjectGlobals.h>



#include "../Helper/Simple_SingleTon/Singleton.h"




