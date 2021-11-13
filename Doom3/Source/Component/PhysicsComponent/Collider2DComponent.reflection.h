#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\Collider2DComponent.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_PhysicsComponent_Collider2DComponent_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\Collider2DComponent.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\Collider2DComponent.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_PhysicsComponent_Collider2DComponent_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__Collider2DComponent
#error "GENERATE_BODY_FULLNAME_dooms__Collider2DComponent already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__Collider2DComponent
#define INHERITANCE_INFORMATION_dooms__Collider2DComponent \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 2836413646, 960295289, 1503232071, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 5 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::ColliderComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__Collider2DComponent
#define CURRENT_TYPE_ALIAS_dooms__Collider2DComponent \
public: typedef dooms::Collider2DComponent Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Collider2DComponent
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Collider2DComponent \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2836413646; \
inline static const char* const TYPE_FULL_NAME = "dooms::Collider2DComponent"; \
inline static const char* const TYPE_SHORT_NAME = "Collider2DComponent"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Collider2DComponent
#define TYPE_CHECK_FUNCTION_Collider2DComponent \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__Collider2DComponent
#define GENERATE_BODY_FULLNAME_dooms__Collider2DComponent(...) \
INHERITANCE_INFORMATION_dooms__Collider2DComponent \
CURRENT_TYPE_ALIAS_dooms__Collider2DComponent \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Collider2DComponent \
TYPE_CHECK_FUNCTION_Collider2DComponent \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Collider2DComponent(...) GENERATE_BODY_FULLNAME_dooms__Collider2DComponent(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__Collider2DComponent(__VA_ARGS__)


//-------------------------------------------


