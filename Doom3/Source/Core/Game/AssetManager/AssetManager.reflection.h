#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Game\AssetManager\AssetManager.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Game_AssetManager_AssetManager_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Game\AssetManager\AssetManager.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Game\AssetManager\AssetManager.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Game_AssetManager_AssetManager_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetManager
#error "GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetManager already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__assetImporter__AssetManager
#define INHERITANCE_INFORMATION_dooms__assetImporter__AssetManager \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 2475534706, 3668408939, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::IGameFlow Base;


#undef CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetManager
#define CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetManager \
public: typedef dooms::assetImporter::AssetManager Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetManager
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetManager \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2475534706; \
inline static const char* const TYPE_FULL_NAME = "dooms::assetImporter::AssetManager"; \
inline static const char* const TYPE_SHORT_NAME = "AssetManager"; 


#undef TYPE_CHECK_FUNCTION_AssetManager
#define TYPE_CHECK_FUNCTION_AssetManager \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetManager
#define GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetManager(...) \
INHERITANCE_INFORMATION_dooms__assetImporter__AssetManager \
CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetManager \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetManager \
TYPE_CHECK_FUNCTION_AssetManager \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_AssetManager(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetManager(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetManager(__VA_ARGS__)


//-------------------------------------------


