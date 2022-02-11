#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_Graphics_Pipeline_DeferredRenderingDrawer_reflection_h


#ifdef __Source_Core_Graphics_Pipeline_DeferredRenderingDrawer_reflection_h

#error "__Source_Core_Graphics_Pipeline_DeferredRenderingDrawer_reflection_h already included, missing '#pragma once' in __Source_Core_Graphics_Pipeline_DeferredRenderingDrawer_reflection_h"

#endif

#define __Source_Core_Graphics_Pipeline_DeferredRenderingDrawer_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__DeferredRenderingDrawer
#error "GENERATE_BODY_FULLNAME_dooms__graphics__DeferredRenderingDrawer already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__DeferredRenderingDrawer
#define INHERITANCE_INFORMATION_dooms__graphics__DeferredRenderingDrawer \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 3774730794, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__graphics__DeferredRenderingDrawer
#define CLONE_OBJECT_dooms__graphics__DeferredRenderingDrawer \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::graphics::DeferredRenderingDrawer>::value == true) && (std::is_base_of<dooms::DObject, dooms::graphics::DeferredRenderingDrawer>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::graphics::DeferredRenderingDrawer>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__graphics__DeferredRenderingDrawer
#define CURRENT_TYPE_ALIAS_dooms__graphics__DeferredRenderingDrawer \
public : \
typedef dooms::graphics::DeferredRenderingDrawer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__DeferredRenderingDrawer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__DeferredRenderingDrawer \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3774730794; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::DeferredRenderingDrawer"; \
inline static const char* const TYPE_SHORT_NAME = "DeferredRenderingDrawer"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_DeferredRenderingDrawer
#define TYPE_CHECK_FUNCTION_DeferredRenderingDrawer \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__DeferredRenderingDrawer
#define GENERATE_BODY_FULLNAME_dooms__graphics__DeferredRenderingDrawer(...) \
INHERITANCE_INFORMATION_dooms__graphics__DeferredRenderingDrawer \
CLONE_OBJECT_dooms__graphics__DeferredRenderingDrawer \
CURRENT_TYPE_ALIAS_dooms__graphics__DeferredRenderingDrawer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__DeferredRenderingDrawer \
TYPE_CHECK_FUNCTION_DeferredRenderingDrawer \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DeferredRenderingDrawer(...) GENERATE_BODY_FULLNAME_dooms__graphics__DeferredRenderingDrawer(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__DeferredRenderingDrawer(__VA_ARGS__)


//-------------------------------------------


