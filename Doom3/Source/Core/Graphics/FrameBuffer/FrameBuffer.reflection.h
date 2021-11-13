#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\FrameBuffer\FrameBuffer.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_FrameBuffer_FrameBuffer_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\FrameBuffer\FrameBuffer.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\FrameBuffer\FrameBuffer.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_FrameBuffer_FrameBuffer_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__FrameBuffer
#error "GENERATE_BODY_FULLNAME_dooms__graphics__FrameBuffer already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__FrameBuffer
#define INHERITANCE_INFORMATION_dooms__graphics__FrameBuffer \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 521766154, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::DObject Base;


#undef CURRENT_TYPE_ALIAS_dooms__graphics__FrameBuffer
#define CURRENT_TYPE_ALIAS_dooms__graphics__FrameBuffer \
public: typedef dooms::graphics::FrameBuffer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__FrameBuffer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__FrameBuffer \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 521766154; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::FrameBuffer"; \
inline static const char* const TYPE_SHORT_NAME = "FrameBuffer"; 


#undef TYPE_CHECK_FUNCTION_FrameBuffer
#define TYPE_CHECK_FUNCTION_FrameBuffer \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__FrameBuffer
#define GENERATE_BODY_FULLNAME_dooms__graphics__FrameBuffer(...) \
INHERITANCE_INFORMATION_dooms__graphics__FrameBuffer \
CURRENT_TYPE_ALIAS_dooms__graphics__FrameBuffer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__FrameBuffer \
TYPE_CHECK_FUNCTION_FrameBuffer \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_FrameBuffer(...) GENERATE_BODY_FULLNAME_dooms__graphics__FrameBuffer(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__FrameBuffer(__VA_ARGS__)


//-------------------------------------------


