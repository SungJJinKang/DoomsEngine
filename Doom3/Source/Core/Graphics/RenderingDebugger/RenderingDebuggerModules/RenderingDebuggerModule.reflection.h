#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_Graphics_RenderingDebugger_RenderingDebuggerModules_RenderingDebuggerModule_reflection_h


#ifdef __Source_Core_Graphics_RenderingDebugger_RenderingDebuggerModules_RenderingDebuggerModule_reflection_h

#error "__Source_Core_Graphics_RenderingDebugger_RenderingDebuggerModules_RenderingDebuggerModule_reflection_h already included, missing '#pragma once' in __Source_Core_Graphics_RenderingDebugger_RenderingDebuggerModules_RenderingDebuggerModule_reflection_h"

#endif

#define __Source_Core_Graphics_RenderingDebugger_RenderingDebuggerModules_RenderingDebuggerModule_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebuggerModule
#error "GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebuggerModule already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__RenderingDebuggerModule
#define INHERITANCE_INFORMATION_dooms__graphics__RenderingDebuggerModule \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 3005919411, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__graphics__RenderingDebuggerModule
#define CLONE_OBJECT_dooms__graphics__RenderingDebuggerModule \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::graphics::RenderingDebuggerModule>::value == true) && (std::is_base_of<dooms::DObject, dooms::graphics::RenderingDebuggerModule>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::graphics::RenderingDebuggerModule>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__graphics__RenderingDebuggerModule
#define CURRENT_TYPE_ALIAS_dooms__graphics__RenderingDebuggerModule \
public : \
typedef dooms::graphics::RenderingDebuggerModule Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__RenderingDebuggerModule
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__RenderingDebuggerModule \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3005919411; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::RenderingDebuggerModule"; \
inline static const char* const TYPE_SHORT_NAME = "RenderingDebuggerModule"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_RenderingDebuggerModule
#define TYPE_CHECK_FUNCTION_RenderingDebuggerModule \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebuggerModule
#define GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebuggerModule(...) \
INHERITANCE_INFORMATION_dooms__graphics__RenderingDebuggerModule \
CLONE_OBJECT_dooms__graphics__RenderingDebuggerModule \
CURRENT_TYPE_ALIAS_dooms__graphics__RenderingDebuggerModule \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__RenderingDebuggerModule \
TYPE_CHECK_FUNCTION_RenderingDebuggerModule \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_RenderingDebuggerModule(...) GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebuggerModule(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__RenderingDebuggerModule(__VA_ARGS__)


//-------------------------------------------


