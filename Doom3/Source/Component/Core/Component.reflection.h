#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Component_Core_Component_reflection_h


#ifdef __Source_Component_Core_Component_reflection_h

#error "__Source_Component_Core_Component_reflection_h already included, missing '#pragma once' in __Source_Component_Core_Component_reflection_h"

#endif

#define __Source_Component_Core_Component_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__Component
#error "GENERATE_BODY_FULLNAME_dooms__Component already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__Component
#define INHERITANCE_INFORMATION_dooms__Component \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__Component
#define CLONE_OBJECT_dooms__Component \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::Component>::value == true) && (std::is_base_of<dooms::DObject, dooms::Component>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::Component>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__Component
#define CURRENT_TYPE_ALIAS_dooms__Component \
public : \
typedef dooms::Component Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Component
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Component \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3040581954; \
inline static const char* const TYPE_FULL_NAME = "dooms::Component"; \
inline static const char* const TYPE_SHORT_NAME = "Component"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Component
#define TYPE_CHECK_FUNCTION_Component \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__Component
#define GENERATE_BODY_FULLNAME_dooms__Component(...) \
INHERITANCE_INFORMATION_dooms__Component \
CLONE_OBJECT_dooms__Component \
CURRENT_TYPE_ALIAS_dooms__Component \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Component \
TYPE_CHECK_FUNCTION_Component \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Component(...) GENERATE_BODY_FULLNAME_dooms__Component(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__Component(__VA_ARGS__)


//-------------------------------------------


