#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\AutoRotateAround.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_AutoRotateAround_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\AutoRotateAround.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\AutoRotateAround.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_AutoRotateAround_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__AutoRotateAround
#error "GENERATE_BODY_FULLNAME_dooms__AutoRotateAround already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__AutoRotateAround
#define INHERITANCE_INFORMATION_dooms__AutoRotateAround \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3166802544, 3576686641, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::PlainComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__AutoRotateAround
#define CURRENT_TYPE_ALIAS_dooms__AutoRotateAround \
public: typedef dooms::AutoRotateAround Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__AutoRotateAround
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__AutoRotateAround \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3166802544; \
inline static const char* const TYPE_FULL_NAME = "dooms::AutoRotateAround"; \
inline static const char* const TYPE_SHORT_NAME = "AutoRotateAround"; 


#undef TYPE_CHECK_FUNCTION_AutoRotateAround
#define TYPE_CHECK_FUNCTION_AutoRotateAround \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__AutoRotateAround
#define GENERATE_BODY_FULLNAME_dooms__AutoRotateAround(...) \
INHERITANCE_INFORMATION_dooms__AutoRotateAround \
CURRENT_TYPE_ALIAS_dooms__AutoRotateAround \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__AutoRotateAround \
TYPE_CHECK_FUNCTION_AutoRotateAround \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_AutoRotateAround(...) GENERATE_BODY_FULLNAME_dooms__AutoRotateAround(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__AutoRotateAround(__VA_ARGS__)


//-------------------------------------------


