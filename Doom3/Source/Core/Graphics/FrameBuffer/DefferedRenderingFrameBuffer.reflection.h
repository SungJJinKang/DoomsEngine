#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\FrameBuffer\DefferedRenderingFrameBuffer.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_FrameBuffer_DefferedRenderingFrameBuffer_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\FrameBuffer\DefferedRenderingFrameBuffer.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\FrameBuffer\DefferedRenderingFrameBuffer.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_FrameBuffer_DefferedRenderingFrameBuffer_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__DefferedRenderingFrameBuffer
#error "GENERATE_BODY_FULLNAME_dooms__graphics__DefferedRenderingFrameBuffer already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__DefferedRenderingFrameBuffer
#define INHERITANCE_INFORMATION_dooms__graphics__DefferedRenderingFrameBuffer \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 1132735981, 521766154, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::graphics::FrameBuffer Base;


#undef CURRENT_TYPE_ALIAS_dooms__graphics__DefferedRenderingFrameBuffer
#define CURRENT_TYPE_ALIAS_dooms__graphics__DefferedRenderingFrameBuffer \
public: typedef dooms::graphics::DefferedRenderingFrameBuffer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__DefferedRenderingFrameBuffer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__DefferedRenderingFrameBuffer \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1132735981; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::DefferedRenderingFrameBuffer"; \
inline static const char* const TYPE_SHORT_NAME = "DefferedRenderingFrameBuffer"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_DefferedRenderingFrameBuffer
#define TYPE_CHECK_FUNCTION_DefferedRenderingFrameBuffer \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__DefferedRenderingFrameBuffer
#define GENERATE_BODY_FULLNAME_dooms__graphics__DefferedRenderingFrameBuffer(...) \
INHERITANCE_INFORMATION_dooms__graphics__DefferedRenderingFrameBuffer \
CURRENT_TYPE_ALIAS_dooms__graphics__DefferedRenderingFrameBuffer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__DefferedRenderingFrameBuffer \
TYPE_CHECK_FUNCTION_DefferedRenderingFrameBuffer \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DefferedRenderingFrameBuffer(...) GENERATE_BODY_FULLNAME_dooms__graphics__DefferedRenderingFrameBuffer(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__DefferedRenderingFrameBuffer(__VA_ARGS__)


//-------------------------------------------


