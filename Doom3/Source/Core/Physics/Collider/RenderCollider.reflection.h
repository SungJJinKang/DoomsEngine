#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Physics\Collider\RenderCollider.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Physics_Collider_RenderCollider_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Physics\Collider\RenderCollider.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Physics\Collider\RenderCollider.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Physics_Collider_RenderCollider_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__physics__RenderCollider
#error "GENERATE_BODY_FULLNAME_dooms__physics__RenderCollider already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__physics__RenderCollider
#define CURRENT_TYPE_ALIAS_dooms__physics__RenderCollider \
public : \
typedef dooms::physics::RenderCollider Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__RenderCollider
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__RenderCollider \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2408510197; \
inline static const char* const TYPE_FULL_NAME = "dooms::physics::RenderCollider"; \
inline static const char* const TYPE_SHORT_NAME = "RenderCollider"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_RenderCollider
#define TYPE_CHECK_FUNCTION_RenderCollider \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__physics__RenderCollider
#define GENERATE_BODY_FULLNAME_dooms__physics__RenderCollider(...) \
CURRENT_TYPE_ALIAS_dooms__physics__RenderCollider \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__RenderCollider \
TYPE_CHECK_FUNCTION_RenderCollider \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_RenderCollider(...) GENERATE_BODY_FULLNAME_dooms__physics__RenderCollider(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__physics__RenderCollider(__VA_ARGS__)


//-------------------------------------------


