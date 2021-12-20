#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_Physics_Collider_Circle2D_reflection_h


#ifdef __Source_Core_Physics_Collider_Circle2D_reflection_h

#error "__Source_Core_Physics_Collider_Circle2D_reflection_h already included, missing '#pragma once' in __Source_Core_Physics_Collider_Circle2D_reflection_h"

#endif

#define __Source_Core_Physics_Collider_Circle2D_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__physics__Circle2D
#error "GENERATE_BODY_FULLNAME_dooms__physics__Circle2D already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__physics__Circle2D
#define CURRENT_TYPE_ALIAS_dooms__physics__Circle2D \
public : \
typedef dooms::physics::Circle2D Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Circle2D
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Circle2D \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 4118877868; \
inline static const char* const TYPE_FULL_NAME = "dooms::physics::Circle2D"; \
inline static const char* const TYPE_SHORT_NAME = "Circle2D"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Circle2D
#define TYPE_CHECK_FUNCTION_Circle2D \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__physics__Circle2D
#define GENERATE_BODY_FULLNAME_dooms__physics__Circle2D(...) \
CURRENT_TYPE_ALIAS_dooms__physics__Circle2D \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Circle2D \
TYPE_CHECK_FUNCTION_Circle2D \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Circle2D(...) GENERATE_BODY_FULLNAME_dooms__physics__Circle2D(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__physics__Circle2D(__VA_ARGS__)


//-------------------------------------------


