#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Physics\Collider\AABB.cpp


#ifdef _Source_Core_Physics_Collider_AABB_reflection_h

#error "_Source_Core_Physics_Collider_AABB_reflection_h already included, missing '#pragma once' in _Source_Core_Physics_Collider_AABB_reflection_h"

#endif

#define _Source_Core_Physics_Collider_AABB_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__physics__AABB3D
#error "GENERATE_BODY_FULLNAME_dooms__physics__AABB3D already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__physics__AABB3D
#define CURRENT_TYPE_ALIAS_dooms__physics__AABB3D \
public : \
typedef dooms::physics::AABB3D Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__AABB3D
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__AABB3D \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 504734176; \
inline static const char* const TYPE_FULL_NAME = "dooms::physics::AABB3D"; \
inline static const char* const TYPE_SHORT_NAME = "AABB3D"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_AABB3D
#define TYPE_CHECK_FUNCTION_AABB3D \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__physics__AABB3D
#define GENERATE_BODY_FULLNAME_dooms__physics__AABB3D(...) \
CURRENT_TYPE_ALIAS_dooms__physics__AABB3D \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__AABB3D \
TYPE_CHECK_FUNCTION_AABB3D \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_AABB3D(...) GENERATE_BODY_FULLNAME_dooms__physics__AABB3D(__VA_ARGS__)


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__physics__AABB2D
#error "GENERATE_BODY_FULLNAME_dooms__physics__AABB2D already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__physics__AABB2D
#define CURRENT_TYPE_ALIAS_dooms__physics__AABB2D \
public : \
typedef dooms::physics::AABB2D Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__AABB2D
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__AABB2D \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 308233036; \
inline static const char* const TYPE_FULL_NAME = "dooms::physics::AABB2D"; \
inline static const char* const TYPE_SHORT_NAME = "AABB2D"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_AABB2D
#define TYPE_CHECK_FUNCTION_AABB2D \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__physics__AABB2D
#define GENERATE_BODY_FULLNAME_dooms__physics__AABB2D(...) \
CURRENT_TYPE_ALIAS_dooms__physics__AABB2D \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__AABB2D \
TYPE_CHECK_FUNCTION_AABB2D \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_AABB2D(...) GENERATE_BODY_FULLNAME_dooms__physics__AABB2D(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__physics__AABB2D(__VA_ARGS__)


//-------------------------------------------


