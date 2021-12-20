#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_GameLogic_CustomComponent_Portfolio_OverDrawVisualizationDebugger_reflection_h


#ifdef __Source_GameLogic_CustomComponent_Portfolio_OverDrawVisualizationDebugger_reflection_h

#error "__Source_GameLogic_CustomComponent_Portfolio_OverDrawVisualizationDebugger_reflection_h already included, missing '#pragma once' in __Source_GameLogic_CustomComponent_Portfolio_OverDrawVisualizationDebugger_reflection_h"

#endif

#define __Source_GameLogic_CustomComponent_Portfolio_OverDrawVisualizationDebugger_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__OverDrawVisualizationDebugger
#error "GENERATE_BODY_FULLNAME_dooms__OverDrawVisualizationDebugger already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__OverDrawVisualizationDebugger
#define INHERITANCE_INFORMATION_dooms__OverDrawVisualizationDebugger \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 937246513, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::Component Base;


#undef CLONE_OBJECT_dooms__OverDrawVisualizationDebugger
#define CLONE_OBJECT_dooms__OverDrawVisualizationDebugger \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::OverDrawVisualizationDebugger>::value == true) && (std::is_base_of<dooms::DObject, dooms::OverDrawVisualizationDebugger>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::OverDrawVisualizationDebugger>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__OverDrawVisualizationDebugger
#define CURRENT_TYPE_ALIAS_dooms__OverDrawVisualizationDebugger \
public : \
typedef dooms::OverDrawVisualizationDebugger Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__OverDrawVisualizationDebugger
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__OverDrawVisualizationDebugger \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 937246513; \
inline static const char* const TYPE_FULL_NAME = "dooms::OverDrawVisualizationDebugger"; \
inline static const char* const TYPE_SHORT_NAME = "OverDrawVisualizationDebugger"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_OverDrawVisualizationDebugger
#define TYPE_CHECK_FUNCTION_OverDrawVisualizationDebugger \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__OverDrawVisualizationDebugger
#define GENERATE_BODY_FULLNAME_dooms__OverDrawVisualizationDebugger(...) \
INHERITANCE_INFORMATION_dooms__OverDrawVisualizationDebugger \
CLONE_OBJECT_dooms__OverDrawVisualizationDebugger \
CURRENT_TYPE_ALIAS_dooms__OverDrawVisualizationDebugger \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__OverDrawVisualizationDebugger \
TYPE_CHECK_FUNCTION_OverDrawVisualizationDebugger \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_OverDrawVisualizationDebugger(...) GENERATE_BODY_FULLNAME_dooms__OverDrawVisualizationDebugger(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__OverDrawVisualizationDebugger(__VA_ARGS__)


//-------------------------------------------


