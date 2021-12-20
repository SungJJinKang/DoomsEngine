#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Reflection\ReflectionType\DType.cpp


#ifdef _Source_Core_Reflection_ReflectionType_DType_reflection_h

#error "_Source_Core_Reflection_ReflectionType_DType_reflection_h already included, missing '#pragma once' in _Source_Core_Reflection_ReflectionType_DType_reflection_h"

#endif

#define _Source_Core_Reflection_ReflectionType_DType_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__reflection__DType
#error "GENERATE_BODY_FULLNAME_dooms__reflection__DType already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__reflection__DType
#define CURRENT_TYPE_ALIAS_dooms__reflection__DType \
public : \
typedef dooms::reflection::DType Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__reflection__DType
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__reflection__DType \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 159154334; \
inline static const char* const TYPE_FULL_NAME = "dooms::reflection::DType"; \
inline static const char* const TYPE_SHORT_NAME = "DType"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_DType
#define TYPE_CHECK_FUNCTION_DType \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__reflection__DType
#define GENERATE_BODY_FULLNAME_dooms__reflection__DType(...) \
CURRENT_TYPE_ALIAS_dooms__reflection__DType \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__reflection__DType \
TYPE_CHECK_FUNCTION_DType \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DType(...) GENERATE_BODY_FULLNAME_dooms__reflection__DType(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__reflection__DType(__VA_ARGS__)


//-------------------------------------------


