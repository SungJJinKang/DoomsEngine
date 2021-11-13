#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\Core\ServerComponent.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_Core_ServerComponent_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\Core\ServerComponent.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\Core\ServerComponent.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_Core_ServerComponent_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__ServerComponent
#error "GENERATE_BODY_FULLNAME_dooms__ServerComponent already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__ServerComponent
#define INHERITANCE_INFORMATION_dooms__ServerComponent \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 1503232071, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::Component Base;


#undef CURRENT_TYPE_ALIAS_dooms__ServerComponent
#define CURRENT_TYPE_ALIAS_dooms__ServerComponent \
public: typedef dooms::ServerComponent Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ServerComponent
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ServerComponent \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1503232071; \
inline static const char* const TYPE_FULL_NAME = "dooms::ServerComponent"; \
inline static const char* const TYPE_SHORT_NAME = "ServerComponent"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_ServerComponent
#define TYPE_CHECK_FUNCTION_ServerComponent \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__ServerComponent
#define GENERATE_BODY_FULLNAME_dooms__ServerComponent(...) \
INHERITANCE_INFORMATION_dooms__ServerComponent \
CURRENT_TYPE_ALIAS_dooms__ServerComponent \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ServerComponent \
TYPE_CHECK_FUNCTION_ServerComponent \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ServerComponent(...) GENERATE_BODY_FULLNAME_dooms__ServerComponent(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__ServerComponent(__VA_ARGS__)


//-------------------------------------------


