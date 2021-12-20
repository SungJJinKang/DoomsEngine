#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Light\DirectionalLight.cpp


#ifdef _Source_Component_Rendering_Light_DirectionalLight_reflection_h

#error "_Source_Component_Rendering_Light_DirectionalLight_reflection_h already included, missing '#pragma once' in _Source_Component_Rendering_Light_DirectionalLight_reflection_h"

#endif

#define _Source_Component_Rendering_Light_DirectionalLight_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__DirectionalLight
#error "GENERATE_BODY_FULLNAME_dooms__DirectionalLight already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__DirectionalLight
#define INHERITANCE_INFORMATION_dooms__DirectionalLight \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 1852129323, 2741420880, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::Light Base;


#undef CLONE_OBJECT_dooms__DirectionalLight
#define CLONE_OBJECT_dooms__DirectionalLight \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::DirectionalLight>::value == true) && (std::is_base_of<dooms::DObject, dooms::DirectionalLight>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::DirectionalLight>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__DirectionalLight
#define CURRENT_TYPE_ALIAS_dooms__DirectionalLight \
public : \
typedef dooms::DirectionalLight Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DirectionalLight
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DirectionalLight \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1852129323; \
inline static const char* const TYPE_FULL_NAME = "dooms::DirectionalLight"; \
inline static const char* const TYPE_SHORT_NAME = "DirectionalLight"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_DirectionalLight
#define TYPE_CHECK_FUNCTION_DirectionalLight \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__DirectionalLight
#define GENERATE_BODY_FULLNAME_dooms__DirectionalLight(...) \
INHERITANCE_INFORMATION_dooms__DirectionalLight \
CLONE_OBJECT_dooms__DirectionalLight \
CURRENT_TYPE_ALIAS_dooms__DirectionalLight \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DirectionalLight \
TYPE_CHECK_FUNCTION_DirectionalLight \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DirectionalLight(...) GENERATE_BODY_FULLNAME_dooms__DirectionalLight(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__DirectionalLight(__VA_ARGS__)


//-------------------------------------------


