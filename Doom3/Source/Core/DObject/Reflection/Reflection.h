#pragma once

#include "TypeDef.h"

#ifndef REFLECTION_ENABLED
#define REFLECTION_ENABLED
#endif

#if defined(REFLECTION_ENABLED)
#include "clReflect_automation/clReflect/inc/clcpp/clcpp.h"
#endif



#if defined(REFLECTION_ENABLED) && defined(__clcpp_parse__)

clcpp_reflect(int8_t);
clcpp_reflect(int16_t);
clcpp_reflect(int32_t);
clcpp_reflect(int64_t);
clcpp_reflect(INT32);
clcpp_reflect(uint8_t);
clcpp_reflect(uint16_t);
clcpp_reflect(uint32_t);
clcpp_reflect(uint64_t);
clcpp_reflect(intptr_t);
clcpp_reflect(uintptr_t);
clcpp_reflect(float);
clcpp_reflect(double);
clcpp_reflect(double);
clcpp_reflect(const char* const* const)
clcpp_reflect(const char* const*)
clcpp_reflect(const char* const)
clcpp_reflect(const char*)
clcpp_reflect(const char)
clcpp_reflect(char)
clcpp_reflect(char*)
clcpp_reflect(const char**)
clcpp_reflect(char**)
clcpp_reflect(std::unique_ptr)
clcpp_reflect(std::unique_ptr<uint32_t[]>)
clcpp_reflect(uint32_t[])
clcpp_reflect(std::string)
clcpp_reflect(std::vector)
clcpp_reflect(std::unordered_map)
clcpp_reflect(std::map)
clcpp_reflect(std::set)

#ifndef D_NAMESPACE
#define D_NAMESPACE(NAMESPACE_NAME) clcpp_reflect_part(NAMESPACE_NAME)
#endif

#ifndef D_CLASS
#define D_CLASS clcpp_attr(reflect_part)
#endif

#ifndef D_STRUCT
#define D_STRUCT clcpp_attr(reflect_part)
#endif

#ifndef D_ENUM
#define D_ENUM clcpp_attr(reflect)
#endif

#ifndef D_PROPERTY
#define D_PROPERTY(...) clcpp_attr(reflect)
#endif

#ifndef D_FUNCTION
#define D_FUNCTION(...) clcpp_attr(reflect)
#endif

#ifndef D_REFLECTION_TYPE
#define D_REFLECTION_TYPE(TYPE_NAME) clcpp_reflect_part(TYPE_NAME)
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
#define D_REFLECTION_TYPE(...)
#endif

#endif
