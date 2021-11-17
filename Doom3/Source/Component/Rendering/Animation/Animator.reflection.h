#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Animation\Animator.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_Rendering_Animation_Animator_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Animation\Animator.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Animation\Animator.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_Rendering_Animation_Animator_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__Animator
#error "GENERATE_BODY_FULLNAME_dooms__Animator already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__Animator
#define INHERITANCE_INFORMATION_dooms__Animator \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 2311486034, 1503232071, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::ServerComponent Base;


#undef CLONE_OBJECT_dooms__Animator
#define CLONE_OBJECT_dooms__Animator \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::Animator>::value == true) && (std::is_base_of<dooms::DObject, dooms::Animator>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::Animator>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__Animator
#define CURRENT_TYPE_ALIAS_dooms__Animator \
public : \
typedef dooms::Animator Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Animator
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Animator \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2311486034; \
inline static const char* const TYPE_FULL_NAME = "dooms::Animator"; \
inline static const char* const TYPE_SHORT_NAME = "Animator"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Animator
#define TYPE_CHECK_FUNCTION_Animator \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__Animator
#define GENERATE_BODY_FULLNAME_dooms__Animator(...) \
INHERITANCE_INFORMATION_dooms__Animator \
CLONE_OBJECT_dooms__Animator \
CURRENT_TYPE_ALIAS_dooms__Animator \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Animator \
TYPE_CHECK_FUNCTION_Animator \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Animator(...) GENERATE_BODY_FULLNAME_dooms__Animator(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__Animator(__VA_ARGS__)


//-------------------------------------------


