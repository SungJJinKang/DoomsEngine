#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\IO\AssetImporter\AssetImporterWorker\AssetImporterWorker.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\IO\AssetImporter\AssetImporterWorker\AssetImporterWorker.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\IO\AssetImporter\AssetImporterWorker\AssetImporterWorker.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker
#error "GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker
#define INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 1388311841, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::DObject Base;


#undef CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker
#define CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker \
public: typedef dooms::assetImporter::AssetImporterWorker Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1388311841; \
inline static const char* const TYPE_FULL_NAME = "dooms::assetImporter::AssetImporterWorker"; \
inline static const char* const TYPE_SHORT_NAME = "AssetImporterWorker"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_AssetImporterWorker
#define TYPE_CHECK_FUNCTION_AssetImporterWorker \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker
#define GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker(...) \
INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker \
CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker \
TYPE_CHECK_FUNCTION_AssetImporterWorker \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_AssetImporterWorker(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker(__VA_ARGS__)


//-------------------------------------------


