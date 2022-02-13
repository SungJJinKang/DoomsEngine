#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Engine_Rendering_PrimitiveType_PrimitiveLine_reflection_h


#ifdef __Source_Engine_Rendering_PrimitiveType_PrimitiveLine_reflection_h

#error "__Source_Engine_Rendering_PrimitiveType_PrimitiveLine_reflection_h already included, missing '#pragma once' in __Source_Engine_Rendering_PrimitiveType_PrimitiveLine_reflection_h"

#endif

#define __Source_Engine_Rendering_PrimitiveType_PrimitiveLine_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__PrimitiveLine
#error "GENERATE_BODY_FULLNAME_dooms__graphics__PrimitiveLine already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__graphics__PrimitiveLine
#define CURRENT_TYPE_ALIAS_dooms__graphics__PrimitiveLine \
typedef dooms::graphics::PrimitiveLine Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__PrimitiveLine
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__PrimitiveLine \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2774699867; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::PrimitiveLine"; \
inline static const char* const TYPE_SHORT_NAME = "PrimitiveLine"; \


#undef TYPE_CHECK_FUNCTION_PrimitiveLine
#define TYPE_CHECK_FUNCTION_PrimitiveLine \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


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


