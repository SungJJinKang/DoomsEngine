#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\Collider3DComponent.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_PhysicsComponent_Collider3DComponent_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\Collider3DComponent.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\Collider3DComponent.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_PhysicsComponent_Collider3DComponent_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__Collider3DComponent
#error "GENERATE_BODY_FULLNAME_dooms__Collider3DComponent already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__Collider3DComponent
#define INHERITANCE_INFORMATION_dooms__Collider3DComponent \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3608780617, 960295289, 1503232071, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 5 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::ColliderComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__Collider3DComponent
#define CURRENT_TYPE_ALIAS_dooms__Collider3DComponent \
public: typedef dooms::Collider3DComponent Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Collider3DComponent
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Collider3DComponent \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3608780617; \
inline static const char* const TYPE_FULL_NAME = "dooms::Collider3DComponent"; \
inline static const char* const TYPE_SHORT_NAME = "Collider3DComponent"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Collider3DComponent
#define TYPE_CHECK_FUNCTION_Collider3DComponent \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__Collider3DComponent
#define GENERATE_BODY_FULLNAME_dooms__Collider3DComponent(...) \
INHERITANCE_INFORMATION_dooms__Collider3DComponent \
CURRENT_TYPE_ALIAS_dooms__Collider3DComponent \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Collider3DComponent \
TYPE_CHECK_FUNCTION_Collider3DComponent \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Collider3DComponent(...) GENERATE_BODY_FULLNAME_dooms__Collider3DComponent(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__Collider3DComponent(__VA_ARGS__)


//-------------------------------------------


