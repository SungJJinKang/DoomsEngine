#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Asset\Asset.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Asset_Asset_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Asset\Asset.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Asset\Asset.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Asset_Asset_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__asset__Asset
#error "GENERATE_BODY_FULLNAME_dooms__asset__Asset already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__asset__Asset
#define INHERITANCE_INFORMATION_dooms__asset__Asset \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 2982024308, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::DObject Base;


#undef CURRENT_TYPE_ALIAS_dooms__asset__Asset
#define CURRENT_TYPE_ALIAS_dooms__asset__Asset \
public: typedef dooms::asset::Asset Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__Asset
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__Asset \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2982024308; \
inline static const char* const TYPE_FULL_NAME = "dooms::asset::Asset"; \
inline static const char* const TYPE_SHORT_NAME = "Asset"; 


#undef TYPE_CHECK_FUNCTION_Asset
#define TYPE_CHECK_FUNCTION_Asset \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__asset__Asset
#define GENERATE_BODY_FULLNAME_dooms__asset__Asset(...) \
INHERITANCE_INFORMATION_dooms__asset__Asset \
CURRENT_TYPE_ALIAS_dooms__asset__Asset \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__Asset \
TYPE_CHECK_FUNCTION_Asset \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Asset(...) GENERATE_BODY_FULLNAME_dooms__asset__Asset(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__asset__Asset(__VA_ARGS__)


//-------------------------------------------


