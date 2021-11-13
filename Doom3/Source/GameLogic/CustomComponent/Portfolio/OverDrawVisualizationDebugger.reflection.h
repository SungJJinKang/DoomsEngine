#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\Portfolio\OverDrawVisualizationDebugger.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_Portfolio_OverDrawVisualizationDebugger_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\Portfolio\OverDrawVisualizationDebugger.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\Portfolio\OverDrawVisualizationDebugger.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_Portfolio_OverDrawVisualizationDebugger_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__OverDrawVisualizationDebugger
#error "GENERATE_BODY_FULLNAME_dooms__OverDrawVisualizationDebugger already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__OverDrawVisualizationDebugger
#define INHERITANCE_INFORMATION_dooms__OverDrawVisualizationDebugger \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 937246513, 3576686641, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::PlainComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__OverDrawVisualizationDebugger
#define CURRENT_TYPE_ALIAS_dooms__OverDrawVisualizationDebugger \
public: typedef dooms::OverDrawVisualizationDebugger Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__OverDrawVisualizationDebugger
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__OverDrawVisualizationDebugger \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 937246513; \
inline static const char* const TYPE_FULL_NAME = "dooms::OverDrawVisualizationDebugger"; \
inline static const char* const TYPE_SHORT_NAME = "OverDrawVisualizationDebugger"; 


#undef TYPE_CHECK_FUNCTION_OverDrawVisualizationDebugger
#define TYPE_CHECK_FUNCTION_OverDrawVisualizationDebugger \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__OverDrawVisualizationDebugger
#define GENERATE_BODY_FULLNAME_dooms__OverDrawVisualizationDebugger(...) \
INHERITANCE_INFORMATION_dooms__OverDrawVisualizationDebugger \
CURRENT_TYPE_ALIAS_dooms__OverDrawVisualizationDebugger \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__OverDrawVisualizationDebugger \
TYPE_CHECK_FUNCTION_OverDrawVisualizationDebugger \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_OverDrawVisualizationDebugger(...) GENERATE_BODY_FULLNAME_dooms__OverDrawVisualizationDebugger(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__OverDrawVisualizationDebugger(__VA_ARGS__)


//-------------------------------------------


