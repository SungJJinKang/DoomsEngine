#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\IO\AssetImporter\AssetImporterWorker\AssetImporterWorker_Three_D_Model.cpp


#ifdef _Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_Three_D_Model_reflection_h

#error "_Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_Three_D_Model_reflection_h already included, missing '#pragma once' in _Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_Three_D_Model_reflection_h"

#endif

#define _Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_Three_D_Model_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL
#error "GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL
#define INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 2404261598, 1388311841, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::assetImporter::AssetImporterWorker Base;


#undef CLONE_OBJECT_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL
#define CLONE_OBJECT_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL>::value == true) && (std::is_base_of<dooms::DObject, dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL
#define CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL \
public : \
typedef dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2404261598; \
inline static const char* const TYPE_FULL_NAME = "dooms::assetImporter::AssetImporterWorker_THREE_D_MODEL"; \
inline static const char* const TYPE_SHORT_NAME = "AssetImporterWorker_THREE_D_MODEL"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_AssetImporterWorker_THREE_D_MODEL
#define TYPE_CHECK_FUNCTION_AssetImporterWorker_THREE_D_MODEL \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL
#define GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL(...) \
INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL \
CLONE_OBJECT_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL \
CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL \
TYPE_CHECK_FUNCTION_AssetImporterWorker_THREE_D_MODEL \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_AssetImporterWorker_THREE_D_MODEL(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_THREE_D_MODEL(__VA_ARGS__)


//-------------------------------------------


