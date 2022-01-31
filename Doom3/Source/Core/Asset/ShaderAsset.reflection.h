#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_Asset_ShaderAsset_reflection_h


#ifdef __Source_Core_Asset_ShaderAsset_reflection_h

#error "__Source_Core_Asset_ShaderAsset_reflection_h already included, missing '#pragma once' in __Source_Core_Asset_ShaderAsset_reflection_h"

#endif

#define __Source_Core_Asset_ShaderAsset_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__asset__ShaderTextData
#error "GENERATE_BODY_FULLNAME_dooms__asset__ShaderTextData already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__asset__ShaderTextData
#define CURRENT_TYPE_ALIAS_dooms__asset__ShaderTextData \
typedef dooms::asset::ShaderTextData Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderTextData
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderTextData \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 634440315; \
inline static const char* const TYPE_FULL_NAME = "dooms::asset::ShaderTextData"; \
inline static const char* const TYPE_SHORT_NAME = "ShaderTextData"; \


#undef TYPE_CHECK_FUNCTION_ShaderTextData
#define TYPE_CHECK_FUNCTION_ShaderTextData \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__asset__ShaderTextData
#define GENERATE_BODY_FULLNAME_dooms__asset__ShaderTextData(...) \
CURRENT_TYPE_ALIAS_dooms__asset__ShaderTextData \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderTextData \
TYPE_CHECK_FUNCTION_ShaderTextData \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ShaderTextData(...) GENERATE_BODY_FULLNAME_dooms__asset__ShaderTextData(__VA_ARGS__)


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset__ShaderObject
#error "GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset__ShaderObject already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__asset__ShaderAsset__ShaderObject
#define CURRENT_TYPE_ALIAS_dooms__asset__ShaderAsset__ShaderObject \
typedef dooms::asset::ShaderAsset::ShaderObject Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderAsset__ShaderObject
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderAsset__ShaderObject \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2633997282; \
inline static const char* const TYPE_FULL_NAME = "dooms::asset::ShaderAsset::ShaderObject"; \
inline static const char* const TYPE_SHORT_NAME = "ShaderObject"; \


#undef TYPE_CHECK_FUNCTION_ShaderObject
#define TYPE_CHECK_FUNCTION_ShaderObject \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset__ShaderObject
#define GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset__ShaderObject(...) \
CURRENT_TYPE_ALIAS_dooms__asset__ShaderAsset__ShaderObject \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderAsset__ShaderObject \
TYPE_CHECK_FUNCTION_ShaderObject \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ShaderObject(...) GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset__ShaderObject(__VA_ARGS__)


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset
#error "GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__asset__ShaderAsset
#define INHERITANCE_INFORMATION_dooms__asset__ShaderAsset \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 4085855849, 2982024308, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::asset::Asset Base;


#undef CLONE_OBJECT_dooms__asset__ShaderAsset
#define CLONE_OBJECT_dooms__asset__ShaderAsset \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::asset::ShaderAsset>::value == true) && (std::is_base_of<dooms::DObject, dooms::asset::ShaderAsset>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::asset::ShaderAsset>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__asset__ShaderAsset
#define CURRENT_TYPE_ALIAS_dooms__asset__ShaderAsset \
public : \
typedef dooms::asset::ShaderAsset Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderAsset
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderAsset \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 4085855849; \
inline static const char* const TYPE_FULL_NAME = "dooms::asset::ShaderAsset"; \
inline static const char* const TYPE_SHORT_NAME = "ShaderAsset"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_ShaderAsset
#define TYPE_CHECK_FUNCTION_ShaderAsset \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset
#define GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset(...) \
INHERITANCE_INFORMATION_dooms__asset__ShaderAsset \
CLONE_OBJECT_dooms__asset__ShaderAsset \
CURRENT_TYPE_ALIAS_dooms__asset__ShaderAsset \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ShaderAsset \
TYPE_CHECK_FUNCTION_ShaderAsset \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ShaderAsset(...) GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__asset__ShaderAsset(__VA_ARGS__)


//-------------------------------------------


