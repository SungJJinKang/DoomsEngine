#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Physics\Physics_Server.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Physics_Physics_Server_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Physics\Physics_Server.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Physics\Physics_Server.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Physics_Physics_Server_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__physics__Physics_Server
#error "GENERATE_BODY_FULLNAME_dooms__physics__Physics_Server already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__physics__Physics_Server
#define INHERITANCE_INFORMATION_dooms__physics__Physics_Server \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 3649827376, 3668408939, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::IGameFlow Base;


#undef CLONE_OBJECT_dooms__physics__Physics_Server
#define CLONE_OBJECT_dooms__physics__Physics_Server \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::physics::Physics_Server>::value == true) && (std::is_base_of<dooms::DObject, dooms::physics::Physics_Server>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::physics::Physics_Server>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__physics__Physics_Server
#define CURRENT_TYPE_ALIAS_dooms__physics__Physics_Server \
public : \
typedef dooms::physics::Physics_Server Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Physics_Server
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Physics_Server \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3649827376; \
inline static const char* const TYPE_FULL_NAME = "dooms::physics::Physics_Server"; \
inline static const char* const TYPE_SHORT_NAME = "Physics_Server"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Physics_Server
#define TYPE_CHECK_FUNCTION_Physics_Server \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__physics__Physics_Server
#define GENERATE_BODY_FULLNAME_dooms__physics__Physics_Server(...) \
INHERITANCE_INFORMATION_dooms__physics__Physics_Server \
CLONE_OBJECT_dooms__physics__Physics_Server \
CURRENT_TYPE_ALIAS_dooms__physics__Physics_Server \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Physics_Server \
TYPE_CHECK_FUNCTION_Physics_Server \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Physics_Server(...) GENERATE_BODY_FULLNAME_dooms__physics__Physics_Server(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__physics__Physics_Server(__VA_ARGS__)


//-------------------------------------------


