#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\CharacterSpawner.cpp


#ifdef _Source_GameLogic_CustomComponent_CharacterSpawner_reflection_h

#error "_Source_GameLogic_CustomComponent_CharacterSpawner_reflection_h already included, missing '#pragma once' in _Source_GameLogic_CustomComponent_CharacterSpawner_reflection_h"

#endif

#define _Source_GameLogic_CustomComponent_CharacterSpawner_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__CharacterSpawner
#error "GENERATE_BODY_FULLNAME_dooms__CharacterSpawner already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__CharacterSpawner
#define INHERITANCE_INFORMATION_dooms__CharacterSpawner \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 2209894353, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::Component Base;


#undef CLONE_OBJECT_dooms__CharacterSpawner
#define CLONE_OBJECT_dooms__CharacterSpawner \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::CharacterSpawner>::value == true) && (std::is_base_of<dooms::DObject, dooms::CharacterSpawner>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::CharacterSpawner>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__CharacterSpawner
#define CURRENT_TYPE_ALIAS_dooms__CharacterSpawner \
public : \
typedef dooms::CharacterSpawner Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__CharacterSpawner
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__CharacterSpawner \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2209894353; \
inline static const char* const TYPE_FULL_NAME = "dooms::CharacterSpawner"; \
inline static const char* const TYPE_SHORT_NAME = "CharacterSpawner"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_CharacterSpawner
#define TYPE_CHECK_FUNCTION_CharacterSpawner \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__CharacterSpawner
#define GENERATE_BODY_FULLNAME_dooms__CharacterSpawner(...) \
INHERITANCE_INFORMATION_dooms__CharacterSpawner \
CLONE_OBJECT_dooms__CharacterSpawner \
CURRENT_TYPE_ALIAS_dooms__CharacterSpawner \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__CharacterSpawner \
TYPE_CHECK_FUNCTION_CharacterSpawner \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_CharacterSpawner(...) GENERATE_BODY_FULLNAME_dooms__CharacterSpawner(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__CharacterSpawner(__VA_ARGS__)


//-------------------------------------------


