#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_Graphics_RenderingDebugger_RenderingDebugger_reflection_h


#ifdef __Source_Core_Graphics_RenderingDebugger_RenderingDebugger_reflection_h

#error "__Source_Core_Graphics_RenderingDebugger_RenderingDebugger_reflection_h already included, missing '#pragma once' in __Source_Core_Graphics_RenderingDebugger_RenderingDebugger_reflection_h"

#endif

#define __Source_Core_Graphics_RenderingDebugger_RenderingDebugger_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebugger
#error "GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebugger already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__RenderingDebugger
#define INHERITANCE_INFORMATION_dooms__graphics__RenderingDebugger \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 1930869346, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__graphics__RenderingDebugger
#define CLONE_OBJECT_dooms__graphics__RenderingDebugger \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::graphics::RenderingDebugger>::value == true) && (std::is_base_of<dooms::DObject, dooms::graphics::RenderingDebugger>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::graphics::RenderingDebugger>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__graphics__RenderingDebugger
#define CURRENT_TYPE_ALIAS_dooms__graphics__RenderingDebugger \
public : \
typedef dooms::graphics::RenderingDebugger Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__RenderingDebugger
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__RenderingDebugger \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1930869346; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::RenderingDebugger"; \
inline static const char* const TYPE_SHORT_NAME = "RenderingDebugger"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_RenderingDebugger
#define TYPE_CHECK_FUNCTION_RenderingDebugger \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebugger
#define GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebugger(...) \
INHERITANCE_INFORMATION_dooms__graphics__RenderingDebugger \
CLONE_OBJECT_dooms__graphics__RenderingDebugger \
CURRENT_TYPE_ALIAS_dooms__graphics__RenderingDebugger \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__RenderingDebugger \
TYPE_CHECK_FUNCTION_RenderingDebugger \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_RenderingDebugger(...) GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebugger(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebugger(__VA_ARGS__)


//-------------------------------------------


