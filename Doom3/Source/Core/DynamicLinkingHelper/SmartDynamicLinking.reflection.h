#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\DynamicLinkingHelper\SmartDynamicLinking.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_DynamicLinkingHelper_SmartDynamicLinking_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\DynamicLinkingHelper\SmartDynamicLinking.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\DynamicLinkingHelper\SmartDynamicLinking.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_DynamicLinkingHelper_SmartDynamicLinking_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__DynamicLinkingLibrary
#error "GENERATE_BODY_FULLNAME_dooms__DynamicLinkingLibrary already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__DynamicLinkingLibrary
#define CURRENT_TYPE_ALIAS_dooms__DynamicLinkingLibrary \
typedef dooms::DynamicLinkingLibrary Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DynamicLinkingLibrary
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DynamicLinkingLibrary \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3427236552; \
inline static const char* const TYPE_FULL_NAME = "dooms::DynamicLinkingLibrary"; \
inline static const char* const TYPE_SHORT_NAME = "DynamicLinkingLibrary"; \


#undef TYPE_CHECK_FUNCTION_DynamicLinkingLibrary
#define TYPE_CHECK_FUNCTION_DynamicLinkingLibrary \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__DynamicLinkingLibrary
#define GENERATE_BODY_FULLNAME_dooms__DynamicLinkingLibrary(...) \
CURRENT_TYPE_ALIAS_dooms__DynamicLinkingLibrary \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DynamicLinkingLibrary \
TYPE_CHECK_FUNCTION_DynamicLinkingLibrary \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DynamicLinkingLibrary(...) GENERATE_BODY_FULLNAME_dooms__DynamicLinkingLibrary(__VA_ARGS__)


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__SmartDynamicLinking
#error "GENERATE_BODY_FULLNAME_dooms__SmartDynamicLinking already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__SmartDynamicLinking
#define CURRENT_TYPE_ALIAS_dooms__SmartDynamicLinking \
public : \
typedef dooms::SmartDynamicLinking Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__SmartDynamicLinking
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__SmartDynamicLinking \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 100502829; \
inline static const char* const TYPE_FULL_NAME = "dooms::SmartDynamicLinking"; \
inline static const char* const TYPE_SHORT_NAME = "SmartDynamicLinking"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_SmartDynamicLinking
#define TYPE_CHECK_FUNCTION_SmartDynamicLinking \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__SmartDynamicLinking
#define GENERATE_BODY_FULLNAME_dooms__SmartDynamicLinking(...) \
CURRENT_TYPE_ALIAS_dooms__SmartDynamicLinking \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__SmartDynamicLinking \
TYPE_CHECK_FUNCTION_SmartDynamicLinking \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_SmartDynamicLinking(...) GENERATE_BODY_FULLNAME_dooms__SmartDynamicLinking(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__SmartDynamicLinking(__VA_ARGS__)


//-------------------------------------------


