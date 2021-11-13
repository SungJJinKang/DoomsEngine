#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\CircleCollider2D.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_PhysicsComponent_CircleCollider2D_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\CircleCollider2D.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\CircleCollider2D.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_PhysicsComponent_CircleCollider2D_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__CircleCollider2D
#error "GENERATE_BODY_FULLNAME_dooms__CircleCollider2D already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__CircleCollider2D
#define INHERITANCE_INFORMATION_dooms__CircleCollider2D \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 1171934251, 2836413646, 960295289, 1503232071, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 6 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::Collider2DComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__CircleCollider2D
#define CURRENT_TYPE_ALIAS_dooms__CircleCollider2D \
public: typedef dooms::CircleCollider2D Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__CircleCollider2D
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__CircleCollider2D \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1171934251; \
inline static const char* const TYPE_FULL_NAME = "dooms::CircleCollider2D"; \
inline static const char* const TYPE_SHORT_NAME = "CircleCollider2D"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_CircleCollider2D
#define TYPE_CHECK_FUNCTION_CircleCollider2D \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__CircleCollider2D
#define GENERATE_BODY_FULLNAME_dooms__CircleCollider2D(...) \
INHERITANCE_INFORMATION_dooms__CircleCollider2D \
CURRENT_TYPE_ALIAS_dooms__CircleCollider2D \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__CircleCollider2D \
TYPE_CHECK_FUNCTION_CircleCollider2D \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_CircleCollider2D(...) GENERATE_BODY_FULLNAME_dooms__CircleCollider2D(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__CircleCollider2D(__VA_ARGS__)


//-------------------------------------------


