#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\TestComponent2.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_TestComponent2_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\TestComponent2.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\TestComponent2.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_TestComponent2_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__TestComponent2
#error "GENERATE_BODY_FULLNAME_dooms__TestComponent2 already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__TestComponent2
#define INHERITANCE_INFORMATION_dooms__TestComponent2 \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 911693594, 699055446, 3576686641, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 5 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::TestComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__TestComponent2
#define CURRENT_TYPE_ALIAS_dooms__TestComponent2 \
public: typedef dooms::TestComponent2 Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__TestComponent2
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__TestComponent2 \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 911693594; \
inline static const char* const TYPE_FULL_NAME = "dooms::TestComponent2"; \
inline static const char* const TYPE_SHORT_NAME = "TestComponent2"; 


#undef TYPE_CHECK_FUNCTION_TestComponent2
#define TYPE_CHECK_FUNCTION_TestComponent2 \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__TestComponent2
#define GENERATE_BODY_FULLNAME_dooms__TestComponent2(...) \
INHERITANCE_INFORMATION_dooms__TestComponent2 \
CURRENT_TYPE_ALIAS_dooms__TestComponent2 \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__TestComponent2 \
TYPE_CHECK_FUNCTION_TestComponent2 \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_TestComponent2(...) GENERATE_BODY_FULLNAME_dooms__TestComponent2(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__TestComponent2(__VA_ARGS__)


//-------------------------------------------

