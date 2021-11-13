#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\SphereCollider3D.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_PhysicsComponent_SphereCollider3D_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\SphereCollider3D.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\SphereCollider3D.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_PhysicsComponent_SphereCollider3D_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__SphereCollider3D
#error "GENERATE_BODY_FULLNAME_dooms__SphereCollider3D already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__SphereCollider3D
#define INHERITANCE_INFORMATION_dooms__SphereCollider3D \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3805051692, 3608780617, 960295289, 1503232071, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 6 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::Collider3DComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__SphereCollider3D
#define CURRENT_TYPE_ALIAS_dooms__SphereCollider3D \
public: typedef dooms::SphereCollider3D Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__SphereCollider3D
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__SphereCollider3D \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3805051692; \
inline static const char* const TYPE_FULL_NAME = "dooms::SphereCollider3D"; \
inline static const char* const TYPE_SHORT_NAME = "SphereCollider3D"; 


#undef TYPE_CHECK_FUNCTION_SphereCollider3D
#define TYPE_CHECK_FUNCTION_SphereCollider3D \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__SphereCollider3D
#define GENERATE_BODY_FULLNAME_dooms__SphereCollider3D(...) \
INHERITANCE_INFORMATION_dooms__SphereCollider3D \
CURRENT_TYPE_ALIAS_dooms__SphereCollider3D \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__SphereCollider3D \
TYPE_CHECK_FUNCTION_SphereCollider3D \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_SphereCollider3D(...) GENERATE_BODY_FULLNAME_dooms__SphereCollider3D(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__SphereCollider3D(__VA_ARGS__)


//-------------------------------------------


