#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Engine_Rendering_Pipeline_PipeLines_PBR_ForwardPhysicsBasedRenderingPipeLine_reflection_h


#ifdef __Source_Engine_Rendering_Pipeline_PipeLines_PBR_ForwardPhysicsBasedRenderingPipeLine_reflection_h

#error "__Source_Engine_Rendering_Pipeline_PipeLines_PBR_ForwardPhysicsBasedRenderingPipeLine_reflection_h already included, missing '#pragma once' in __Source_Engine_Rendering_Pipeline_PipeLines_PBR_ForwardPhysicsBasedRenderingPipeLine_reflection_h"

#endif

#define __Source_Engine_Rendering_Pipeline_PipeLines_PBR_ForwardPhysicsBasedRenderingPipeLine_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine
#error "GENERATE_BODY_FULLNAME_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine
#define INHERITANCE_INFORMATION_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 3593307682, 1760253633, 693533215, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::graphics::DefaultGraphcisPipeLine Base;


#undef CLONE_OBJECT_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine
#define CLONE_OBJECT_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::graphics::ForwardPhysicsBasedRenderingPipeLine>::value == true) && (std::is_base_of<dooms::DObject, dooms::graphics::ForwardPhysicsBasedRenderingPipeLine>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::graphics::ForwardPhysicsBasedRenderingPipeLine>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine
#define CURRENT_TYPE_ALIAS_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine \
public : \
typedef dooms::graphics::ForwardPhysicsBasedRenderingPipeLine Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3593307682; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::ForwardPhysicsBasedRenderingPipeLine"; \
inline static const char* const TYPE_SHORT_NAME = "ForwardPhysicsBasedRenderingPipeLine"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_ForwardPhysicsBasedRenderingPipeLine
#define TYPE_CHECK_FUNCTION_ForwardPhysicsBasedRenderingPipeLine \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine
#define GENERATE_BODY_FULLNAME_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine(...) \
INHERITANCE_INFORMATION_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine \
CLONE_OBJECT_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine \
CURRENT_TYPE_ALIAS_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine \
TYPE_CHECK_FUNCTION_ForwardPhysicsBasedRenderingPipeLine \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ForwardPhysicsBasedRenderingPipeLine(...) GENERATE_BODY_FULLNAME_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__ForwardPhysicsBasedRenderingPipeLine(__VA_ARGS__)


//-------------------------------------------


