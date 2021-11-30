#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Reflection\ReflectionType\DTemplateArgumentType.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Reflection_ReflectionType_DTemplateArgumentType_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Reflection\ReflectionType\DTemplateArgumentType.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Reflection\ReflectionType\DTemplateArgumentType.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Reflection_ReflectionType_DTemplateArgumentType_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__reflection__DTemplateArgumentType
#error "GENERATE_BODY_FULLNAME_dooms__reflection__DTemplateArgumentType already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__reflection__DTemplateArgumentType
#define CURRENT_TYPE_ALIAS_dooms__reflection__DTemplateArgumentType \
public : \
typedef dooms::reflection::DTemplateArgumentType Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__reflection__DTemplateArgumentType
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__reflection__DTemplateArgumentType \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1193788451; \
inline static const char* const TYPE_FULL_NAME = "dooms::reflection::DTemplateArgumentType"; \
inline static const char* const TYPE_SHORT_NAME = "DTemplateArgumentType"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_DTemplateArgumentType
#define TYPE_CHECK_FUNCTION_DTemplateArgumentType \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__reflection__DTemplateArgumentType
#define GENERATE_BODY_FULLNAME_dooms__reflection__DTemplateArgumentType(...) \
CURRENT_TYPE_ALIAS_dooms__reflection__DTemplateArgumentType \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__reflection__DTemplateArgumentType \
TYPE_CHECK_FUNCTION_DTemplateArgumentType \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DTemplateArgumentType(...) GENERATE_BODY_FULLNAME_dooms__reflection__DTemplateArgumentType(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__reflection__DTemplateArgumentType(__VA_ARGS__)


//-------------------------------------------


