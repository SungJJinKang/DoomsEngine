#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Physics\Physics_Setting.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Physics_Physics_Setting_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Physics\Physics_Setting.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Physics\Physics_Setting.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Physics_Physics_Setting_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__physics__Physics_Setting
#error "GENERATE_BODY_FULLNAME_dooms__physics__Physics_Setting already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__physics__Physics_Setting
#define CURRENT_TYPE_ALIAS_dooms__physics__Physics_Setting \
public: typedef dooms::physics::Physics_Setting Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Physics_Setting
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Physics_Setting \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 848179968; \
inline static const char* const TYPE_FULL_NAME = "dooms::physics::Physics_Setting"; \
inline static const char* const TYPE_SHORT_NAME = "Physics_Setting"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Physics_Setting
#define TYPE_CHECK_FUNCTION_Physics_Setting \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__physics__Physics_Setting
#define GENERATE_BODY_FULLNAME_dooms__physics__Physics_Setting(...) \
CURRENT_TYPE_ALIAS_dooms__physics__Physics_Setting \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__physics__Physics_Setting \
TYPE_CHECK_FUNCTION_Physics_Setting \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Physics_Setting(...) GENERATE_BODY_FULLNAME_dooms__physics__Physics_Setting(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__physics__Physics_Setting(__VA_ARGS__)


//-------------------------------------------


