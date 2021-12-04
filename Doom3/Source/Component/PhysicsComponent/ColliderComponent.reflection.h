#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\ColliderComponent.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_PhysicsComponent_ColliderComponent_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\ColliderComponent.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\ColliderComponent.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_PhysicsComponent_ColliderComponent_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__ColliderComponent
#error "GENERATE_BODY_FULLNAME_dooms__ColliderComponent already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__ColliderComponent
#define INHERITANCE_INFORMATION_dooms__ColliderComponent \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 960295289, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::Component Base;


#undef CLONE_OBJECT_dooms__ColliderComponent
#define CLONE_OBJECT_dooms__ColliderComponent \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::ColliderComponent>::value == true) && (std::is_base_of<dooms::DObject, dooms::ColliderComponent>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::ColliderComponent>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__ColliderComponent
#define CURRENT_TYPE_ALIAS_dooms__ColliderComponent \
public : \
typedef dooms::ColliderComponent Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ColliderComponent
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ColliderComponent \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 960295289; \
inline static const char* const TYPE_FULL_NAME = "dooms::ColliderComponent"; \
inline static const char* const TYPE_SHORT_NAME = "ColliderComponent"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_ColliderComponent
#define TYPE_CHECK_FUNCTION_ColliderComponent \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__ColliderComponent
#define GENERATE_BODY_FULLNAME_dooms__ColliderComponent(...) \
INHERITANCE_INFORMATION_dooms__ColliderComponent \
CLONE_OBJECT_dooms__ColliderComponent \
CURRENT_TYPE_ALIAS_dooms__ColliderComponent \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ColliderComponent \
TYPE_CHECK_FUNCTION_ColliderComponent \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ColliderComponent(...) GENERATE_BODY_FULLNAME_dooms__ColliderComponent(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__ColliderComponent(__VA_ARGS__)


//-------------------------------------------


