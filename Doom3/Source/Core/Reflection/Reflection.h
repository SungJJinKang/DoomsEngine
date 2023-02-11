#pragma once

#include "CompilerMacros.h"
#include "TypeDef.h"

#ifndef REFLECTION_ENABLED
#define REFLECTION_ENABLED 1
#endif

#if REFLECTION_ENABLED
#include "clReflect_automation/clReflect/inc/clcpp/clcpp.h"
#endif

#if REFLECTION_ENABLED

#ifndef GENERATE_REFLECTION_DATA
#define GENERATE_REFLECTION_DATA 1
#endif

#else

#define GENERATE_REFLECTION_DATA 0

#endif
// Flag : Invisible

//TODO : Support flag attribute macros for imgui option 
#if (REFLECTION_ENABLED && defined(__clcpp_parse__))

#ifndef D_NAMESPACE
#define D_NAMESPACE(NAMESPACE_NAME) clcpp_reflect_part(NAMESPACE_NAME)
#endif

// TODO : SUPPORT Attribute for class
#ifndef D_CLASS
#define D_CLASS clcpp_attr(reflect_part)
#endif

// TODO : SUPPORT Attribute for struct
#ifndef D_STRUCT
#define D_STRUCT clcpp_attr(reflect_part)
#endif

// TODO : SUPPORT Attribute for enum
#ifndef D_ENUM
#define D_ENUM clcpp_attr(reflect)
#endif

#ifndef D_PROPERTY
#define D_PROPERTY(...) clcpp_attr(reflect, ##__VA_ARGS__)
#endif

#ifndef D_FUNCTION
#define D_FUNCTION(...) clcpp_attr(reflect, ##__VA_ARGS__)
#endif

#ifndef D_REFLECTION_TYPE
#define D_REFLECTION_TYPE(TYPE_NAME) clcpp_reflect_part(TYPE_NAME)
#endif

#ifndef D_REFLECT_ALL
#define D_REFLECT_ALL(TYPE_NAME) clcpp_reflect(TYPE_NAME)
#endif

#else



#ifndef D_NAMESPACE
#define D_NAMESPACE(...)
#endif

#ifndef D_CLASS
#define D_CLASS
#endif

#ifndef D_STRUCT
#define D_STRUCT
#endif

#ifndef D_ENUM
#define D_ENUM
#endif

#ifndef D_PROPERTY
#define D_PROPERTY(...)
#endif

#ifndef D_FUNCTION
#define D_FUNCTION(...)
#endif

#ifndef D_REFLECTION_TYPE
#define D_REFLECTION_TYPE(X)
#endif

#ifndef D_REFLECT_ALL
#define D_REFLECT_ALL(X)
#endif

#endif

#include "ReflectionPredefined.h"

