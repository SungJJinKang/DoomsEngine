#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\Portfolio\PortfolioComponent.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_Portfolio_PortfolioComponent_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\Portfolio\PortfolioComponent.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\Portfolio\PortfolioComponent.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_Portfolio_PortfolioComponent_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__PortfolioComponent
#error "GENERATE_BODY_FULLNAME_dooms__PortfolioComponent already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__PortfolioComponent
#define INHERITANCE_INFORMATION_dooms__PortfolioComponent \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 1158593708, 3576686641, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::PlainComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__PortfolioComponent
#define CURRENT_TYPE_ALIAS_dooms__PortfolioComponent \
public: typedef dooms::PortfolioComponent Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PortfolioComponent
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PortfolioComponent \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1158593708; \
inline static const char* const TYPE_FULL_NAME = "dooms::PortfolioComponent"; \
inline static const char* const TYPE_SHORT_NAME = "PortfolioComponent"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_PortfolioComponent
#define TYPE_CHECK_FUNCTION_PortfolioComponent \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__PortfolioComponent
#define GENERATE_BODY_FULLNAME_dooms__PortfolioComponent(...) \
INHERITANCE_INFORMATION_dooms__PortfolioComponent \
CURRENT_TYPE_ALIAS_dooms__PortfolioComponent \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PortfolioComponent \
TYPE_CHECK_FUNCTION_PortfolioComponent \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_PortfolioComponent(...) GENERATE_BODY_FULLNAME_dooms__PortfolioComponent(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__PortfolioComponent(__VA_ARGS__)


//-------------------------------------------


