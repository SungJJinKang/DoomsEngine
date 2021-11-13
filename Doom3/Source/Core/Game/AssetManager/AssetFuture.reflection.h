#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Game\AssetManager\AssetFuture.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Game_AssetManager_AssetFuture_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Game\AssetManager\AssetFuture.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Game\AssetManager\AssetFuture.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Game_AssetManager_AssetFuture_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetFuture
#error "GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetFuture already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetFuture
#define CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetFuture \
public: typedef dooms::assetImporter::AssetFuture Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetFuture
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetFuture \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 207266924; \
inline static const char* const TYPE_FULL_NAME = "dooms::assetImporter::AssetFuture"; \
inline static const char* const TYPE_SHORT_NAME = "AssetFuture"; 


#undef TYPE_CHECK_FUNCTION_AssetFuture
#define TYPE_CHECK_FUNCTION_AssetFuture \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetFuture
#define GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetFuture(...) \
CURRENT_TYPE_ALIAS_dooms__assetImporter__AssetFuture \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__assetImporter__AssetFuture \
TYPE_CHECK_FUNCTION_AssetFuture \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_AssetFuture(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetFuture(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__assetImporter__AssetFuture(__VA_ARGS__)


//-------------------------------------------


