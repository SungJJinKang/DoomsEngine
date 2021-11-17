#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Color.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_Color_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Color.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Color.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_Color_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__Color
#error "GENERATE_BODY_FULLNAME_dooms__graphics__Color already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__graphics__Color
#define CURRENT_TYPE_ALIAS_dooms__graphics__Color \
public : \
typedef dooms::graphics::Color Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Color
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Color \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3019058562; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::Color"; \
inline static const char* const TYPE_SHORT_NAME = "Color"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Color
#define TYPE_CHECK_FUNCTION_Color \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__Color
#define GENERATE_BODY_FULLNAME_dooms__graphics__Color(...) \
CURRENT_TYPE_ALIAS_dooms__graphics__Color \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Color \
TYPE_CHECK_FUNCTION_Color \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Color(...) GENERATE_BODY_FULLNAME_dooms__graphics__Color(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__Color(__VA_ARGS__)


//-------------------------------------------


