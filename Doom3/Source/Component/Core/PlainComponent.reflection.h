#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\Core\PlainComponent.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_Core_PlainComponent_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\Core\PlainComponent.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\Core\PlainComponent.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_Core_PlainComponent_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__PlainComponent
#error "GENERATE_BODY_FULLNAME_dooms__PlainComponent already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__PlainComponent
#define INHERITANCE_INFORMATION_dooms__PlainComponent \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3576686641, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::Component Base;


#undef CURRENT_TYPE_ALIAS_dooms__PlainComponent
#define CURRENT_TYPE_ALIAS_dooms__PlainComponent \
public: typedef dooms::PlainComponent Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PlainComponent
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PlainComponent \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3576686641; \
inline static const char* const TYPE_FULL_NAME = "dooms::PlainComponent"; \
inline static const char* const TYPE_SHORT_NAME = "PlainComponent"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_PlainComponent
#define TYPE_CHECK_FUNCTION_PlainComponent \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__PlainComponent
#define GENERATE_BODY_FULLNAME_dooms__PlainComponent(...) \
INHERITANCE_INFORMATION_dooms__PlainComponent \
CURRENT_TYPE_ALIAS_dooms__PlainComponent \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PlainComponent \
TYPE_CHECK_FUNCTION_PlainComponent \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_PlainComponent(...) GENERATE_BODY_FULLNAME_dooms__PlainComponent(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__PlainComponent(__VA_ARGS__)


//-------------------------------------------


