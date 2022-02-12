#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Engine_EngineGUI_GUIModules_Modules_SceneGUI_reflection_h


#ifdef __Source_Engine_EngineGUI_GUIModules_Modules_SceneGUI_reflection_h

#error "__Source_Engine_EngineGUI_GUIModules_Modules_SceneGUI_reflection_h already included, missing '#pragma once' in __Source_Engine_EngineGUI_GUIModules_Modules_SceneGUI_reflection_h"

#endif

#define __Source_Engine_EngineGUI_GUIModules_Modules_SceneGUI_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__ui__SceneGUI
#error "GENERATE_BODY_FULLNAME_dooms__ui__SceneGUI already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__ui__SceneGUI
#define INHERITANCE_INFORMATION_dooms__ui__SceneGUI \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 367305417, 3340247602, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::ui::EngineGUIModule Base;


#undef CLONE_OBJECT_dooms__ui__SceneGUI
#define CLONE_OBJECT_dooms__ui__SceneGUI \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::ui::SceneGUI>::value == true) && (std::is_base_of<dooms::DObject, dooms::ui::SceneGUI>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::ui::SceneGUI>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__ui__SceneGUI
#define CURRENT_TYPE_ALIAS_dooms__ui__SceneGUI \
public : \
typedef dooms::ui::SceneGUI Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ui__SceneGUI
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ui__SceneGUI \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 367305417; \
inline static const char* const TYPE_FULL_NAME = "dooms::ui::SceneGUI"; \
inline static const char* const TYPE_SHORT_NAME = "SceneGUI"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_SceneGUI
#define TYPE_CHECK_FUNCTION_SceneGUI \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__ui__SceneGUI
#define GENERATE_BODY_FULLNAME_dooms__ui__SceneGUI(...) \
INHERITANCE_INFORMATION_dooms__ui__SceneGUI \
CLONE_OBJECT_dooms__ui__SceneGUI \
CURRENT_TYPE_ALIAS_dooms__ui__SceneGUI \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ui__SceneGUI \
TYPE_CHECK_FUNCTION_SceneGUI \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_SceneGUI(...) GENERATE_BODY_FULLNAME_dooms__ui__SceneGUI(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__ui__SceneGUI(__VA_ARGS__)


//-------------------------------------------

