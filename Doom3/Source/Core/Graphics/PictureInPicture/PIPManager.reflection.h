#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\PictureInPicture\PIPManager.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_PictureInPicture_PIPManager_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\PictureInPicture\PIPManager.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\PictureInPicture\PIPManager.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_PictureInPicture_PIPManager_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__PIPManager
#error "GENERATE_BODY_FULLNAME_dooms__graphics__PIPManager already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__PIPManager
#define INHERITANCE_INFORMATION_dooms__graphics__PIPManager \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3614957572, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::DObject Base;


#undef CURRENT_TYPE_ALIAS_dooms__graphics__PIPManager
#define CURRENT_TYPE_ALIAS_dooms__graphics__PIPManager \
public: typedef dooms::graphics::PIPManager Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__PIPManager
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__PIPManager \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3614957572; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::PIPManager"; \
inline static const char* const TYPE_SHORT_NAME = "PIPManager"; 


#undef TYPE_CHECK_FUNCTION_PIPManager
#define TYPE_CHECK_FUNCTION_PIPManager \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__PIPManager
#define GENERATE_BODY_FULLNAME_dooms__graphics__PIPManager(...) \
INHERITANCE_INFORMATION_dooms__graphics__PIPManager \
CURRENT_TYPE_ALIAS_dooms__graphics__PIPManager \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__PIPManager \
TYPE_CHECK_FUNCTION_PIPManager \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_PIPManager(...) GENERATE_BODY_FULLNAME_dooms__graphics__PIPManager(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__PIPManager(__VA_ARGS__)


//-------------------------------------------


