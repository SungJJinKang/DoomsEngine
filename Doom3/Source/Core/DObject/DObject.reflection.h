#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\DObject\DObject.cpp


#ifdef _Source_Core_DObject_DObject_reflection_h

#error "_Source_Core_DObject_DObject_reflection_h already included, missing '#pragma once' in _Source_Core_DObject_DObject_reflection_h"

#endif

#define _Source_Core_DObject_DObject_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__DObjectContructorParams
#error "GENERATE_BODY_FULLNAME_dooms__DObjectContructorParams already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__DObjectContructorParams
#define CURRENT_TYPE_ALIAS_dooms__DObjectContructorParams \
typedef dooms::DObjectContructorParams Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DObjectContructorParams
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DObjectContructorParams \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1908514145; \
inline static const char* const TYPE_FULL_NAME = "dooms::DObjectContructorParams"; \
inline static const char* const TYPE_SHORT_NAME = "DObjectContructorParams"; \


#undef TYPE_CHECK_FUNCTION_DObjectContructorParams
#define TYPE_CHECK_FUNCTION_DObjectContructorParams \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__DObjectContructorParams
#define GENERATE_BODY_FULLNAME_dooms__DObjectContructorParams(...) \
CURRENT_TYPE_ALIAS_dooms__DObjectContructorParams \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DObjectContructorParams \
TYPE_CHECK_FUNCTION_DObjectContructorParams \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DObjectContructorParams(...) GENERATE_BODY_FULLNAME_dooms__DObjectContructorParams(__VA_ARGS__)


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__DObject__DObjectProperties
#error "GENERATE_BODY_FULLNAME_dooms__DObject__DObjectProperties already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__DObject__DObjectProperties
#define CURRENT_TYPE_ALIAS_dooms__DObject__DObjectProperties \
typedef dooms::DObject::DObjectProperties Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DObject__DObjectProperties
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DObject__DObjectProperties \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1186928914; \
inline static const char* const TYPE_FULL_NAME = "dooms::DObject::DObjectProperties"; \
inline static const char* const TYPE_SHORT_NAME = "DObjectProperties"; \


#undef TYPE_CHECK_FUNCTION_DObjectProperties
#define TYPE_CHECK_FUNCTION_DObjectProperties \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__DObject__DObjectProperties
#define GENERATE_BODY_FULLNAME_dooms__DObject__DObjectProperties(...) \
CURRENT_TYPE_ALIAS_dooms__DObject__DObjectProperties \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DObject__DObjectProperties \
TYPE_CHECK_FUNCTION_DObjectProperties \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DObjectProperties(...) GENERATE_BODY_FULLNAME_dooms__DObject__DObjectProperties(__VA_ARGS__)


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__DObject
#error "GENERATE_BODY_FULLNAME_dooms__DObject already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__DObject
#define INHERITANCE_INFORMATION_dooms__DObject \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 1 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \


#undef CLONE_OBJECT_dooms__DObject
#define CLONE_OBJECT_dooms__DObject \
public : \
virtual dooms::DObject* CloneObject() const { assert(false); return nullptr; }


#undef CURRENT_TYPE_ALIAS_dooms__DObject
#define CURRENT_TYPE_ALIAS_dooms__DObject \
public : \
typedef dooms::DObject Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DObject
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DObject \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3969188510; \
inline static const char* const TYPE_FULL_NAME = "dooms::DObject"; \
inline static const char* const TYPE_SHORT_NAME = "DObject"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_DObject
#define TYPE_CHECK_FUNCTION_DObject \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__DObject
#define GENERATE_BODY_FULLNAME_dooms__DObject(...) \
INHERITANCE_INFORMATION_dooms__DObject \
CLONE_OBJECT_dooms__DObject \
CURRENT_TYPE_ALIAS_dooms__DObject \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DObject \
TYPE_CHECK_FUNCTION_DObject \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DObject(...) GENERATE_BODY_FULLNAME_dooms__DObject(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__DObject(__VA_ARGS__)


//-------------------------------------------


