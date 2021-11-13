#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Light\Light.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_Rendering_Light_Light_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Light\Light.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Light\Light.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_Rendering_Light_Light_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__Light
#error "GENERATE_BODY_FULLNAME_dooms__Light already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__Light
#define INHERITANCE_INFORMATION_dooms__Light \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 2741420880, 1503232071, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::ServerComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__Light
#define CURRENT_TYPE_ALIAS_dooms__Light \
public: typedef dooms::Light Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Light
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Light \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2741420880; \
inline static const char* const TYPE_FULL_NAME = "dooms::Light"; \
inline static const char* const TYPE_SHORT_NAME = "Light"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Light
#define TYPE_CHECK_FUNCTION_Light \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__Light
#define GENERATE_BODY_FULLNAME_dooms__Light(...) \
INHERITANCE_INFORMATION_dooms__Light \
CURRENT_TYPE_ALIAS_dooms__Light \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Light \
TYPE_CHECK_FUNCTION_Light \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Light(...) GENERATE_BODY_FULLNAME_dooms__Light(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__Light(__VA_ARGS__)


//-------------------------------------------


