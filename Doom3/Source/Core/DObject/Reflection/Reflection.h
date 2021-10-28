#pragma once

#ifndef REFLECTION_ENABLED
#define REFLECTION_ENABLED
#endif

#ifdef REFLECTION_ENABLED
#include "clReflect/inc/clcpp/clcpp.h"

#ifndef DOBJECT_REFLECTIONS
#define DOBJECT_REFLECTIONS(X) clcpp_reflect(X)
#endif

#else

#ifndef DOBJECT_REFLECTIONS
#define DOBJECT_REFLECTIONS(X)
#endif

#endif
