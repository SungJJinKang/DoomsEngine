#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\Portfolio\PhysicsDebuggerController.cpp


#ifdef _Source_GameLogic_CustomComponent_Portfolio_PhysicsDebuggerController_reflection_h

#error "_Source_GameLogic_CustomComponent_Portfolio_PhysicsDebuggerController_reflection_h already included, missing '#pragma once' in _Source_GameLogic_CustomComponent_Portfolio_PhysicsDebuggerController_reflection_h"

#endif

#define _Source_GameLogic_CustomComponent_Portfolio_PhysicsDebuggerController_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__PhysicsDebuggerController
#error "GENERATE_BODY_FULLNAME_dooms__PhysicsDebuggerController already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__PhysicsDebuggerController
#define INHERITANCE_INFORMATION_dooms__PhysicsDebuggerController \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 343226959, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::Component Base;


#undef CLONE_OBJECT_dooms__PhysicsDebuggerController
#define CLONE_OBJECT_dooms__PhysicsDebuggerController \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::PhysicsDebuggerController>::value == true) && (std::is_base_of<dooms::DObject, dooms::PhysicsDebuggerController>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::PhysicsDebuggerController>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__PhysicsDebuggerController
#define CURRENT_TYPE_ALIAS_dooms__PhysicsDebuggerController \
public : \
typedef dooms::PhysicsDebuggerController Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PhysicsDebuggerController
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PhysicsDebuggerController \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 343226959; \
inline static const char* const TYPE_FULL_NAME = "dooms::PhysicsDebuggerController"; \
inline static const char* const TYPE_SHORT_NAME = "PhysicsDebuggerController"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_PhysicsDebuggerController
#define TYPE_CHECK_FUNCTION_PhysicsDebuggerController \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__PhysicsDebuggerController
#define GENERATE_BODY_FULLNAME_dooms__PhysicsDebuggerController(...) \
INHERITANCE_INFORMATION_dooms__PhysicsDebuggerController \
CLONE_OBJECT_dooms__PhysicsDebuggerController \
CURRENT_TYPE_ALIAS_dooms__PhysicsDebuggerController \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PhysicsDebuggerController \
TYPE_CHECK_FUNCTION_PhysicsDebuggerController \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_PhysicsDebuggerController(...) GENERATE_BODY_FULLNAME_dooms__PhysicsDebuggerController(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__PhysicsDebuggerController(__VA_ARGS__)


//-------------------------------------------


