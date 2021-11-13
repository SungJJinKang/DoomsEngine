#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\Portfolio\RenderingAABBController.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_Portfolio_RenderingAABBController_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\Portfolio\RenderingAABBController.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\Portfolio\RenderingAABBController.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_Portfolio_RenderingAABBController_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__RenderingAABBController
#error "GENERATE_BODY_FULLNAME_dooms__RenderingAABBController already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__RenderingAABBController
#define INHERITANCE_INFORMATION_dooms__RenderingAABBController \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 2685490677, 3576686641, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::PlainComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__RenderingAABBController
#define CURRENT_TYPE_ALIAS_dooms__RenderingAABBController \
public: typedef dooms::RenderingAABBController Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__RenderingAABBController
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__RenderingAABBController \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2685490677; \
inline static const char* const TYPE_FULL_NAME = "dooms::RenderingAABBController"; \
inline static const char* const TYPE_SHORT_NAME = "RenderingAABBController"; 


#undef TYPE_CHECK_FUNCTION_RenderingAABBController
#define TYPE_CHECK_FUNCTION_RenderingAABBController \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__RenderingAABBController
#define GENERATE_BODY_FULLNAME_dooms__RenderingAABBController(...) \
INHERITANCE_INFORMATION_dooms__RenderingAABBController \
CURRENT_TYPE_ALIAS_dooms__RenderingAABBController \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__RenderingAABBController \
TYPE_CHECK_FUNCTION_RenderingAABBController \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_RenderingAABBController(...) GENERATE_BODY_FULLNAME_dooms__RenderingAABBController(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__RenderingAABBController(__VA_ARGS__)


//-------------------------------------------


