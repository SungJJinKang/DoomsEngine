#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_GameLogic_CustomComponent_Portfolio_ViewFrustumCullingDebug_reflection_h


#ifdef __Source_GameLogic_CustomComponent_Portfolio_ViewFrustumCullingDebug_reflection_h

#error "__Source_GameLogic_CustomComponent_Portfolio_ViewFrustumCullingDebug_reflection_h already included, missing '#pragma once' in __Source_GameLogic_CustomComponent_Portfolio_ViewFrustumCullingDebug_reflection_h"

#endif

#define __Source_GameLogic_CustomComponent_Portfolio_ViewFrustumCullingDebug_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__ViewFrustumCullingDebug
#error "GENERATE_BODY_FULLNAME_dooms__ViewFrustumCullingDebug already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__ViewFrustumCullingDebug
#define INHERITANCE_INFORMATION_dooms__ViewFrustumCullingDebug \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 1981500682, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::Component Base;


#undef CLONE_OBJECT_dooms__ViewFrustumCullingDebug
#define CLONE_OBJECT_dooms__ViewFrustumCullingDebug \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::ViewFrustumCullingDebug>::value == true) && (std::is_base_of<dooms::DObject, dooms::ViewFrustumCullingDebug>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::ViewFrustumCullingDebug>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__ViewFrustumCullingDebug
#define CURRENT_TYPE_ALIAS_dooms__ViewFrustumCullingDebug \
public : \
typedef dooms::ViewFrustumCullingDebug Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ViewFrustumCullingDebug
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ViewFrustumCullingDebug \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1981500682; \
inline static const char* const TYPE_FULL_NAME = "dooms::ViewFrustumCullingDebug"; \
inline static const char* const TYPE_SHORT_NAME = "ViewFrustumCullingDebug"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_ViewFrustumCullingDebug
#define TYPE_CHECK_FUNCTION_ViewFrustumCullingDebug \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__ViewFrustumCullingDebug
#define GENERATE_BODY_FULLNAME_dooms__ViewFrustumCullingDebug(...) \
INHERITANCE_INFORMATION_dooms__ViewFrustumCullingDebug \
CLONE_OBJECT_dooms__ViewFrustumCullingDebug \
CURRENT_TYPE_ALIAS_dooms__ViewFrustumCullingDebug \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ViewFrustumCullingDebug \
TYPE_CHECK_FUNCTION_ViewFrustumCullingDebug \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ViewFrustumCullingDebug(...) GENERATE_BODY_FULLNAME_dooms__ViewFrustumCullingDebug(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__ViewFrustumCullingDebug(__VA_ARGS__)


//-------------------------------------------


