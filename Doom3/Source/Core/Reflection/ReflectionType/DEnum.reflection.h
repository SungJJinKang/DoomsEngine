#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Reflection\ReflectionType\DEnum.cpp


#ifdef _Source_Core_Reflection_ReflectionType_DEnum_reflection_h

#error "_Source_Core_Reflection_ReflectionType_DEnum_reflection_h already included, missing '#pragma once' in _Source_Core_Reflection_ReflectionType_DEnum_reflection_h"

#endif

#define _Source_Core_Reflection_ReflectionType_DEnum_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__reflection__DEnum
#error "GENERATE_BODY_FULLNAME_dooms__reflection__DEnum already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__reflection__DEnum
#define CURRENT_TYPE_ALIAS_dooms__reflection__DEnum \
public : \
typedef dooms::reflection::DEnum Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__reflection__DEnum
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__reflection__DEnum \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 971348217; \
inline static const char* const TYPE_FULL_NAME = "dooms::reflection::DEnum"; \
inline static const char* const TYPE_SHORT_NAME = "DEnum"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_DEnum
#define TYPE_CHECK_FUNCTION_DEnum \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__reflection__DEnum
#define GENERATE_BODY_FULLNAME_dooms__reflection__DEnum(...) \
CURRENT_TYPE_ALIAS_dooms__reflection__DEnum \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__reflection__DEnum \
TYPE_CHECK_FUNCTION_DEnum \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DEnum(...) GENERATE_BODY_FULLNAME_dooms__reflection__DEnum(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__reflection__DEnum(__VA_ARGS__)


//-------------------------------------------


