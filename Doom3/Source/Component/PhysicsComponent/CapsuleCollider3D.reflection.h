#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Component_PhysicsComponent_CapsuleCollider3D_reflection_h


#ifdef __Source_Component_PhysicsComponent_CapsuleCollider3D_reflection_h

#error "__Source_Component_PhysicsComponent_CapsuleCollider3D_reflection_h already included, missing '#pragma once' in __Source_Component_PhysicsComponent_CapsuleCollider3D_reflection_h"

#endif

#define __Source_Component_PhysicsComponent_CapsuleCollider3D_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__CapsuleCollider3D
#error "GENERATE_BODY_FULLNAME_dooms__CapsuleCollider3D already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__CapsuleCollider3D
#define INHERITANCE_INFORMATION_dooms__CapsuleCollider3D \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 174153128, 3608780617, 960295289, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 5 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::Collider3DComponent Base;


#undef CLONE_OBJECT_dooms__CapsuleCollider3D
#define CLONE_OBJECT_dooms__CapsuleCollider3D \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::CapsuleCollider3D>::value == true) && (std::is_base_of<dooms::DObject, dooms::CapsuleCollider3D>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::CapsuleCollider3D>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__CapsuleCollider3D
#define CURRENT_TYPE_ALIAS_dooms__CapsuleCollider3D \
public : \
typedef dooms::CapsuleCollider3D Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__CapsuleCollider3D
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__CapsuleCollider3D \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 174153128; \
inline static const char* const TYPE_FULL_NAME = "dooms::CapsuleCollider3D"; \
inline static const char* const TYPE_SHORT_NAME = "CapsuleCollider3D"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_CapsuleCollider3D
#define TYPE_CHECK_FUNCTION_CapsuleCollider3D \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__CapsuleCollider3D
#define GENERATE_BODY_FULLNAME_dooms__CapsuleCollider3D(...) \
INHERITANCE_INFORMATION_dooms__CapsuleCollider3D \
CLONE_OBJECT_dooms__CapsuleCollider3D \
CURRENT_TYPE_ALIAS_dooms__CapsuleCollider3D \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__CapsuleCollider3D \
TYPE_CHECK_FUNCTION_CapsuleCollider3D \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_CapsuleCollider3D(...) GENERATE_BODY_FULLNAME_dooms__CapsuleCollider3D(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__CapsuleCollider3D(__VA_ARGS__)


//-------------------------------------------


