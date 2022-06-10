#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_ResourceManagement_Thread_JobPool_reflection_h


#ifdef __Source_Core_ResourceManagement_Thread_JobPool_reflection_h

#error "__Source_Core_ResourceManagement_Thread_JobPool_reflection_h already included, missing '#pragma once' in __Source_Core_ResourceManagement_Thread_JobPool_reflection_h"

#endif

#define __Source_Core_ResourceManagement_Thread_JobPool_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__thread__JobPool
#error "GENERATE_BODY_FULLNAME_dooms__thread__JobPool already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__thread__JobPool
#define INHERITANCE_INFORMATION_dooms__thread__JobPool \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 950084399, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__thread__JobPool
#define CLONE_OBJECT_dooms__thread__JobPool \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::thread::JobPool>::value == true) && (std::is_base_of<dooms::DObject, dooms::thread::JobPool>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::thread::JobPool>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__thread__JobPool
#define CURRENT_TYPE_ALIAS_dooms__thread__JobPool \
public : \
typedef dooms::thread::JobPool Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__thread__JobPool
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__thread__JobPool \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 950084399; \
inline static const char* const TYPE_FULL_NAME = "dooms::thread::JobPool"; \
inline static const char* const TYPE_SHORT_NAME = "JobPool"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_JobPool
#define TYPE_CHECK_FUNCTION_JobPool \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__thread__JobPool
#define GENERATE_BODY_FULLNAME_dooms__thread__JobPool(...) \
INHERITANCE_INFORMATION_dooms__thread__JobPool \
CLONE_OBJECT_dooms__thread__JobPool \
CURRENT_TYPE_ALIAS_dooms__thread__JobPool \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__thread__JobPool \
TYPE_CHECK_FUNCTION_JobPool \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_JobPool(...) GENERATE_BODY_FULLNAME_dooms__thread__JobPool(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__thread__JobPool(__VA_ARGS__)


//-------------------------------------------


