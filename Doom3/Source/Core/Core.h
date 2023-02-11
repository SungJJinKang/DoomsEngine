#pragma once

#include "CompilerMacros.h"

// Never include HEAVY header.
// SEPERATE codes included in Core.h with implemation codes( use MACRO_IMPLEMENTATION for this )
// Use Forward declaration.
// And Define implemations in MACRO_IMPLEMENTATION

#include <Macros/Macros.h>

#include <DObject/DObjectHeaders.h>
#include <Reflection/Reflection.h>
#include <ConfigurationValue/ConfigurationValue.h>

#include <ResourceManagement/Thread/ThreadGlobal.h>