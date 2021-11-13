#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\Portfolio\PhysicsDebuggerController.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_Portfolio_PhysicsDebuggerController_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\Portfolio\PhysicsDebuggerController.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\Portfolio\PhysicsDebuggerController.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_Portfolio_PhysicsDebuggerController_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__PhysicsDebuggerController
#error "GENERATE_BODY_FULLNAME_dooms__PhysicsDebuggerController already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__PhysicsDebuggerController
#define INHERITANCE_INFORMATION_dooms__PhysicsDebuggerController \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 343226959, 3576686641, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::PlainComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__PhysicsDebuggerController
#define CURRENT_TYPE_ALIAS_dooms__PhysicsDebuggerController \
public: typedef dooms::PhysicsDebuggerController Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PhysicsDebuggerController
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PhysicsDebuggerController \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 343226959; \
inline static const char* const TYPE_FULL_NAME = "dooms::PhysicsDebuggerController"; \
inline static const char* const TYPE_SHORT_NAME = "PhysicsDebuggerController"; 


#undef TYPE_CHECK_FUNCTION_PhysicsDebuggerController
#define TYPE_CHECK_FUNCTION_PhysicsDebuggerController \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__PhysicsDebuggerController
#define GENERATE_BODY_FULLNAME_dooms__PhysicsDebuggerController(...) \
INHERITANCE_INFORMATION_dooms__PhysicsDebuggerController \
CURRENT_TYPE_ALIAS_dooms__PhysicsDebuggerController \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PhysicsDebuggerController \
TYPE_CHECK_FUNCTION_PhysicsDebuggerController \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_PhysicsDebuggerController(...) GENERATE_BODY_FULLNAME_dooms__PhysicsDebuggerController(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__PhysicsDebuggerController(__VA_ARGS__)


//-------------------------------------------


