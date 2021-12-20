#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Reflection\Test\TestDObject.cpp


#ifdef _Source_Core_Reflection_Test_TestDObject_reflection_h

#error "_Source_Core_Reflection_Test_TestDObject_reflection_h already included, missing '#pragma once' in _Source_Core_Reflection_Test_TestDObject_reflection_h"

#endif

#define _Source_Core_Reflection_Test_TestDObject_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__TestDObject
#error "GENERATE_BODY_FULLNAME_dooms__TestDObject already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__TestDObject
#define INHERITANCE_INFORMATION_dooms__TestDObject \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 3010861289, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__TestDObject
#define CLONE_OBJECT_dooms__TestDObject \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::TestDObject>::value == true) && (std::is_base_of<dooms::DObject, dooms::TestDObject>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::TestDObject>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__TestDObject
#define CURRENT_TYPE_ALIAS_dooms__TestDObject \
public : \
typedef dooms::TestDObject Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__TestDObject
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__TestDObject \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3010861289; \
inline static const char* const TYPE_FULL_NAME = "dooms::TestDObject"; \
inline static const char* const TYPE_SHORT_NAME = "TestDObject"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_TestDObject
#define TYPE_CHECK_FUNCTION_TestDObject \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__TestDObject
#define GENERATE_BODY_FULLNAME_dooms__TestDObject(...) \
INHERITANCE_INFORMATION_dooms__TestDObject \
CLONE_OBJECT_dooms__TestDObject \
CURRENT_TYPE_ALIAS_dooms__TestDObject \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__TestDObject \
TYPE_CHECK_FUNCTION_TestDObject \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_TestDObject(...) GENERATE_BODY_FULLNAME_dooms__TestDObject(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__TestDObject(__VA_ARGS__)


//-------------------------------------------


