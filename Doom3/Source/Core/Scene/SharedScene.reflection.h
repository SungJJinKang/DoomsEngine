#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Scene\SharedScene.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Scene_SharedScene_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Scene\SharedScene.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Scene\SharedScene.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Scene_SharedScene_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__SharedScene
#error "GENERATE_BODY_FULLNAME_dooms__SharedScene already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__SharedScene
#define INHERITANCE_INFORMATION_dooms__SharedScene \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 463505080, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__SharedScene
#define CLONE_OBJECT_dooms__SharedScene \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::SharedScene>::value == true) && (std::is_base_of<dooms::DObject, dooms::SharedScene>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::SharedScene>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__SharedScene
#define CURRENT_TYPE_ALIAS_dooms__SharedScene \
public : \
typedef dooms::SharedScene Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__SharedScene
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__SharedScene \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 463505080; \
inline static const char* const TYPE_FULL_NAME = "dooms::SharedScene"; \
inline static const char* const TYPE_SHORT_NAME = "SharedScene"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_SharedScene
#define TYPE_CHECK_FUNCTION_SharedScene \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__SharedScene
#define GENERATE_BODY_FULLNAME_dooms__SharedScene(...) \
INHERITANCE_INFORMATION_dooms__SharedScene \
CLONE_OBJECT_dooms__SharedScene \
CURRENT_TYPE_ALIAS_dooms__SharedScene \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__SharedScene \
TYPE_CHECK_FUNCTION_SharedScene \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_SharedScene(...) GENERATE_BODY_FULLNAME_dooms__SharedScene(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__SharedScene(__VA_ARGS__)


//-------------------------------------------


