#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_ResourceManagement_Thread_RunnableThread_JobThread_reflection_h


#ifdef __Source_Core_ResourceManagement_Thread_RunnableThread_JobThread_reflection_h

#error "__Source_Core_ResourceManagement_Thread_RunnableThread_JobThread_reflection_h already included, missing '#pragma once' in __Source_Core_ResourceManagement_Thread_RunnableThread_JobThread_reflection_h"

#endif

#define __Source_Core_ResourceManagement_Thread_RunnableThread_JobThread_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__thread__JobThread
#error "GENERATE_BODY_FULLNAME_dooms__thread__JobThread already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__thread__JobThread
#define INHERITANCE_INFORMATION_dooms__thread__JobThread \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 3481447628, 2618687433, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::thread::RunnableThread Base;


#undef CLONE_OBJECT_dooms__thread__JobThread
#define CLONE_OBJECT_dooms__thread__JobThread \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::thread::JobThread>::value == true) && (std::is_base_of<dooms::DObject, dooms::thread::JobThread>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::thread::JobThread>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__thread__JobThread
#define CURRENT_TYPE_ALIAS_dooms__thread__JobThread \
public : \
typedef dooms::thread::JobThread Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__thread__JobThread
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__thread__JobThread \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3481447628; \
inline static const char* const TYPE_FULL_NAME = "dooms::thread::JobThread"; \
inline static const char* const TYPE_SHORT_NAME = "JobThread"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_JobThread
#define TYPE_CHECK_FUNCTION_JobThread \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__thread__JobThread
#define GENERATE_BODY_FULLNAME_dooms__thread__JobThread(...) \
INHERITANCE_INFORMATION_dooms__thread__JobThread \
CLONE_OBJECT_dooms__thread__JobThread \
CURRENT_TYPE_ALIAS_dooms__thread__JobThread \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__thread__JobThread \
TYPE_CHECK_FUNCTION_JobThread \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_JobThread(...) GENERATE_BODY_FULLNAME_dooms__thread__JobThread(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__thread__JobThread(__VA_ARGS__)


//-------------------------------------------


