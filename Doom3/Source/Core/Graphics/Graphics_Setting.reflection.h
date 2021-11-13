#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Graphics_Setting.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_Graphics_Setting_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Graphics_Setting.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Graphics_Setting.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_Graphics_Setting_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__Graphics_Setting
#error "GENERATE_BODY_FULLNAME_dooms__graphics__Graphics_Setting already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__graphics__Graphics_Setting
#define CURRENT_TYPE_ALIAS_dooms__graphics__Graphics_Setting \
public: typedef dooms::graphics::Graphics_Setting Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Graphics_Setting
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Graphics_Setting \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1775195333; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::Graphics_Setting"; \
inline static const char* const TYPE_SHORT_NAME = "Graphics_Setting"; 


#undef TYPE_CHECK_FUNCTION_Graphics_Setting
#define TYPE_CHECK_FUNCTION_Graphics_Setting \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__Graphics_Setting
#define GENERATE_BODY_FULLNAME_dooms__graphics__Graphics_Setting(...) \
CURRENT_TYPE_ALIAS_dooms__graphics__Graphics_Setting \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Graphics_Setting \
TYPE_CHECK_FUNCTION_Graphics_Setting \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Graphics_Setting(...) GENERATE_BODY_FULLNAME_dooms__graphics__Graphics_Setting(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__Graphics_Setting(__VA_ARGS__)


//-------------------------------------------


