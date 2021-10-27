#pragma once

#ifndef REFLECTION_ENABLED
#define REFLECTION_ENABLED
#endif

#ifdef REFLECTION_ENABLED
#include "Reflection/clReflect/inc/clcpp/clcpp.h"

#ifndef DOBJECT_REFLECTIONS
#define DOBJECT_REFLECTIONS(X) clcpp_reflect(X)
#endif

#else

#ifndef DOBJECT_REFLECTIONS
#define DOBJECT_REFLECTIONS(X)
#endif

#endif

DOBJECT_REFLECTIONS(doom)
namespace doom
{
	
}

#include <DObject/DObject.h>
#include <DObject/DObjectManager.h>
#include <DObject/DObjectGlobals.h>
#include <DObject/DObjectMacros.h>
#include <DObject/DClass.h>
#include <DObject/TSubclassOf.h>