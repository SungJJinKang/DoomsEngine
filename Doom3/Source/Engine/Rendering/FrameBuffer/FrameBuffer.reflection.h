#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Engine_Rendering_FrameBuffer_FrameBuffer_reflection_h


#ifdef __Source_Engine_Rendering_FrameBuffer_FrameBuffer_reflection_h

#error "__Source_Engine_Rendering_FrameBuffer_FrameBuffer_reflection_h already included, missing '#pragma once' in __Source_Engine_Rendering_FrameBuffer_FrameBuffer_reflection_h"

#endif

#define __Source_Engine_Rendering_FrameBuffer_FrameBuffer_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__FrameBuffer
#error "GENERATE_BODY_FULLNAME_dooms__graphics__FrameBuffer already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__FrameBuffer
#define INHERITANCE_INFORMATION_dooms__graphics__FrameBuffer \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 521766154, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__graphics__FrameBuffer
#define CLONE_OBJECT_dooms__graphics__FrameBuffer \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::graphics::FrameBuffer>::value == true) && (std::is_base_of<dooms::DObject, dooms::graphics::FrameBuffer>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::graphics::FrameBuffer>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__graphics__FrameBuffer
#define CURRENT_TYPE_ALIAS_dooms__graphics__FrameBuffer \
public : \
typedef dooms::graphics::FrameBuffer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__FrameBuffer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__FrameBuffer \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 521766154; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::FrameBuffer"; \
inline static const char* const TYPE_SHORT_NAME = "FrameBuffer"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_FrameBuffer
#define TYPE_CHECK_FUNCTION_FrameBuffer \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__FrameBuffer
#define GENERATE_BODY_FULLNAME_dooms__graphics__FrameBuffer(...) \
INHERITANCE_INFORMATION_dooms__graphics__FrameBuffer \
CLONE_OBJECT_dooms__graphics__FrameBuffer \
CURRENT_TYPE_ALIAS_dooms__graphics__FrameBuffer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__FrameBuffer \
TYPE_CHECK_FUNCTION_FrameBuffer \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_FrameBuffer(...) GENERATE_BODY_FULLNAME_dooms__graphics__FrameBuffer(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__FrameBuffer(__VA_ARGS__)


//-------------------------------------------


