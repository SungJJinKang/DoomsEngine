#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Time\Time_Server.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Time_Time_Server_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Time\Time_Server.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Time\Time_Server.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Time_Time_Server_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__time__Time_Server
#error "GENERATE_BODY_FULLNAME_dooms__time__Time_Server already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__time__Time_Server
#define INHERITANCE_INFORMATION_dooms__time__Time_Server \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3679049012, 3668408939, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::IGameFlow Base;


#undef CURRENT_TYPE_ALIAS_dooms__time__Time_Server
#define CURRENT_TYPE_ALIAS_dooms__time__Time_Server \
public: typedef dooms::time::Time_Server Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__time__Time_Server
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__time__Time_Server \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3679049012; \
inline static const char* const TYPE_FULL_NAME = "dooms::time::Time_Server"; \
inline static const char* const TYPE_SHORT_NAME = "Time_Server"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Time_Server
#define TYPE_CHECK_FUNCTION_Time_Server \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__time__Time_Server
#define GENERATE_BODY_FULLNAME_dooms__time__Time_Server(...) \
INHERITANCE_INFORMATION_dooms__time__Time_Server \
CURRENT_TYPE_ALIAS_dooms__time__Time_Server \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__time__Time_Server \
TYPE_CHECK_FUNCTION_Time_Server \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Time_Server(...) GENERATE_BODY_FULLNAME_dooms__time__Time_Server(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__time__Time_Server(__VA_ARGS__)


//-------------------------------------------


