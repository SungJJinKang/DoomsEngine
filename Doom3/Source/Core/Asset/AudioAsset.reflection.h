#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Asset\AudioAsset.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Asset_AudioAsset_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Asset\AudioAsset.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Asset\AudioAsset.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Asset_AudioAsset_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__asset__AudioAsset
#error "GENERATE_BODY_FULLNAME_dooms__asset__AudioAsset already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__asset__AudioAsset
#define INHERITANCE_INFORMATION_dooms__asset__AudioAsset \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3302541540, 2982024308, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::asset::Asset Base;


#undef CURRENT_TYPE_ALIAS_dooms__asset__AudioAsset
#define CURRENT_TYPE_ALIAS_dooms__asset__AudioAsset \
public: typedef dooms::asset::AudioAsset Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__AudioAsset
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__AudioAsset \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3302541540; \
inline static const char* const TYPE_FULL_NAME = "dooms::asset::AudioAsset"; \
inline static const char* const TYPE_SHORT_NAME = "AudioAsset"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_AudioAsset
#define TYPE_CHECK_FUNCTION_AudioAsset \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__asset__AudioAsset
#define GENERATE_BODY_FULLNAME_dooms__asset__AudioAsset(...) \
INHERITANCE_INFORMATION_dooms__asset__AudioAsset \
CURRENT_TYPE_ALIAS_dooms__asset__AudioAsset \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__AudioAsset \
TYPE_CHECK_FUNCTION_AudioAsset \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_AudioAsset(...) GENERATE_BODY_FULLNAME_dooms__asset__AudioAsset(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__asset__AudioAsset(__VA_ARGS__)


//-------------------------------------------


