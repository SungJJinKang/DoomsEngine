#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Physics\Collider\ColliderSolution.cpp


#ifdef _Source_Core_Physics_Collider_ColliderSolution_reflection_h

#error "_Source_Core_Physics_Collider_ColliderSolution_reflection_h already included, missing '#pragma once' in _Source_Core_Physics_Collider_ColliderSolution_reflection_h"

#endif

#define _Source_Core_Physics_Collider_ColliderSolution_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__physics__ColliderSolution
#error "GENERATE_BODY_FULLNAME_dooms__physics__ColliderSolution already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__physics__ColliderSolution
#define CURRENT_TYPE_ALIAS_dooms__physics__ColliderSolution \
public : \
typedef dooms::physics::ColliderSolution Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__ColliderSolution
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__ColliderSolution \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2039693723; \
inline static const char* const TYPE_FULL_NAME = "dooms::physics::ColliderSolution"; \
inline static const char* const TYPE_SHORT_NAME = "ColliderSolution"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_ColliderSolution
#define TYPE_CHECK_FUNCTION_ColliderSolution \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__physics__ColliderSolution
#define GENERATE_BODY_FULLNAME_dooms__physics__ColliderSolution(...) \
CURRENT_TYPE_ALIAS_dooms__physics__ColliderSolution \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__ColliderSolution \
TYPE_CHECK_FUNCTION_ColliderSolution \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ColliderSolution(...) GENERATE_BODY_FULLNAME_dooms__physics__ColliderSolution(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__physics__ColliderSolution(__VA_ARGS__)


//-------------------------------------------


