#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Asset\TextAsset.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Asset_TextAsset_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Asset\TextAsset.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Asset\TextAsset.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Asset_TextAsset_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__asset__TextAsset
#error "GENERATE_BODY_FULLNAME_dooms__asset__TextAsset already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__asset__TextAsset
#define INHERITANCE_INFORMATION_dooms__asset__TextAsset \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 2711351113, 2982024308, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::asset::Asset Base;


#undef CURRENT_TYPE_ALIAS_dooms__asset__TextAsset
#define CURRENT_TYPE_ALIAS_dooms__asset__TextAsset \
public: typedef dooms::asset::TextAsset Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__TextAsset
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__TextAsset \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2711351113; \
inline static const char* const TYPE_FULL_NAME = "dooms::asset::TextAsset"; \
inline static const char* const TYPE_SHORT_NAME = "TextAsset"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_TextAsset
#define TYPE_CHECK_FUNCTION_TextAsset \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__asset__TextAsset
#define GENERATE_BODY_FULLNAME_dooms__asset__TextAsset(...) \
INHERITANCE_INFORMATION_dooms__asset__TextAsset \
CURRENT_TYPE_ALIAS_dooms__asset__TextAsset \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__TextAsset \
TYPE_CHECK_FUNCTION_TextAsset \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_TextAsset(...) GENERATE_BODY_FULLNAME_dooms__asset__TextAsset(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__asset__TextAsset(__VA_ARGS__)


//-------------------------------------------


