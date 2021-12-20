#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Asset\FontAsset.cpp


#ifdef _Source_Core_Asset_FontAsset_reflection_h

#error "_Source_Core_Asset_FontAsset_reflection_h already included, missing '#pragma once' in _Source_Core_Asset_FontAsset_reflection_h"

#endif

#define _Source_Core_Asset_FontAsset_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__asset__FontAsset
#error "GENERATE_BODY_FULLNAME_dooms__asset__FontAsset already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__asset__FontAsset
#define INHERITANCE_INFORMATION_dooms__asset__FontAsset \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 1796695865, 2982024308, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::asset::Asset Base;


#undef CLONE_OBJECT_dooms__asset__FontAsset
#define CLONE_OBJECT_dooms__asset__FontAsset \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::asset::FontAsset>::value == true) && (std::is_base_of<dooms::DObject, dooms::asset::FontAsset>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::asset::FontAsset>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__asset__FontAsset
#define CURRENT_TYPE_ALIAS_dooms__asset__FontAsset \
public : \
typedef dooms::asset::FontAsset Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__FontAsset
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__FontAsset \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1796695865; \
inline static const char* const TYPE_FULL_NAME = "dooms::asset::FontAsset"; \
inline static const char* const TYPE_SHORT_NAME = "FontAsset"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_FontAsset
#define TYPE_CHECK_FUNCTION_FontAsset \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__asset__FontAsset
#define GENERATE_BODY_FULLNAME_dooms__asset__FontAsset(...) \
INHERITANCE_INFORMATION_dooms__asset__FontAsset \
CLONE_OBJECT_dooms__asset__FontAsset \
CURRENT_TYPE_ALIAS_dooms__asset__FontAsset \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__FontAsset \
TYPE_CHECK_FUNCTION_FontAsset \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_FontAsset(...) GENERATE_BODY_FULLNAME_dooms__asset__FontAsset(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__asset__FontAsset(__VA_ARGS__)


//-------------------------------------------


