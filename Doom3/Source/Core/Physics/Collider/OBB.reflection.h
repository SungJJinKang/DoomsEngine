#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Physics\Collider\OBB.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Physics_Collider_OBB_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Physics\Collider\OBB.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Physics\Collider\OBB.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Physics_Collider_OBB_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__physics__OBB
#error "GENERATE_BODY_FULLNAME_dooms__physics__OBB already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__physics__OBB
#define CURRENT_TYPE_ALIAS_dooms__physics__OBB \
public: typedef dooms::physics::OBB Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__OBB
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__OBB \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2994906221; \
inline static const char* const TYPE_FULL_NAME = "dooms::physics::OBB"; \
inline static const char* const TYPE_SHORT_NAME = "OBB"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_OBB
#define TYPE_CHECK_FUNCTION_OBB \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__physics__OBB
#define GENERATE_BODY_FULLNAME_dooms__physics__OBB(...) \
CURRENT_TYPE_ALIAS_dooms__physics__OBB \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__OBB \
TYPE_CHECK_FUNCTION_OBB \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_OBB(...) GENERATE_BODY_FULLNAME_dooms__physics__OBB(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__physics__OBB(__VA_ARGS__)


//-------------------------------------------

