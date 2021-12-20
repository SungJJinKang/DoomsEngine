#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\FireBulletComponent.cpp


#ifdef _Source_GameLogic_CustomComponent_FireBulletComponent_reflection_h

#error "_Source_GameLogic_CustomComponent_FireBulletComponent_reflection_h already included, missing '#pragma once' in _Source_GameLogic_CustomComponent_FireBulletComponent_reflection_h"

#endif

#define _Source_GameLogic_CustomComponent_FireBulletComponent_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__FireBulletComponent
#error "GENERATE_BODY_FULLNAME_dooms__FireBulletComponent already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__FireBulletComponent
#define INHERITANCE_INFORMATION_dooms__FireBulletComponent \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 3111448023, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::Component Base;


#undef CLONE_OBJECT_dooms__FireBulletComponent
#define CLONE_OBJECT_dooms__FireBulletComponent \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::FireBulletComponent>::value == true) && (std::is_base_of<dooms::DObject, dooms::FireBulletComponent>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::FireBulletComponent>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__FireBulletComponent
#define CURRENT_TYPE_ALIAS_dooms__FireBulletComponent \
public : \
typedef dooms::FireBulletComponent Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__FireBulletComponent
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__FireBulletComponent \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3111448023; \
inline static const char* const TYPE_FULL_NAME = "dooms::FireBulletComponent"; \
inline static const char* const TYPE_SHORT_NAME = "FireBulletComponent"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_FireBulletComponent
#define TYPE_CHECK_FUNCTION_FireBulletComponent \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__FireBulletComponent
#define GENERATE_BODY_FULLNAME_dooms__FireBulletComponent(...) \
INHERITANCE_INFORMATION_dooms__FireBulletComponent \
CLONE_OBJECT_dooms__FireBulletComponent \
CURRENT_TYPE_ALIAS_dooms__FireBulletComponent \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__FireBulletComponent \
TYPE_CHECK_FUNCTION_FireBulletComponent \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_FireBulletComponent(...) GENERATE_BODY_FULLNAME_dooms__FireBulletComponent(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__FireBulletComponent(__VA_ARGS__)


//-------------------------------------------


