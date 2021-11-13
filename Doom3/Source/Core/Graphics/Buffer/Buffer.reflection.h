#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Buffer\Buffer.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_Buffer_Buffer_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Buffer\Buffer.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Buffer\Buffer.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_Buffer_Buffer_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__Buffer
#error "GENERATE_BODY_FULLNAME_dooms__graphics__Buffer already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__Buffer
#define INHERITANCE_INFORMATION_dooms__graphics__Buffer \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 2373964349, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::DObject Base;


#undef CURRENT_TYPE_ALIAS_dooms__graphics__Buffer
#define CURRENT_TYPE_ALIAS_dooms__graphics__Buffer \
public: typedef dooms::graphics::Buffer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Buffer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Buffer \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2373964349; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::Buffer"; \
inline static const char* const TYPE_SHORT_NAME = "Buffer"; 


#undef TYPE_CHECK_FUNCTION_Buffer
#define TYPE_CHECK_FUNCTION_Buffer \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__Buffer
#define GENERATE_BODY_FULLNAME_dooms__graphics__Buffer(...) \
INHERITANCE_INFORMATION_dooms__graphics__Buffer \
CURRENT_TYPE_ALIAS_dooms__graphics__Buffer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Buffer \
TYPE_CHECK_FUNCTION_Buffer \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Buffer(...) GENERATE_BODY_FULLNAME_dooms__graphics__Buffer(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__Buffer(__VA_ARGS__)


//-------------------------------------------


