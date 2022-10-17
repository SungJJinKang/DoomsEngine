#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Engine_EngineGUI_GUIModules_Modules_DrawCallCounterGUI_reflection_h


#ifdef __Source_Engine_EngineGUI_GUIModules_Modules_DrawCallCounterGUI_reflection_h

#error "__Source_Engine_EngineGUI_GUIModules_Modules_DrawCallCounterGUI_reflection_h already included, missing '#pragma once' in __Source_Engine_EngineGUI_GUIModules_Modules_DrawCallCounterGUI_reflection_h"

#endif

#define __Source_Engine_EngineGUI_GUIModules_Modules_DrawCallCounterGUI_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__ui__DrawCallCounterGUI
#error "GENERATE_BODY_FULLNAME_dooms__ui__DrawCallCounterGUI already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__ui__DrawCallCounterGUI
#define INHERITANCE_INFORMATION_dooms__ui__DrawCallCounterGUI \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 982479568, 3340247602, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::ui::EngineGUIModule Base;


#undef CLONE_OBJECT_dooms__ui__DrawCallCounterGUI
#define CLONE_OBJECT_dooms__ui__DrawCallCounterGUI \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::ui::DrawCallCounterGUI>::value == true) && (std::is_base_of<dooms::DObject, dooms::ui::DrawCallCounterGUI>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::ui::DrawCallCounterGUI>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__ui__DrawCallCounterGUI
#define CURRENT_TYPE_ALIAS_dooms__ui__DrawCallCounterGUI \
public : \
typedef dooms::ui::DrawCallCounterGUI Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ui__DrawCallCounterGUI
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ui__DrawCallCounterGUI \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 982479568; \
inline static const char* const TYPE_FULL_NAME = "dooms::ui::DrawCallCounterGUI"; \
inline static const char* const TYPE_SHORT_NAME = "DrawCallCounterGUI"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_DrawCallCounterGUI
#define TYPE_CHECK_FUNCTION_DrawCallCounterGUI \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__ui__DrawCallCounterGUI
#define GENERATE_BODY_FULLNAME_dooms__ui__DrawCallCounterGUI(...) \
INHERITANCE_INFORMATION_dooms__ui__DrawCallCounterGUI \
CLONE_OBJECT_dooms__ui__DrawCallCounterGUI \
CURRENT_TYPE_ALIAS_dooms__ui__DrawCallCounterGUI \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ui__DrawCallCounterGUI \
TYPE_CHECK_FUNCTION_DrawCallCounterGUI \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DrawCallCounterGUI(...) GENERATE_BODY_FULLNAME_dooms__ui__DrawCallCounterGUI(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__ui__DrawCallCounterGUI(__VA_ARGS__)


//-------------------------------------------


