#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Asset\FontAsset.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Asset_FontAsset_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Asset\FontAsset.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Asset\FontAsset.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Asset_FontAsset_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__asset__FontAsset
#error "GENERATE_BODY_FULLNAME_dooms__asset__FontAsset already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__asset__FontAsset
#define INHERITANCE_INFORMATION_dooms__asset__FontAsset \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 1796695865, 2982024308, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::asset::Asset Base;


#undef CURRENT_TYPE_ALIAS_dooms__asset__FontAsset
#define CURRENT_TYPE_ALIAS_dooms__asset__FontAsset \
public: typedef dooms::asset::FontAsset Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__FontAsset
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__FontAsset \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1796695865; \
inline static const char* const TYPE_FULL_NAME = "dooms::asset::FontAsset"; \
inline static const char* const TYPE_SHORT_NAME = "FontAsset"; 


#undef TYPE_CHECK_FUNCTION_FontAsset
#define TYPE_CHECK_FUNCTION_FontAsset \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__asset__FontAsset
#define GENERATE_BODY_FULLNAME_dooms__asset__FontAsset(...) \
INHERITANCE_INFORMATION_dooms__asset__FontAsset \
CURRENT_TYPE_ALIAS_dooms__asset__FontAsset \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__FontAsset \
TYPE_CHECK_FUNCTION_FontAsset \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_FontAsset(...) GENERATE_BODY_FULLNAME_dooms__asset__FontAsset(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__asset__FontAsset(__VA_ARGS__)


//-------------------------------------------


