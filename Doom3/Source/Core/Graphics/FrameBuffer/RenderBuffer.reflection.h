#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\FrameBuffer\RenderBuffer.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_FrameBuffer_RenderBuffer_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\FrameBuffer\RenderBuffer.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\FrameBuffer\RenderBuffer.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_FrameBuffer_RenderBuffer_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__RenderBuffer
#error "GENERATE_BODY_FULLNAME_dooms__graphics__RenderBuffer already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__RenderBuffer
#define INHERITANCE_INFORMATION_dooms__graphics__RenderBuffer \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3889749315, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::DObject Base;


#undef CURRENT_TYPE_ALIAS_dooms__graphics__RenderBuffer
#define CURRENT_TYPE_ALIAS_dooms__graphics__RenderBuffer \
public: typedef dooms::graphics::RenderBuffer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__RenderBuffer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__RenderBuffer \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3889749315; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::RenderBuffer"; \
inline static const char* const TYPE_SHORT_NAME = "RenderBuffer"; 


#undef TYPE_CHECK_FUNCTION_RenderBuffer
#define TYPE_CHECK_FUNCTION_RenderBuffer \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__RenderBuffer
#define GENERATE_BODY_FULLNAME_dooms__graphics__RenderBuffer(...) \
INHERITANCE_INFORMATION_dooms__graphics__RenderBuffer \
CURRENT_TYPE_ALIAS_dooms__graphics__RenderBuffer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__RenderBuffer \
TYPE_CHECK_FUNCTION_RenderBuffer \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_RenderBuffer(...) GENERATE_BODY_FULLNAME_dooms__graphics__RenderBuffer(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__RenderBuffer(__VA_ARGS__)


//-------------------------------------------


