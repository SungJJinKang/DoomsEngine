#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\PrimitiveType\PrimitiveLine.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_PrimitiveType_PrimitiveLine_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\PrimitiveType\PrimitiveLine.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\PrimitiveType\PrimitiveLine.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_PrimitiveType_PrimitiveLine_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__PrimitiveLine
#error "GENERATE_BODY_FULLNAME_dooms__graphics__PrimitiveLine already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__graphics__PrimitiveLine
#define CURRENT_TYPE_ALIAS_dooms__graphics__PrimitiveLine \
public: typedef dooms::graphics::PrimitiveLine Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__PrimitiveLine
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__PrimitiveLine \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2774699867; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::PrimitiveLine"; \
inline static const char* const TYPE_SHORT_NAME = "PrimitiveLine"; 


#undef TYPE_CHECK_FUNCTION_PrimitiveLine
#define TYPE_CHECK_FUNCTION_PrimitiveLine \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__PrimitiveLine
#define GENERATE_BODY_FULLNAME_dooms__graphics__PrimitiveLine(...) \
CURRENT_TYPE_ALIAS_dooms__graphics__PrimitiveLine \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__PrimitiveLine \
TYPE_CHECK_FUNCTION_PrimitiveLine \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_PrimitiveLine(...) GENERATE_BODY_FULLNAME_dooms__graphics__PrimitiveLine(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__PrimitiveLine(__VA_ARGS__)


//-------------------------------------------


