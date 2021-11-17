#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Renderer\MeshRenderer.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_Rendering_Renderer_MeshRenderer_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Renderer\MeshRenderer.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Renderer\MeshRenderer.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_Rendering_Renderer_MeshRenderer_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__MeshRenderer
#error "GENERATE_BODY_FULLNAME_dooms__MeshRenderer already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__MeshRenderer
#define INHERITANCE_INFORMATION_dooms__MeshRenderer \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 3778871520, 3346461073, 1503232071, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 5 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::Renderer Base;


#undef CLONE_OBJECT_dooms__MeshRenderer
#define CLONE_OBJECT_dooms__MeshRenderer \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::MeshRenderer>::value == true) && (std::is_base_of<dooms::DObject, dooms::MeshRenderer>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::MeshRenderer>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__MeshRenderer
#define CURRENT_TYPE_ALIAS_dooms__MeshRenderer \
public : \
typedef dooms::MeshRenderer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshRenderer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshRenderer \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3778871520; \
inline static const char* const TYPE_FULL_NAME = "dooms::MeshRenderer"; \
inline static const char* const TYPE_SHORT_NAME = "MeshRenderer"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_MeshRenderer
#define TYPE_CHECK_FUNCTION_MeshRenderer \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__MeshRenderer
#define GENERATE_BODY_FULLNAME_dooms__MeshRenderer(...) \
INHERITANCE_INFORMATION_dooms__MeshRenderer \
CLONE_OBJECT_dooms__MeshRenderer \
CURRENT_TYPE_ALIAS_dooms__MeshRenderer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshRenderer \
TYPE_CHECK_FUNCTION_MeshRenderer \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_MeshRenderer(...) GENERATE_BODY_FULLNAME_dooms__MeshRenderer(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__MeshRenderer(__VA_ARGS__)


//-------------------------------------------


