#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\BoxCollider2D.cpp


#ifdef _Source_Component_PhysicsComponent_BoxCollider2D_reflection_h

#error "_Source_Component_PhysicsComponent_BoxCollider2D_reflection_h already included, missing '#pragma once' in _Source_Component_PhysicsComponent_BoxCollider2D_reflection_h"

#endif

#define _Source_Component_PhysicsComponent_BoxCollider2D_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__BoxCollider2D
#error "GENERATE_BODY_FULLNAME_dooms__BoxCollider2D already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__BoxCollider2D
#define INHERITANCE_INFORMATION_dooms__BoxCollider2D \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 108344030, 2836413646, 960295289, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 5 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::Collider2DComponent Base;


#undef CLONE_OBJECT_dooms__BoxCollider2D
#define CLONE_OBJECT_dooms__BoxCollider2D \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::BoxCollider2D>::value == true) && (std::is_base_of<dooms::DObject, dooms::BoxCollider2D>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::BoxCollider2D>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__BoxCollider2D
#define CURRENT_TYPE_ALIAS_dooms__BoxCollider2D \
public : \
typedef dooms::BoxCollider2D Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__BoxCollider2D
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__BoxCollider2D \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 108344030; \
inline static const char* const TYPE_FULL_NAME = "dooms::BoxCollider2D"; \
inline static const char* const TYPE_SHORT_NAME = "BoxCollider2D"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_BoxCollider2D
#define TYPE_CHECK_FUNCTION_BoxCollider2D \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__BoxCollider2D
#define GENERATE_BODY_FULLNAME_dooms__BoxCollider2D(...) \
INHERITANCE_INFORMATION_dooms__BoxCollider2D \
CLONE_OBJECT_dooms__BoxCollider2D \
CURRENT_TYPE_ALIAS_dooms__BoxCollider2D \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__BoxCollider2D \
TYPE_CHECK_FUNCTION_BoxCollider2D \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_BoxCollider2D(...) GENERATE_BODY_FULLNAME_dooms__BoxCollider2D(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__BoxCollider2D(__VA_ARGS__)


//-------------------------------------------


