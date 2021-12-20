#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_Reflection_Test_ReflectionTest_reflection_h


#ifdef __Source_Core_Reflection_Test_ReflectionTest_reflection_h

#error "__Source_Core_Reflection_Test_ReflectionTest_reflection_h already included, missing '#pragma once' in __Source_Core_Reflection_Test_ReflectionTest_reflection_h"

#endif

#define __Source_Core_Reflection_Test_ReflectionTest_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__TestStruct_ReflectionTest
#error "GENERATE_BODY_FULLNAME_dooms__TestStruct_ReflectionTest already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__TestStruct_ReflectionTest
#define CURRENT_TYPE_ALIAS_dooms__TestStruct_ReflectionTest \
typedef dooms::TestStruct_ReflectionTest Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__TestStruct_ReflectionTest
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__TestStruct_ReflectionTest \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3914775030; \
inline static const char* const TYPE_FULL_NAME = "dooms::TestStruct_ReflectionTest"; \
inline static const char* const TYPE_SHORT_NAME = "TestStruct_ReflectionTest"; \


#undef TYPE_CHECK_FUNCTION_TestStruct_ReflectionTest
#define TYPE_CHECK_FUNCTION_TestStruct_ReflectionTest \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__TestStruct_ReflectionTest
#define GENERATE_BODY_FULLNAME_dooms__TestStruct_ReflectionTest(...) \
CURRENT_TYPE_ALIAS_dooms__TestStruct_ReflectionTest \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__TestStruct_ReflectionTest \
TYPE_CHECK_FUNCTION_TestStruct_ReflectionTest \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_TestStruct_ReflectionTest(...) GENERATE_BODY_FULLNAME_dooms__TestStruct_ReflectionTest(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__TestStruct_ReflectionTest(__VA_ARGS__)


//-------------------------------------------


