#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\LightManager.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_LightManager_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\LightManager.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\LightManager.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_LightManager_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__LightManager
#error "GENERATE_BODY_FULLNAME_dooms__graphics__LightManager already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__LightManager
#define INHERITANCE_INFORMATION_dooms__graphics__LightManager \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 963987378, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::DObject Base;


#undef CURRENT_TYPE_ALIAS_dooms__graphics__LightManager
#define CURRENT_TYPE_ALIAS_dooms__graphics__LightManager \
public: typedef dooms::graphics::LightManager Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__LightManager
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__LightManager \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 963987378; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::LightManager"; \
inline static const char* const TYPE_SHORT_NAME = "LightManager"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_LightManager
#define TYPE_CHECK_FUNCTION_LightManager \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__LightManager
#define GENERATE_BODY_FULLNAME_dooms__graphics__LightManager(...) \
INHERITANCE_INFORMATION_dooms__graphics__LightManager \
CURRENT_TYPE_ALIAS_dooms__graphics__LightManager \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__LightManager \
TYPE_CHECK_FUNCTION_LightManager \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_LightManager(...) GENERATE_BODY_FULLNAME_dooms__graphics__LightManager(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__LightManager(__VA_ARGS__)


//-------------------------------------------


