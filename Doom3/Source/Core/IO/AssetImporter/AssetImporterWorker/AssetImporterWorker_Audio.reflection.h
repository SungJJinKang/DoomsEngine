#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_Audio_reflection_h


#ifdef __Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_Audio_reflection_h

#error "__Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_Audio_reflection_h already included, missing '#pragma once' in __Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_Audio_reflection_h"

#endif

#define __Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_Audio_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Audio
#error "GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Audio already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_Audio
#define INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_Audio \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 2429147574, 1388311841, 3251103914, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::assetImporter::AssetImporterWorker Base;


#undef CLONE_OBJECT_dooms__assetImporter__AssetImporterWorker_Audio
#define CLONE_OBJECT_dooms__assetImporter__AssetImporterWorker_Audio \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::assetImporter::AssetImporterWorker_Audio>::value == true) && (std::is_base_of<dooms::DObject, dooms::assetImporter::AssetImporterWorker_Audio>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::assetImporter::AssetImporterWorker_Audio>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_Audio
#define CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_Audio \
public : \
typedef dooms::assetImporter::AssetImporterWorker_Audio Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_Audio
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_Audio \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2429147574; \
inline static const char* const TYPE_FULL_NAME = "dooms::assetImporter::AssetImporterWorker_Audio"; \
inline static const char* const TYPE_SHORT_NAME = "AssetImporterWorker_Audio"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_AssetImporterWorker_Audio
#define TYPE_CHECK_FUNCTION_AssetImporterWorker_Audio \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Audio
#define GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Audio(...) \
INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_Audio \
CLONE_OBJECT_dooms__assetImporter__AssetImporterWorker_Audio \
CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_Audio \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_Audio \
TYPE_CHECK_FUNCTION_AssetImporterWorker_Audio \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_AssetImporterWorker_Audio(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Audio(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Audio(__VA_ARGS__)


//-------------------------------------------


