#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Physics\Collider\Plane.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Physics_Collider_Plane_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Physics\Collider\Plane.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Physics\Collider\Plane.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Physics_Collider_Plane_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__physics__Plane
#error "GENERATE_BODY_FULLNAME_dooms__physics__Plane already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__physics__Plane
#define CURRENT_TYPE_ALIAS_dooms__physics__Plane \
public: typedef dooms::physics::Plane Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Plane
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Plane \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3338765717; \
inline static const char* const TYPE_FULL_NAME = "dooms::physics::Plane"; \
inline static const char* const TYPE_SHORT_NAME = "Plane"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Plane
#define TYPE_CHECK_FUNCTION_Plane \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__physics__Plane
#define GENERATE_BODY_FULLNAME_dooms__physics__Plane(...) \
CURRENT_TYPE_ALIAS_dooms__physics__Plane \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Plane \
TYPE_CHECK_FUNCTION_Plane \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Plane(...) GENERATE_BODY_FULLNAME_dooms__physics__Plane(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__physics__Plane(__VA_ARGS__)


//-------------------------------------------


