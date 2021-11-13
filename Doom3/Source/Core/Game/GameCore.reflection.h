#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Game\GameCore.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Game_GameCore_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Game\GameCore.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Game\GameCore.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Game_GameCore_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__GameCore
#error "GENERATE_BODY_FULLNAME_dooms__GameCore already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__GameCore
#define INHERITANCE_INFORMATION_dooms__GameCore \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3657779232, 3668408939, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::IGameFlow Base;


#undef CURRENT_TYPE_ALIAS_dooms__GameCore
#define CURRENT_TYPE_ALIAS_dooms__GameCore \
public: typedef dooms::GameCore Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__GameCore
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__GameCore \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3657779232; \
inline static const char* const TYPE_FULL_NAME = "dooms::GameCore"; \
inline static const char* const TYPE_SHORT_NAME = "GameCore"; 


#undef TYPE_CHECK_FUNCTION_GameCore
#define TYPE_CHECK_FUNCTION_GameCore \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__GameCore
#define GENERATE_BODY_FULLNAME_dooms__GameCore(...) \
INHERITANCE_INFORMATION_dooms__GameCore \
CURRENT_TYPE_ALIAS_dooms__GameCore \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__GameCore \
TYPE_CHECK_FUNCTION_GameCore \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_GameCore(...) GENERATE_BODY_FULLNAME_dooms__GameCore(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__GameCore(__VA_ARGS__)


//-------------------------------------------


