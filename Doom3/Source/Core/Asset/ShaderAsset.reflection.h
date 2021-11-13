#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Asset\ShaderAsset.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Asset_ShaderAsset_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Asset\ShaderAsset.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Asset\ShaderAsset.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Asset_ShaderAsset_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset__ShaderText
#error "GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset__ShaderText already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__asset__ShaderAsset__ShaderText
#define CURRENT_TYPE_ALIAS_dooms__asset__ShaderAsset__ShaderText \
public: typedef dooms::asset::ShaderAsset::ShaderText Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderAsset__ShaderText
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderAsset__ShaderText \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 4054785202; \
inline static const char* const TYPE_FULL_NAME = "dooms::asset::ShaderAsset::ShaderText"; \
inline static const char* const TYPE_SHORT_NAME = "ShaderText"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_ShaderText
#define TYPE_CHECK_FUNCTION_ShaderText \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset__ShaderText
#define GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset__ShaderText(...) \
CURRENT_TYPE_ALIAS_dooms__asset__ShaderAsset__ShaderText \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderAsset__ShaderText \
TYPE_CHECK_FUNCTION_ShaderText \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ShaderText(...) GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset__ShaderText(__VA_ARGS__)


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset
#error "GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__asset__ShaderAsset
#define INHERITANCE_INFORMATION_dooms__asset__ShaderAsset \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 4085855849, 2982024308, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::asset::Asset Base;


#undef CURRENT_TYPE_ALIAS_dooms__asset__ShaderAsset
#define CURRENT_TYPE_ALIAS_dooms__asset__ShaderAsset \
public: typedef dooms::asset::ShaderAsset Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderAsset
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderAsset \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 4085855849; \
inline static const char* const TYPE_FULL_NAME = "dooms::asset::ShaderAsset"; \
inline static const char* const TYPE_SHORT_NAME = "ShaderAsset"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_ShaderAsset
#define TYPE_CHECK_FUNCTION_ShaderAsset \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset
#define GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset(...) \
INHERITANCE_INFORMATION_dooms__asset__ShaderAsset \
CURRENT_TYPE_ALIAS_dooms__asset__ShaderAsset \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderAsset \
TYPE_CHECK_FUNCTION_ShaderAsset \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ShaderAsset(...) GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset(__VA_ARGS__)


//-------------------------------------------


