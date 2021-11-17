#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Scene\SharedSceneSetting.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Scene_SharedSceneSetting_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Scene\SharedSceneSetting.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Scene\SharedSceneSetting.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Scene_SharedSceneSetting_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__SharedSceneSetting
#error "GENERATE_BODY_FULLNAME_dooms__SharedSceneSetting already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__SharedSceneSetting
#define INHERITANCE_INFORMATION_dooms__SharedSceneSetting \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 1979459991, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__SharedSceneSetting
#define CLONE_OBJECT_dooms__SharedSceneSetting \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::SharedSceneSetting>::value == true) && (std::is_base_of<dooms::DObject, dooms::SharedSceneSetting>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::SharedSceneSetting>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__SharedSceneSetting
#define CURRENT_TYPE_ALIAS_dooms__SharedSceneSetting \
public : \
typedef dooms::SharedSceneSetting Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__SharedSceneSetting
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__SharedSceneSetting \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1979459991; \
inline static const char* const TYPE_FULL_NAME = "dooms::SharedSceneSetting"; \
inline static const char* const TYPE_SHORT_NAME = "SharedSceneSetting"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_SharedSceneSetting
#define TYPE_CHECK_FUNCTION_SharedSceneSetting \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__SharedSceneSetting
#define GENERATE_BODY_FULLNAME_dooms__SharedSceneSetting(...) \
INHERITANCE_INFORMATION_dooms__SharedSceneSetting \
CLONE_OBJECT_dooms__SharedSceneSetting \
CURRENT_TYPE_ALIAS_dooms__SharedSceneSetting \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__SharedSceneSetting \
TYPE_CHECK_FUNCTION_SharedSceneSetting \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_SharedSceneSetting(...) GENERATE_BODY_FULLNAME_dooms__SharedSceneSetting(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__SharedSceneSetting(__VA_ARGS__)


//-------------------------------------------


