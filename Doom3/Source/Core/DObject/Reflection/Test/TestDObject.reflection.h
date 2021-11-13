#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\DObject\Reflection\Test\TestDObject.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_DObject_Reflection_Test_TestDObject_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\DObject\Reflection\Test\TestDObject.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\DObject\Reflection\Test\TestDObject.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_DObject_Reflection_Test_TestDObject_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__TestDObject
#error "GENERATE_BODY_FULLNAME_dooms__TestDObject already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__TestDObject
#define INHERITANCE_INFORMATION_dooms__TestDObject \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3010861289, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::DObject Base;


#undef CURRENT_TYPE_ALIAS_dooms__TestDObject
#define CURRENT_TYPE_ALIAS_dooms__TestDObject \
public: typedef dooms::TestDObject Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__TestDObject
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__TestDObject \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3010861289; \
inline static const char* const TYPE_FULL_NAME = "dooms::TestDObject"; \
inline static const char* const TYPE_SHORT_NAME = "TestDObject"; 


#undef TYPE_CHECK_FUNCTION_TestDObject
#define TYPE_CHECK_FUNCTION_TestDObject \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__TestDObject
#define GENERATE_BODY_FULLNAME_dooms__TestDObject(...) \
INHERITANCE_INFORMATION_dooms__TestDObject \
CURRENT_TYPE_ALIAS_dooms__TestDObject \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__TestDObject \
TYPE_CHECK_FUNCTION_TestDObject \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_TestDObject(...) GENERATE_BODY_FULLNAME_dooms__TestDObject(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__TestDObject(__VA_ARGS__)


//-------------------------------------------


