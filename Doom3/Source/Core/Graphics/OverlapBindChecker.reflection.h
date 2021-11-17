#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\OverlapBindChecker.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_OverlapBindChecker_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\OverlapBindChecker.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\OverlapBindChecker.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_OverlapBindChecker_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__OverlapBindChecker
#error "GENERATE_BODY_FULLNAME_dooms__graphics__OverlapBindChecker already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__graphics__OverlapBindChecker
#define CURRENT_TYPE_ALIAS_dooms__graphics__OverlapBindChecker \
public : \
typedef dooms::graphics::OverlapBindChecker Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__OverlapBindChecker
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__OverlapBindChecker \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 494570388; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::OverlapBindChecker"; \
inline static const char* const TYPE_SHORT_NAME = "OverlapBindChecker"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_OverlapBindChecker
#define TYPE_CHECK_FUNCTION_OverlapBindChecker \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__OverlapBindChecker
#define GENERATE_BODY_FULLNAME_dooms__graphics__OverlapBindChecker(...) \
CURRENT_TYPE_ALIAS_dooms__graphics__OverlapBindChecker \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__OverlapBindChecker \
TYPE_CHECK_FUNCTION_OverlapBindChecker \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_OverlapBindChecker(...) GENERATE_BODY_FULLNAME_dooms__graphics__OverlapBindChecker(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__OverlapBindChecker(__VA_ARGS__)


//-------------------------------------------


