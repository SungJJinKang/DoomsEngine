#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Buffer\UniformBufferObjectUpdater.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_Buffer_UniformBufferObjectUpdater_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Buffer\UniformBufferObjectUpdater.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Buffer\UniformBufferObjectUpdater.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_Buffer_UniformBufferObjectUpdater_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__UniformBufferObjectUpdater
#error "GENERATE_BODY_FULLNAME_dooms__graphics__UniformBufferObjectUpdater already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__graphics__UniformBufferObjectUpdater
#define CURRENT_TYPE_ALIAS_dooms__graphics__UniformBufferObjectUpdater \
public: typedef dooms::graphics::UniformBufferObjectUpdater Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__UniformBufferObjectUpdater
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__UniformBufferObjectUpdater \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3706686641; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::UniformBufferObjectUpdater"; \
inline static const char* const TYPE_SHORT_NAME = "UniformBufferObjectUpdater"; 


#undef TYPE_CHECK_FUNCTION_UniformBufferObjectUpdater
#define TYPE_CHECK_FUNCTION_UniformBufferObjectUpdater \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


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


