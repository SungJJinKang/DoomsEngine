#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Graphics_Server.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_Graphics_Server_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Graphics_Server.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Graphics_Server.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_Graphics_Server_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__Graphics_Server
#error "GENERATE_BODY_FULLNAME_dooms__graphics__Graphics_Server already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__Graphics_Server
#define INHERITANCE_INFORMATION_dooms__graphics__Graphics_Server \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 385065569, 3668408939, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::IGameFlow Base;


#undef CURRENT_TYPE_ALIAS_dooms__graphics__Graphics_Server
#define CURRENT_TYPE_ALIAS_dooms__graphics__Graphics_Server \
public: typedef dooms::graphics::Graphics_Server Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Graphics_Server
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Graphics_Server \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 385065569; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::Graphics_Server"; \
inline static const char* const TYPE_SHORT_NAME = "Graphics_Server"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Graphics_Server
#define TYPE_CHECK_FUNCTION_Graphics_Server \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__Graphics_Server
#define GENERATE_BODY_FULLNAME_dooms__graphics__Graphics_Server(...) \
INHERITANCE_INFORMATION_dooms__graphics__Graphics_Server \
CURRENT_TYPE_ALIAS_dooms__graphics__Graphics_Server \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Graphics_Server \
TYPE_CHECK_FUNCTION_Graphics_Server \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Graphics_Server(...) GENERATE_BODY_FULLNAME_dooms__graphics__Graphics_Server(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__Graphics_Server(__VA_ARGS__)


//-------------------------------------------


