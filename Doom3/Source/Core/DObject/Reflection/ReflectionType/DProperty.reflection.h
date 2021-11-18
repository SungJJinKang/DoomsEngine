#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\DObject\Reflection\ReflectionType\DProperty.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_DObject_Reflection_ReflectionType_DProperty_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\DObject\Reflection\ReflectionType\DProperty.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\DObject\Reflection\ReflectionType\DProperty.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_DObject_Reflection_ReflectionType_DProperty_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__DProperty
#error "GENERATE_BODY_FULLNAME_dooms__DProperty already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__DProperty
#define CURRENT_TYPE_ALIAS_dooms__DProperty \
public : \
typedef dooms::DProperty Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DProperty
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DProperty \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3583092198; \
inline static const char* const TYPE_FULL_NAME = "dooms::DProperty"; \
inline static const char* const TYPE_SHORT_NAME = "DProperty"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_DProperty
#define TYPE_CHECK_FUNCTION_DProperty \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__DProperty
#define GENERATE_BODY_FULLNAME_dooms__DProperty(...) \
CURRENT_TYPE_ALIAS_dooms__DProperty \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DProperty \
TYPE_CHECK_FUNCTION_DProperty \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DProperty(...) GENERATE_BODY_FULLNAME_dooms__DProperty(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__DProperty(__VA_ARGS__)


//-------------------------------------------


