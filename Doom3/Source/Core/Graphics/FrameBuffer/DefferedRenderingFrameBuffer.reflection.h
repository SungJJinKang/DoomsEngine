#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\FrameBuffer\DefferedRenderingFrameBuffer.cpp


#ifdef _Source_Core_Graphics_FrameBuffer_DefferedRenderingFrameBuffer_reflection_h

#error "_Source_Core_Graphics_FrameBuffer_DefferedRenderingFrameBuffer_reflection_h already included, missing '#pragma once' in _Source_Core_Graphics_FrameBuffer_DefferedRenderingFrameBuffer_reflection_h"

#endif

#define _Source_Core_Graphics_FrameBuffer_DefferedRenderingFrameBuffer_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__DefferedRenderingFrameBuffer
#error "GENERATE_BODY_FULLNAME_dooms__graphics__DefferedRenderingFrameBuffer already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__DefferedRenderingFrameBuffer
#define INHERITANCE_INFORMATION_dooms__graphics__DefferedRenderingFrameBuffer \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 1132735981, 521766154, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::graphics::FrameBuffer Base;


#undef CLONE_OBJECT_dooms__graphics__DefferedRenderingFrameBuffer
#define CLONE_OBJECT_dooms__graphics__DefferedRenderingFrameBuffer \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::graphics::DefferedRenderingFrameBuffer>::value == true) && (std::is_base_of<dooms::DObject, dooms::graphics::DefferedRenderingFrameBuffer>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::graphics::DefferedRenderingFrameBuffer>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__graphics__DefferedRenderingFrameBuffer
#define CURRENT_TYPE_ALIAS_dooms__graphics__DefferedRenderingFrameBuffer \
public : \
typedef dooms::graphics::DefferedRenderingFrameBuffer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__DefferedRenderingFrameBuffer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__DefferedRenderingFrameBuffer \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1132735981; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::DefferedRenderingFrameBuffer"; \
inline static const char* const TYPE_SHORT_NAME = "DefferedRenderingFrameBuffer"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_DefferedRenderingFrameBuffer
#define TYPE_CHECK_FUNCTION_DefferedRenderingFrameBuffer \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__DefferedRenderingFrameBuffer
#define GENERATE_BODY_FULLNAME_dooms__graphics__DefferedRenderingFrameBuffer(...) \
INHERITANCE_INFORMATION_dooms__graphics__DefferedRenderingFrameBuffer \
CLONE_OBJECT_dooms__graphics__DefferedRenderingFrameBuffer \
CURRENT_TYPE_ALIAS_dooms__graphics__DefferedRenderingFrameBuffer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__DefferedRenderingFrameBuffer \
TYPE_CHECK_FUNCTION_DefferedRenderingFrameBuffer \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DefferedRenderingFrameBuffer(...) GENERATE_BODY_FULLNAME_dooms__graphics__DefferedRenderingFrameBuffer(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__DefferedRenderingFrameBuffer(__VA_ARGS__)


//-------------------------------------------


