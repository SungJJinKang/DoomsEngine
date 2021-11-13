#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\IO\AssetImporter\AssetImporterWorker\AssetImporterWorker_Audio.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_Audio_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\IO\AssetImporter\AssetImporterWorker\AssetImporterWorker_Audio.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\IO\AssetImporter\AssetImporterWorker\AssetImporterWorker_Audio.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_IO_AssetImporter_AssetImporterWorker_AssetImporterWorker_Audio_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Audio
#error "GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Audio already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_Audio
#define INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_Audio \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 2429147574, 1388311841, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::assetImporter::AssetImporterWorker Base;


#undef CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_Audio
#define CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_Audio \
public: typedef dooms::assetImporter::AssetImporterWorker_Audio Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_Audio
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_Audio \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2429147574; \
inline static const char* const TYPE_FULL_NAME = "dooms::assetImporter::AssetImporterWorker_Audio"; \
inline static const char* const TYPE_SHORT_NAME = "AssetImporterWorker_Audio"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_AssetImporterWorker_Audio
#define TYPE_CHECK_FUNCTION_AssetImporterWorker_Audio \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Audio
#define GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Audio(...) \
INHERITANCE_INFORMATION_dooms__assetImporter__AssetImporterWorker_Audio \
CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetImporterWorker_Audio \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetImporterWorker_Audio \
TYPE_CHECK_FUNCTION_AssetImporterWorker_Audio \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_AssetImporterWorker_Audio(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Audio(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetImporterWorker_Audio(__VA_ARGS__)


//-------------------------------------------


