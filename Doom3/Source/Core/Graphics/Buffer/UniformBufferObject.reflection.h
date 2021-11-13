#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Buffer\UniformBufferObject.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_Buffer_UniformBufferObject_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Buffer\UniformBufferObject.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Buffer\UniformBufferObject.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_Buffer_UniformBufferObject_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__UniformBufferObject
#error "GENERATE_BODY_FULLNAME_dooms__graphics__UniformBufferObject already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__UniformBufferObject
#define INHERITANCE_INFORMATION_dooms__graphics__UniformBufferObject \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 4172709252, 2373964349, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::graphics::Buffer Base;


#undef CURRENT_TYPE_ALIAS_dooms__graphics__UniformBufferObject
#define CURRENT_TYPE_ALIAS_dooms__graphics__UniformBufferObject \
public: typedef dooms::graphics::UniformBufferObject Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__UniformBufferObject
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__UniformBufferObject \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 4172709252; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::UniformBufferObject"; \
inline static const char* const TYPE_SHORT_NAME = "UniformBufferObject"; 


#undef TYPE_CHECK_FUNCTION_UniformBufferObject
#define TYPE_CHECK_FUNCTION_UniformBufferObject \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__UniformBufferObject
#define GENERATE_BODY_FULLNAME_dooms__graphics__UniformBufferObject(...) \
INHERITANCE_INFORMATION_dooms__graphics__UniformBufferObject \
CURRENT_TYPE_ALIAS_dooms__graphics__UniformBufferObject \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__UniformBufferObject \
TYPE_CHECK_FUNCTION_UniformBufferObject \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_UniformBufferObject(...) GENERATE_BODY_FULLNAME_dooms__graphics__UniformBufferObject(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__UniformBufferObject(__VA_ARGS__)


//-------------------------------------------


