#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_Asset_AssetImportExporter_AssetImporter_AssetImporterWorker_AssetImporterWorker_Shader_reflection_h


#ifdef __Source_Core_Asset_AssetImportExporter_AssetImporter_AssetImporterWorker_AssetImporterWorker_Shader_reflection_h

#error "__Source_Core_Asset_AssetImportExporter_AssetImporter_AssetImporterWorker_AssetImporterWorker_Shader_reflection_h already included, missing '#pragma once' in __Source_Core_Asset_AssetImportExporter_AssetImporter_AssetImporterWorker_AssetImporterWorker_Shader_reflection_h"

#endif

#define __Source_Core_Asset_AssetImportExporter_AssetImporter_AssetImporterWorker_AssetImporterWorker_Shader_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Shader
#error "GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Shader already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_Shader
#define INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_Shader \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 3387746671, 1388311841, 3251103914, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::assetImporter::AssetImporterWorker Base;


#undef CLONE_OBJECT_dooms__assetImporter__AssetImporterWorker_Shader
#define CLONE_OBJECT_dooms__assetImporter__AssetImporterWorker_Shader \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::assetImporter::AssetImporterWorker_Shader>::value == true) && (std::is_base_of<dooms::DObject, dooms::assetImporter::AssetImporterWorker_Shader>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::assetImporter::AssetImporterWorker_Shader>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_Shader
#define CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_Shader \
public : \
typedef dooms::assetImporter::AssetImporterWorker_Shader Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_Shader
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_Shader \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3387746671; \
inline static const char* const TYPE_FULL_NAME = "dooms::assetImporter::AssetImporterWorker_Shader"; \
inline static const char* const TYPE_SHORT_NAME = "AssetImporterWorker_Shader"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_AssetImporterWorker_Shader
#define TYPE_CHECK_FUNCTION_AssetImporterWorker_Shader \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Shader
#define GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Shader(...) \
INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_Shader \
CLONE_OBJECT_dooms__assetImporter__AssetImporterWorker_Shader \
CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_Shader \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_Shader \
TYPE_CHECK_FUNCTION_AssetImporterWorker_Shader \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_AssetImporterWorker_Shader(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Shader(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Shader(__VA_ARGS__)


//-------------------------------------------

