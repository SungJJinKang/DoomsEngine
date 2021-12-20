#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_Reflection_ReflectionType_DAttributeList_reflection_h


#ifdef __Source_Core_Reflection_ReflectionType_DAttributeList_reflection_h

#error "__Source_Core_Reflection_ReflectionType_DAttributeList_reflection_h already included, missing '#pragma once' in __Source_Core_Reflection_ReflectionType_DAttributeList_reflection_h"

#endif

#define __Source_Core_Reflection_ReflectionType_DAttributeList_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__reflection__DAttributeList
#error "GENERATE_BODY_FULLNAME_dooms__reflection__DAttributeList already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__reflection__DAttributeList
#define CURRENT_TYPE_ALIAS_dooms__reflection__DAttributeList \
public : \
typedef dooms::reflection::DAttributeList Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__reflection__DAttributeList
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__reflection__DAttributeList \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2390386979; \
inline static const char* const TYPE_FULL_NAME = "dooms::reflection::DAttributeList"; \
inline static const char* const TYPE_SHORT_NAME = "DAttributeList"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_DAttributeList
#define TYPE_CHECK_FUNCTION_DAttributeList \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__reflection__DAttributeList
#define GENERATE_BODY_FULLNAME_dooms__reflection__DAttributeList(...) \
CURRENT_TYPE_ALIAS_dooms__reflection__DAttributeList \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__reflection__DAttributeList \
TYPE_CHECK_FUNCTION_DAttributeList \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DAttributeList(...) GENERATE_BODY_FULLNAME_dooms__reflection__DAttributeList(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__reflection__DAttributeList(__VA_ARGS__)


//-------------------------------------------


