#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_Scene_Layer_Layer_reflection_h


#ifdef __Source_Core_Scene_Layer_Layer_reflection_h

#error "__Source_Core_Scene_Layer_Layer_reflection_h already included, missing '#pragma once' in __Source_Core_Scene_Layer_Layer_reflection_h"

#endif

#define __Source_Core_Scene_Layer_Layer_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__Layer
#error "GENERATE_BODY_FULLNAME_dooms__Layer already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__Layer
#define CURRENT_TYPE_ALIAS_dooms__Layer \
typedef dooms::Layer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Layer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Layer \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1816209029; \
inline static const char* const TYPE_FULL_NAME = "dooms::Layer"; \
inline static const char* const TYPE_SHORT_NAME = "Layer"; \


#undef TYPE_CHECK_FUNCTION_Layer
#define TYPE_CHECK_FUNCTION_Layer \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__Layer
#define GENERATE_BODY_FULLNAME_dooms__Layer(...) \
CURRENT_TYPE_ALIAS_dooms__Layer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Layer \
TYPE_CHECK_FUNCTION_Layer \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Layer(...) GENERATE_BODY_FULLNAME_dooms__Layer(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__Layer(__VA_ARGS__)


//-------------------------------------------


