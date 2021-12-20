#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Asset\ThreeDModelAsset.cpp


#ifdef _Source_Core_Asset_ThreeDModelAsset_reflection_h

#error "_Source_Core_Asset_ThreeDModelAsset_reflection_h already included, missing '#pragma once' in _Source_Core_Asset_ThreeDModelAsset_reflection_h"

#endif

#define _Source_Core_Asset_ThreeDModelAsset_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__MeshData
#error "GENERATE_BODY_FULLNAME_dooms__MeshData already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__MeshData
#define INHERITANCE_INFORMATION_dooms__MeshData \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 1294305453, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__MeshData
#define CLONE_OBJECT_dooms__MeshData \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::MeshData>::value == true) && (std::is_base_of<dooms::DObject, dooms::MeshData>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::MeshData>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__MeshData
#define CURRENT_TYPE_ALIAS_dooms__MeshData \
public : \
typedef dooms::MeshData Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshData
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshData \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1294305453; \
inline static const char* const TYPE_FULL_NAME = "dooms::MeshData"; \
inline static const char* const TYPE_SHORT_NAME = "MeshData"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_MeshData
#define TYPE_CHECK_FUNCTION_MeshData \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__MeshData
#define GENERATE_BODY_FULLNAME_dooms__MeshData(...) \
INHERITANCE_INFORMATION_dooms__MeshData \
CLONE_OBJECT_dooms__MeshData \
CURRENT_TYPE_ALIAS_dooms__MeshData \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshData \
TYPE_CHECK_FUNCTION_MeshData \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_MeshData(...) GENERATE_BODY_FULLNAME_dooms__MeshData(__VA_ARGS__)


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__ThreeDModelMesh
#error "GENERATE_BODY_FULLNAME_dooms__ThreeDModelMesh already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__ThreeDModelMesh
#define INHERITANCE_INFORMATION_dooms__ThreeDModelMesh \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 3774554090, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__ThreeDModelMesh
#define CLONE_OBJECT_dooms__ThreeDModelMesh \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::ThreeDModelMesh>::value == true) && (std::is_base_of<dooms::DObject, dooms::ThreeDModelMesh>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::ThreeDModelMesh>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__ThreeDModelMesh
#define CURRENT_TYPE_ALIAS_dooms__ThreeDModelMesh \
public : \
typedef dooms::ThreeDModelMesh Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ThreeDModelMesh
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ThreeDModelMesh \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3774554090; \
inline static const char* const TYPE_FULL_NAME = "dooms::ThreeDModelMesh"; \
inline static const char* const TYPE_SHORT_NAME = "ThreeDModelMesh"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_ThreeDModelMesh
#define TYPE_CHECK_FUNCTION_ThreeDModelMesh \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__ThreeDModelMesh
#define GENERATE_BODY_FULLNAME_dooms__ThreeDModelMesh(...) \
INHERITANCE_INFORMATION_dooms__ThreeDModelMesh \
CLONE_OBJECT_dooms__ThreeDModelMesh \
CURRENT_TYPE_ALIAS_dooms__ThreeDModelMesh \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ThreeDModelMesh \
TYPE_CHECK_FUNCTION_ThreeDModelMesh \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ThreeDModelMesh(...) GENERATE_BODY_FULLNAME_dooms__ThreeDModelMesh(__VA_ARGS__)


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__ThreeDModelNode
#error "GENERATE_BODY_FULLNAME_dooms__ThreeDModelNode already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__ThreeDModelNode
#define INHERITANCE_INFORMATION_dooms__ThreeDModelNode \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 2344481318, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__ThreeDModelNode
#define CLONE_OBJECT_dooms__ThreeDModelNode \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::ThreeDModelNode>::value == true) && (std::is_base_of<dooms::DObject, dooms::ThreeDModelNode>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::ThreeDModelNode>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__ThreeDModelNode
#define CURRENT_TYPE_ALIAS_dooms__ThreeDModelNode \
public : \
typedef dooms::ThreeDModelNode Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ThreeDModelNode
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ThreeDModelNode \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2344481318; \
inline static const char* const TYPE_FULL_NAME = "dooms::ThreeDModelNode"; \
inline static const char* const TYPE_SHORT_NAME = "ThreeDModelNode"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_ThreeDModelNode
#define TYPE_CHECK_FUNCTION_ThreeDModelNode \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__ThreeDModelNode
#define GENERATE_BODY_FULLNAME_dooms__ThreeDModelNode(...) \
INHERITANCE_INFORMATION_dooms__ThreeDModelNode \
CLONE_OBJECT_dooms__ThreeDModelNode \
CURRENT_TYPE_ALIAS_dooms__ThreeDModelNode \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ThreeDModelNode \
TYPE_CHECK_FUNCTION_ThreeDModelNode \
private:


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


