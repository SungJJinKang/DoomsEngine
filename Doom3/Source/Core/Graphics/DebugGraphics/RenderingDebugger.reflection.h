#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\DebugGraphics\RenderingDebugger.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_DebugGraphics_RenderingDebugger_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\DebugGraphics\RenderingDebugger.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\DebugGraphics\RenderingDebugger.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_DebugGraphics_RenderingDebugger_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebugger
#error "GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebugger already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__RenderingDebugger
#define INHERITANCE_INFORMATION_dooms__graphics__RenderingDebugger \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 1930869346, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::DObject Base;


#undef CURRENT_TYPE_ALIAS_dooms__graphics__RenderingDebugger
#define CURRENT_TYPE_ALIAS_dooms__graphics__RenderingDebugger \
public: typedef dooms::graphics::RenderingDebugger Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__RenderingDebugger
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__RenderingDebugger \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1930869346; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::RenderingDebugger"; \
inline static const char* const TYPE_SHORT_NAME = "RenderingDebugger"; 


#undef TYPE_CHECK_FUNCTION_RenderingDebugger
#define TYPE_CHECK_FUNCTION_RenderingDebugger \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebugger
#define GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebugger(...) \
INHERITANCE_INFORMATION_dooms__graphics__RenderingDebugger \
CURRENT_TYPE_ALIAS_dooms__graphics__RenderingDebugger \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__RenderingDebugger \
TYPE_CHECK_FUNCTION_RenderingDebugger \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_RenderingDebugger(...) GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebugger(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebugger(__VA_ARGS__)


//-------------------------------------------


