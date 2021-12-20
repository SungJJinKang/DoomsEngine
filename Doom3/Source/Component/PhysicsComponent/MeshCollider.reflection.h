#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Component_PhysicsComponent_MeshCollider_reflection_h


#ifdef __Source_Component_PhysicsComponent_MeshCollider_reflection_h

#error "__Source_Component_PhysicsComponent_MeshCollider_reflection_h already included, missing '#pragma once' in __Source_Component_PhysicsComponent_MeshCollider_reflection_h"

#endif

#define __Source_Component_PhysicsComponent_MeshCollider_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__MeshCollider
#error "GENERATE_BODY_FULLNAME_dooms__MeshCollider already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__MeshCollider
#define INHERITANCE_INFORMATION_dooms__MeshCollider \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 1793318124, 3608780617, 960295289, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 5 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::Collider3DComponent Base;


#undef CLONE_OBJECT_dooms__MeshCollider
#define CLONE_OBJECT_dooms__MeshCollider \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::MeshCollider>::value == true) && (std::is_base_of<dooms::DObject, dooms::MeshCollider>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::MeshCollider>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__MeshCollider
#define CURRENT_TYPE_ALIAS_dooms__MeshCollider \
public : \
typedef dooms::MeshCollider Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshCollider
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshCollider \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1793318124; \
inline static const char* const TYPE_FULL_NAME = "dooms::MeshCollider"; \
inline static const char* const TYPE_SHORT_NAME = "MeshCollider"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_MeshCollider
#define TYPE_CHECK_FUNCTION_MeshCollider \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__MeshCollider
#define GENERATE_BODY_FULLNAME_dooms__MeshCollider(...) \
INHERITANCE_INFORMATION_dooms__MeshCollider \
CLONE_OBJECT_dooms__MeshCollider \
CURRENT_TYPE_ALIAS_dooms__MeshCollider \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshCollider \
TYPE_CHECK_FUNCTION_MeshCollider \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_MeshCollider(...) GENERATE_BODY_FULLNAME_dooms__MeshCollider(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__MeshCollider(__VA_ARGS__)


//-------------------------------------------


