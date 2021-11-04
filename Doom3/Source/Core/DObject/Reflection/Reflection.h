#pragma once

#ifndef REFLECTION_ENABLED
#define REFLECTION_ENABLED
#endif

#ifdef REFLECTION_ENABLED



#include "clReflect_automation/clReflect/inc/clcpp/clcpp.h"

#ifndef D_NAMESPACE
#define D_NAMESPACE clcpp_attr(reflect_part)
#endif

#ifndef D_CLASS
#define D_CLASS clcpp_attr(reflect_part)
#endif

#ifndef D_STRUCT
#define D_STRUCT clcpp_attr(reflect_part)
#endif

#ifndef D_ENUM
#define D_ENUM clcpp_attr(reflect_part)
#endif

#ifndef D_PROPERTY
#define D_PROPERTY(...) clcpp_attr(reflect)
#endif

#ifndef D_FUNCTION
#define D_FUNCTION(...) clcpp_attr(reflect)
#endif



#else



#ifndef D_NAMESPACE
#define D_NAMESPACE
#endif

#ifndef D_CLASS
#define D_CLASS(...)
#endif

#ifndef D_STRUCT
#define D_STRUCT(...)
#endif

#ifndef D_ENUM
#define D_ENUM(...)
#endif

#ifndef D_PROPERTY
#define D_PROPERTY(...)
#endif

#ifndef D_FUNCTION
#define D_FUNCTION(...)
#endif



#endif
