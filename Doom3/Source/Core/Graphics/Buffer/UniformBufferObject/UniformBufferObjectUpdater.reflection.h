#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_Graphics_Buffer_UniformBufferObject_UniformBufferObjectUpdater_reflection_h


#ifdef __Source_Core_Graphics_Buffer_UniformBufferObject_UniformBufferObjectUpdater_reflection_h

#error "__Source_Core_Graphics_Buffer_UniformBufferObject_UniformBufferObjectUpdater_reflection_h already included, missing '#pragma once' in __Source_Core_Graphics_Buffer_UniformBufferObject_UniformBufferObjectUpdater_reflection_h"

#endif

#define __Source_Core_Graphics_Buffer_UniformBufferObject_UniformBufferObjectUpdater_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__UniformBufferObjectUpdater
#error "GENERATE_BODY_FULLNAME_dooms__graphics__UniformBufferObjectUpdater already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__graphics__UniformBufferObjectUpdater
#define CURRENT_TYPE_ALIAS_dooms__graphics__UniformBufferObjectUpdater \
public : \
typedef dooms::graphics::UniformBufferObjectUpdater Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__UniformBufferObjectUpdater
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__UniformBufferObjectUpdater \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3706686641; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::UniformBufferObjectUpdater"; \
inline static const char* const TYPE_SHORT_NAME = "UniformBufferObjectUpdater"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_UniformBufferObjectUpdater
#define TYPE_CHECK_FUNCTION_UniformBufferObjectUpdater \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__UniformBufferObjectUpdater
#define GENERATE_BODY_FULLNAME_dooms__graphics__UniformBufferObjectUpdater(...) \
CURRENT_TYPE_ALIAS_dooms__graphics__UniformBufferObjectUpdater \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__UniformBufferObjectUpdater \
TYPE_CHECK_FUNCTION_UniformBufferObjectUpdater \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_UniformBufferObjectUpdater(...) GENERATE_BODY_FULLNAME_dooms__graphics__UniformBufferObjectUpdater(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__UniformBufferObjectUpdater(__VA_ARGS__)


//-------------------------------------------


