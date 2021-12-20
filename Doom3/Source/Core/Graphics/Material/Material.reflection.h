#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_Graphics_Material_Material_reflection_h


#ifdef __Source_Core_Graphics_Material_Material_reflection_h

#error "__Source_Core_Graphics_Material_Material_reflection_h already included, missing '#pragma once' in __Source_Core_Graphics_Material_Material_reflection_h"

#endif

#define __Source_Core_Graphics_Material_Material_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__Material
#error "GENERATE_BODY_FULLNAME_dooms__graphics__Material already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__Material
#define INHERITANCE_INFORMATION_dooms__graphics__Material \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 2617217541, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__graphics__Material
#define CLONE_OBJECT_dooms__graphics__Material \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::graphics::Material>::value == true) && (std::is_base_of<dooms::DObject, dooms::graphics::Material>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::graphics::Material>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__graphics__Material
#define CURRENT_TYPE_ALIAS_dooms__graphics__Material \
public : \
typedef dooms::graphics::Material Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Material
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Material \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2617217541; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::Material"; \
inline static const char* const TYPE_SHORT_NAME = "Material"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Material
#define TYPE_CHECK_FUNCTION_Material \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__Material
#define GENERATE_BODY_FULLNAME_dooms__graphics__Material(...) \
INHERITANCE_INFORMATION_dooms__graphics__Material \
CLONE_OBJECT_dooms__graphics__Material \
CURRENT_TYPE_ALIAS_dooms__graphics__Material \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Material \
TYPE_CHECK_FUNCTION_Material \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Material(...) GENERATE_BODY_FULLNAME_dooms__graphics__Material(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__Material(__VA_ARGS__)


//-------------------------------------------


