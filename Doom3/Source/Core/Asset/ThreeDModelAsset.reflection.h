#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Asset\ThreeDModelAsset.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Asset_ThreeDModelAsset_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Asset\ThreeDModelAsset.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Asset\ThreeDModelAsset.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Asset_ThreeDModelAsset_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__MeshVertexData
#error "GENERATE_BODY_FULLNAME_dooms__MeshVertexData already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__MeshVertexData
#define CURRENT_TYPE_ALIAS_dooms__MeshVertexData \
typedef dooms::MeshVertexData Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshVertexData
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshVertexData \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1497951543; \
inline static const char* const TYPE_FULL_NAME = "dooms::MeshVertexData"; \
inline static const char* const TYPE_SHORT_NAME = "MeshVertexData"; \


#undef TYPE_CHECK_FUNCTION_MeshVertexData
#define TYPE_CHECK_FUNCTION_MeshVertexData \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__MeshVertexData
#define GENERATE_BODY_FULLNAME_dooms__MeshVertexData(...) \
CURRENT_TYPE_ALIAS_dooms__MeshVertexData \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshVertexData \
TYPE_CHECK_FUNCTION_MeshVertexData \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_MeshVertexData(...) GENERATE_BODY_FULLNAME_dooms__MeshVertexData(__VA_ARGS__)


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__ThreeDModelMesh
#error "GENERATE_BODY_FULLNAME_dooms__ThreeDModelMesh already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__ThreeDModelMesh
#define CURRENT_TYPE_ALIAS_dooms__ThreeDModelMesh \
typedef dooms::ThreeDModelMesh Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ThreeDModelMesh
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ThreeDModelMesh \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3774554090; \
inline static const char* const TYPE_FULL_NAME = "dooms::ThreeDModelMesh"; \
inline static const char* const TYPE_SHORT_NAME = "ThreeDModelMesh"; \


#undef TYPE_CHECK_FUNCTION_ThreeDModelMesh
#define TYPE_CHECK_FUNCTION_ThreeDModelMesh \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__ThreeDModelMesh
#define GENERATE_BODY_FULLNAME_dooms__ThreeDModelMesh(...) \
CURRENT_TYPE_ALIAS_dooms__ThreeDModelMesh \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ThreeDModelMesh \
TYPE_CHECK_FUNCTION_ThreeDModelMesh \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ThreeDModelMesh(...) GENERATE_BODY_FULLNAME_dooms__ThreeDModelMesh(__VA_ARGS__)


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__ThreeDModelNode
#error "GENERATE_BODY_FULLNAME_dooms__ThreeDModelNode already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__ThreeDModelNode
#define CURRENT_TYPE_ALIAS_dooms__ThreeDModelNode \
typedef dooms::ThreeDModelNode Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ThreeDModelNode
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ThreeDModelNode \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2344481318; \
inline static const char* const TYPE_FULL_NAME = "dooms::ThreeDModelNode"; \
inline static const char* const TYPE_SHORT_NAME = "ThreeDModelNode"; \


#undef TYPE_CHECK_FUNCTION_ThreeDModelNode
#define TYPE_CHECK_FUNCTION_ThreeDModelNode \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__ThreeDModelNode
#define GENERATE_BODY_FULLNAME_dooms__ThreeDModelNode(...) \
CURRENT_TYPE_ALIAS_dooms__ThreeDModelNode \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ThreeDModelNode \
TYPE_CHECK_FUNCTION_ThreeDModelNode \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ThreeDModelNode(...) GENERATE_BODY_FULLNAME_dooms__ThreeDModelNode(__VA_ARGS__)


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__asset__ThreeDModelAsset
#error "GENERATE_BODY_FULLNAME_dooms__asset__ThreeDModelAsset already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__asset__ThreeDModelAsset
#define INHERITANCE_INFORMATION_dooms__asset__ThreeDModelAsset \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 4198124059, 2982024308, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::asset::Asset Base;


#undef CLONE_OBJECT_dooms__asset__ThreeDModelAsset
#define CLONE_OBJECT_dooms__asset__ThreeDModelAsset \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::asset::ThreeDModelAsset>::value == true) && (std::is_base_of<dooms::DObject, dooms::asset::ThreeDModelAsset>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::asset::ThreeDModelAsset>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__asset__ThreeDModelAsset
#define CURRENT_TYPE_ALIAS_dooms__asset__ThreeDModelAsset \
public : \
typedef dooms::asset::ThreeDModelAsset Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ThreeDModelAsset
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ThreeDModelAsset \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 4198124059; \
inline static const char* const TYPE_FULL_NAME = "dooms::asset::ThreeDModelAsset"; \
inline static const char* const TYPE_SHORT_NAME = "ThreeDModelAsset"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_ThreeDModelAsset
#define TYPE_CHECK_FUNCTION_ThreeDModelAsset \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__asset__ThreeDModelAsset
#define GENERATE_BODY_FULLNAME_dooms__asset__ThreeDModelAsset(...) \
INHERITANCE_INFORMATION_dooms__asset__ThreeDModelAsset \
CLONE_OBJECT_dooms__asset__ThreeDModelAsset \
CURRENT_TYPE_ALIAS_dooms__asset__ThreeDModelAsset \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__asset__ThreeDModelAsset \
TYPE_CHECK_FUNCTION_ThreeDModelAsset \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ThreeDModelAsset(...) GENERATE_BODY_FULLNAME_dooms__asset__ThreeDModelAsset(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__asset__ThreeDModelAsset(__VA_ARGS__)


//-------------------------------------------


