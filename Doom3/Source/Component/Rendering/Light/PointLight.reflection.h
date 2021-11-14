#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Light\PointLight.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_Rendering_Light_PointLight_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Light\PointLight.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Light\PointLight.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_Rendering_Light_PointLight_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__PointLight
#error "GENERATE_BODY_FULLNAME_dooms__PointLight already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__PointLight
#define INHERITANCE_INFORMATION_dooms__PointLight \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 2422500981, 2741420880, 1503232071, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 5 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::Light Base;


#undef CURRENT_TYPE_ALIAS_dooms__PointLight
#define CURRENT_TYPE_ALIAS_dooms__PointLight \
public: typedef dooms::PointLight Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PointLight
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PointLight \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2422500981; \
inline static const char* const TYPE_FULL_NAME = "dooms::PointLight"; \
inline static const char* const TYPE_SHORT_NAME = "PointLight"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_PointLight
#define TYPE_CHECK_FUNCTION_PointLight \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__PointLight
#define GENERATE_BODY_FULLNAME_dooms__PointLight(...) \
INHERITANCE_INFORMATION_dooms__PointLight \
CURRENT_TYPE_ALIAS_dooms__PointLight \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PointLight \
TYPE_CHECK_FUNCTION_PointLight \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_PointLight(...) GENERATE_BODY_FULLNAME_dooms__PointLight(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__PointLight(__VA_ARGS__)


//-------------------------------------------

