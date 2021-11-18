#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Reflection\ReflectionType\DField.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Reflection_ReflectionType_DField_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Reflection\ReflectionType\DField.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Reflection\ReflectionType\DField.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Reflection_ReflectionType_DField_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__DField
#error "GENERATE_BODY_FULLNAME_dooms__DField already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__DField
#define CURRENT_TYPE_ALIAS_dooms__DField \
public : \
typedef dooms::DField Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DField
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DField \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1273923552; \
inline static const char* const TYPE_FULL_NAME = "dooms::DField"; \
inline static const char* const TYPE_SHORT_NAME = "DField"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_DField
#define TYPE_CHECK_FUNCTION_DField \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__DField
#define GENERATE_BODY_FULLNAME_dooms__DField(...) \
CURRENT_TYPE_ALIAS_dooms__DField \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DField \
TYPE_CHECK_FUNCTION_DField \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DField(...) GENERATE_BODY_FULLNAME_dooms__DField(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__DField(__VA_ARGS__)


//-------------------------------------------


