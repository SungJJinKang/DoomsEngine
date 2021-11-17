#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Game\AssetManager\AssetContainer.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Game_AssetManager_AssetContainer_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Game\AssetManager\AssetContainer.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Game\AssetManager\AssetContainer.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Game_AssetManager_AssetContainer_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__asset__AssetContainer
#error "GENERATE_BODY_FULLNAME_dooms__asset__AssetContainer already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__asset__AssetContainer
#define CURRENT_TYPE_ALIAS_dooms__asset__AssetContainer \
typedef dooms::asset::AssetContainer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__AssetContainer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__AssetContainer \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2052131787; \
inline static const char* const TYPE_FULL_NAME = "dooms::asset::AssetContainer"; \
inline static const char* const TYPE_SHORT_NAME = "AssetContainer"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_AssetContainer
#define TYPE_CHECK_FUNCTION_AssetContainer \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__asset__AssetContainer
#define GENERATE_BODY_FULLNAME_dooms__asset__AssetContainer(...) \
CURRENT_TYPE_ALIAS_dooms__asset__AssetContainer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__AssetContainer \
TYPE_CHECK_FUNCTION_AssetContainer \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_AssetContainer(...) GENERATE_BODY_FULLNAME_dooms__asset__AssetContainer(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__asset__AssetContainer(__VA_ARGS__)


//-------------------------------------------


