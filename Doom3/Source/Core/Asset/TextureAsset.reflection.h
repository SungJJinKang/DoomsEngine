#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Asset\TextureAsset.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Asset_TextureAsset_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Asset\TextureAsset.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Asset\TextureAsset.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Asset_TextureAsset_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__asset__TextureAsset
#error "GENERATE_BODY_FULLNAME_dooms__asset__TextureAsset already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__asset__TextureAsset
#define INHERITANCE_INFORMATION_dooms__asset__TextureAsset \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 804918344, 2982024308, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::asset::Asset Base;


#undef CURRENT_TYPE_ALIAS_dooms__asset__TextureAsset
#define CURRENT_TYPE_ALIAS_dooms__asset__TextureAsset \
public: typedef dooms::asset::TextureAsset Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__TextureAsset
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__TextureAsset \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 804918344; \
inline static const char* const TYPE_FULL_NAME = "dooms::asset::TextureAsset"; \
inline static const char* const TYPE_SHORT_NAME = "TextureAsset"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_TextureAsset
#define TYPE_CHECK_FUNCTION_TextureAsset \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__asset__TextureAsset
#define GENERATE_BODY_FULLNAME_dooms__asset__TextureAsset(...) \
INHERITANCE_INFORMATION_dooms__asset__TextureAsset \
CURRENT_TYPE_ALIAS_dooms__asset__TextureAsset \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__TextureAsset \
TYPE_CHECK_FUNCTION_TextureAsset \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_TextureAsset(...) GENERATE_BODY_FULLNAME_dooms__asset__TextureAsset(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__asset__TextureAsset(__VA_ARGS__)


//-------------------------------------------


