#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\IO\AssetImporter\AssetImporterWorker\AssetImporterWorker_Font.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_Font_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\IO\AssetImporter\AssetImporterWorker\AssetImporterWorker_Font.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\IO\AssetImporter\AssetImporterWorker\AssetImporterWorker_Font.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_Font_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Font
#error "GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Font already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_Font
#define INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_Font \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 3547440760, 1388311841, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::assetImporter::AssetImporterWorker Base;


#undef CLONE_OBJECT_dooms__assetImporter__AssetImporterWorker_Font
#define CLONE_OBJECT_dooms__assetImporter__AssetImporterWorker_Font \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::assetImporter::AssetImporterWorker_Font>::value == true) && (std::is_base_of<dooms::DObject, dooms::assetImporter::AssetImporterWorker_Font>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::assetImporter::AssetImporterWorker_Font>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_Font
#define CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_Font \
public : \
typedef dooms::assetImporter::AssetImporterWorker_Font Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_Font
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_Font \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3547440760; \
inline static const char* const TYPE_FULL_NAME = "dooms::assetImporter::AssetImporterWorker_Font"; \
inline static const char* const TYPE_SHORT_NAME = "AssetImporterWorker_Font"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_AssetImporterWorker_Font
#define TYPE_CHECK_FUNCTION_AssetImporterWorker_Font \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Font
#define GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Font(...) \
INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_Font \
CLONE_OBJECT_dooms__assetImporter__AssetImporterWorker_Font \
CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_Font \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_Font \
TYPE_CHECK_FUNCTION_AssetImporterWorker_Font \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_AssetImporterWorker_Font(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Font(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Font(__VA_ARGS__)


//-------------------------------------------


