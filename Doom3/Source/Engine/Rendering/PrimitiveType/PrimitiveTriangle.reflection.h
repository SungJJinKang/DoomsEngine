#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Engine_Rendering_PrimitiveType_PrimitiveTriangle_reflection_h


#ifdef __Source_Engine_Rendering_PrimitiveType_PrimitiveTriangle_reflection_h

#error "__Source_Engine_Rendering_PrimitiveType_PrimitiveTriangle_reflection_h already included, missing '#pragma once' in __Source_Engine_Rendering_PrimitiveType_PrimitiveTriangle_reflection_h"

#endif

#define __Source_Engine_Rendering_PrimitiveType_PrimitiveTriangle_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__PrimitiveTriangle
#error "GENERATE_BODY_FULLNAME_dooms__graphics__PrimitiveTriangle already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__graphics__PrimitiveTriangle
#define CURRENT_TYPE_ALIAS_dooms__graphics__PrimitiveTriangle \
typedef dooms::graphics::PrimitiveTriangle Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__PrimitiveTriangle
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__PrimitiveTriangle \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1673044004; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::PrimitiveTriangle"; \
inline static const char* const TYPE_SHORT_NAME = "PrimitiveTriangle"; \


#undef TYPE_CHECK_FUNCTION_PrimitiveTriangle
#define TYPE_CHECK_FUNCTION_PrimitiveTriangle \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__PrimitiveTriangle
#define GENERATE_BODY_FULLNAME_dooms__graphics__PrimitiveTriangle(...) \
CURRENT_TYPE_ALIAS_dooms__graphics__PrimitiveTriangle \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__PrimitiveTriangle \
TYPE_CHECK_FUNCTION_PrimitiveTriangle \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_PrimitiveTriangle(...) GENERATE_BODY_FULLNAME_dooms__graphics__PrimitiveTriangle(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__PrimitiveTriangle(__VA_ARGS__)


//-------------------------------------------


