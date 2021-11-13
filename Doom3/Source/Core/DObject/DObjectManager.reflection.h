#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\DObject\DObjectManager.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_DObject_DObjectManager_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\DObject\DObjectManager.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\DObject\DObjectManager.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_DObject_DObjectManager_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__DObjectManager
#error "GENERATE_BODY_FULLNAME_dooms__DObjectManager already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__DObjectManager
#define CURRENT_TYPE_ALIAS_dooms__DObjectManager \
public: typedef dooms::DObjectManager Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DObjectManager
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DObjectManager \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1071384096; \
inline static const char* const TYPE_FULL_NAME = "dooms::DObjectManager"; \
inline static const char* const TYPE_SHORT_NAME = "DObjectManager"; 


#undef TYPE_CHECK_FUNCTION_DObjectManager
#define TYPE_CHECK_FUNCTION_DObjectManager \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__DObjectManager
#define GENERATE_BODY_FULLNAME_dooms__DObjectManager(...) \
CURRENT_TYPE_ALIAS_dooms__DObjectManager \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__DObjectManager \
TYPE_CHECK_FUNCTION_DObjectManager \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DObjectManager(...) GENERATE_BODY_FULLNAME_dooms__DObjectManager(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__DObjectManager(__VA_ARGS__)


//-------------------------------------------


