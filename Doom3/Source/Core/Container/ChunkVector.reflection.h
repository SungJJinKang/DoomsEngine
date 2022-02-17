#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_Container_ChunkVector_reflection_h


#ifdef __Source_Core_Container_ChunkVector_reflection_h

#error "__Source_Core_Container_ChunkVector_reflection_h already included, missing '#pragma once' in __Source_Core_Container_ChunkVector_reflection_h"

#endif

#define __Source_Core_Container_ChunkVector_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__ChunkVector
#error "GENERATE_BODY_FULLNAME_dooms__ChunkVector already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__ChunkVector
#define CURRENT_TYPE_ALIAS_dooms__ChunkVector \
typedef dooms::ChunkVector Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ChunkVector
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ChunkVector \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 31807476; \
inline static const char* const TYPE_FULL_NAME = "dooms::ChunkVector"; \
inline static const char* const TYPE_SHORT_NAME = "ChunkVector"; \


#undef TYPE_CHECK_FUNCTION_ChunkVector
#define TYPE_CHECK_FUNCTION_ChunkVector \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__ChunkVector
#define GENERATE_BODY_FULLNAME_dooms__ChunkVector(...) \
CURRENT_TYPE_ALIAS_dooms__ChunkVector \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ChunkVector \
TYPE_CHECK_FUNCTION_ChunkVector \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ChunkVector(...) GENERATE_BODY_FULLNAME_dooms__ChunkVector(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__ChunkVector(__VA_ARGS__)


//-------------------------------------------


