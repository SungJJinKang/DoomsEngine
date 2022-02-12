#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Component_Rendering_Renderer_RendererStaticIterator_reflection_h


#ifdef __Source_Component_Rendering_Renderer_RendererStaticIterator_reflection_h

#error "__Source_Component_Rendering_Renderer_RendererStaticIterator_reflection_h already included, missing '#pragma once' in __Source_Component_Rendering_Renderer_RendererStaticIterator_reflection_h"

#endif

#define __Source_Component_Rendering_Renderer_RendererStaticIterator_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__RendererListSwapContainer
#error "GENERATE_BODY_FULLNAME_dooms__RendererListSwapContainer already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__RendererListSwapContainer
#define CURRENT_TYPE_ALIAS_dooms__RendererListSwapContainer \
typedef dooms::RendererListSwapContainer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__RendererListSwapContainer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__RendererListSwapContainer \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3296655123; \
inline static const char* const TYPE_FULL_NAME = "dooms::RendererListSwapContainer"; \
inline static const char* const TYPE_SHORT_NAME = "RendererListSwapContainer"; \


#undef TYPE_CHECK_FUNCTION_RendererListSwapContainer
#define TYPE_CHECK_FUNCTION_RendererListSwapContainer \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__RendererListSwapContainer
#define GENERATE_BODY_FULLNAME_dooms__RendererListSwapContainer(...) \
CURRENT_TYPE_ALIAS_dooms__RendererListSwapContainer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__RendererListSwapContainer \
TYPE_CHECK_FUNCTION_RendererListSwapContainer \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_RendererListSwapContainer(...) GENERATE_BODY_FULLNAME_dooms__RendererListSwapContainer(__VA_ARGS__)


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__RendererComponentStaticIterator
#error "GENERATE_BODY_FULLNAME_dooms__RendererComponentStaticIterator already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__RendererComponentStaticIterator
#define INHERITANCE_INFORMATION_dooms__RendererComponentStaticIterator \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 2630908701, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__RendererComponentStaticIterator
#define CLONE_OBJECT_dooms__RendererComponentStaticIterator \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::RendererComponentStaticIterator>::value == true) && (std::is_base_of<dooms::DObject, dooms::RendererComponentStaticIterator>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::RendererComponentStaticIterator>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__RendererComponentStaticIterator
#define CURRENT_TYPE_ALIAS_dooms__RendererComponentStaticIterator \
public : \
typedef dooms::RendererComponentStaticIterator Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__RendererComponentStaticIterator
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__RendererComponentStaticIterator \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2630908701; \
inline static const char* const TYPE_FULL_NAME = "dooms::RendererComponentStaticIterator"; \
inline static const char* const TYPE_SHORT_NAME = "RendererComponentStaticIterator"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_RendererComponentStaticIterator
#define TYPE_CHECK_FUNCTION_RendererComponentStaticIterator \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__RendererComponentStaticIterator
#define GENERATE_BODY_FULLNAME_dooms__RendererComponentStaticIterator(...) \
INHERITANCE_INFORMATION_dooms__RendererComponentStaticIterator \
CLONE_OBJECT_dooms__RendererComponentStaticIterator \
CURRENT_TYPE_ALIAS_dooms__RendererComponentStaticIterator \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__RendererComponentStaticIterator \
TYPE_CHECK_FUNCTION_RendererComponentStaticIterator \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_RendererComponentStaticIterator(...) GENERATE_BODY_FULLNAME_dooms__RendererComponentStaticIterator(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__RendererComponentStaticIterator(__VA_ARGS__)


//-------------------------------------------


