#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Animation\Animation.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_Rendering_Animation_Animation_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Animation\Animation.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Animation\Animation.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_Rendering_Animation_Animation_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__Animation
#error "GENERATE_BODY_FULLNAME_dooms__Animation already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__Animation
#define INHERITANCE_INFORMATION_dooms__Animation \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 781093150, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::Component Base;


#undef CLONE_OBJECT_dooms__Animation
#define CLONE_OBJECT_dooms__Animation \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::Animation>::value == true) && (std::is_base_of<dooms::DObject, dooms::Animation>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::Animation>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__Animation
#define CURRENT_TYPE_ALIAS_dooms__Animation \
public : \
typedef dooms::Animation Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Animation
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Animation \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 781093150; \
inline static const char* const TYPE_FULL_NAME = "dooms::Animation"; \
inline static const char* const TYPE_SHORT_NAME = "Animation"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Animation
#define TYPE_CHECK_FUNCTION_Animation \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__Animation
#define GENERATE_BODY_FULLNAME_dooms__Animation(...) \
INHERITANCE_INFORMATION_dooms__Animation \
CLONE_OBJECT_dooms__Animation \
CURRENT_TYPE_ALIAS_dooms__Animation \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Animation \
TYPE_CHECK_FUNCTION_Animation \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Animation(...) GENERATE_BODY_FULLNAME_dooms__Animation(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__Animation(__VA_ARGS__)


//-------------------------------------------


