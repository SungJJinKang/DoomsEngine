#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\MeshCollider.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_PhysicsComponent_MeshCollider_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\MeshCollider.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\MeshCollider.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_PhysicsComponent_MeshCollider_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__MeshCollider
#error "GENERATE_BODY_FULLNAME_dooms__MeshCollider already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__MeshCollider
#define INHERITANCE_INFORMATION_dooms__MeshCollider \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 1793318124, 3608780617, 960295289, 1503232071, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 6 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::Collider3DComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__MeshCollider
#define CURRENT_TYPE_ALIAS_dooms__MeshCollider \
public: typedef dooms::MeshCollider Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshCollider
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshCollider \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1793318124; \
inline static const char* const TYPE_FULL_NAME = "dooms::MeshCollider"; \
inline static const char* const TYPE_SHORT_NAME = "MeshCollider"; 


#undef TYPE_CHECK_FUNCTION_MeshCollider
#define TYPE_CHECK_FUNCTION_MeshCollider \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__MeshCollider
#define GENERATE_BODY_FULLNAME_dooms__MeshCollider(...) \
INHERITANCE_INFORMATION_dooms__MeshCollider \
CURRENT_TYPE_ALIAS_dooms__MeshCollider \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshCollider \
TYPE_CHECK_FUNCTION_MeshCollider \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_MeshCollider(...) GENERATE_BODY_FULLNAME_dooms__MeshCollider(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__MeshCollider(__VA_ARGS__)


//-------------------------------------------


