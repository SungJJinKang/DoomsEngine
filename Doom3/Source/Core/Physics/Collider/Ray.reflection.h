#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Physics\Collider\Ray.cpp


#ifdef _Source_Core_Physics_Collider_Ray_reflection_h

#error "_Source_Core_Physics_Collider_Ray_reflection_h already included, missing '#pragma once' in _Source_Core_Physics_Collider_Ray_reflection_h"

#endif

#define _Source_Core_Physics_Collider_Ray_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__physics__Ray
#error "GENERATE_BODY_FULLNAME_dooms__physics__Ray already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__physics__Ray
#define CURRENT_TYPE_ALIAS_dooms__physics__Ray \
public : \
typedef dooms::physics::Ray Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Ray
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Ray \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2055390917; \
inline static const char* const TYPE_FULL_NAME = "dooms::physics::Ray"; \
inline static const char* const TYPE_SHORT_NAME = "Ray"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Ray
#define TYPE_CHECK_FUNCTION_Ray \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__physics__Ray
#define GENERATE_BODY_FULLNAME_dooms__physics__Ray(...) \
CURRENT_TYPE_ALIAS_dooms__physics__Ray \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Ray \
TYPE_CHECK_FUNCTION_Ray \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Ray(...) GENERATE_BODY_FULLNAME_dooms__physics__Ray(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__physics__Ray(__VA_ARGS__)


//-------------------------------------------


