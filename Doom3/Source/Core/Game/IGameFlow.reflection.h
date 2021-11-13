#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Game\IGameFlow.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Game_IGameFlow_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Game\IGameFlow.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Game\IGameFlow.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Game_IGameFlow_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__IGameFlow
#error "GENERATE_BODY_FULLNAME_dooms__IGameFlow already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__IGameFlow
#define INHERITANCE_INFORMATION_dooms__IGameFlow \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3668408939, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::DObject Base;


#undef CURRENT_TYPE_ALIAS_dooms__IGameFlow
#define CURRENT_TYPE_ALIAS_dooms__IGameFlow \
public: typedef dooms::IGameFlow Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__IGameFlow
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__IGameFlow \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3668408939; \
inline static const char* const TYPE_FULL_NAME = "dooms::IGameFlow"; \
inline static const char* const TYPE_SHORT_NAME = "IGameFlow"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_IGameFlow
#define TYPE_CHECK_FUNCTION_IGameFlow \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__IGameFlow
#define GENERATE_BODY_FULLNAME_dooms__IGameFlow(...) \
INHERITANCE_INFORMATION_dooms__IGameFlow \
CURRENT_TYPE_ALIAS_dooms__IGameFlow \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__IGameFlow \
TYPE_CHECK_FUNCTION_IGameFlow \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_IGameFlow(...) GENERATE_BODY_FULLNAME_dooms__IGameFlow(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__IGameFlow(__VA_ARGS__)


//-------------------------------------------


