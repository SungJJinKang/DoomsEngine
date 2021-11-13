#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Buffer\Mesh.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_Buffer_Mesh_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Buffer\Mesh.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Buffer\Mesh.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_Buffer_Mesh_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__Mesh
#error "GENERATE_BODY_FULLNAME_dooms__graphics__Mesh already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__Mesh
#define INHERITANCE_INFORMATION_dooms__graphics__Mesh \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3423928086, 2373964349, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 3 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::graphics::Buffer Base;


#undef CURRENT_TYPE_ALIAS_dooms__graphics__Mesh
#define CURRENT_TYPE_ALIAS_dooms__graphics__Mesh \
public: typedef dooms::graphics::Mesh Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Mesh
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Mesh \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3423928086; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::Mesh"; \
inline static const char* const TYPE_SHORT_NAME = "Mesh"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Mesh
#define TYPE_CHECK_FUNCTION_Mesh \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__Mesh
#define GENERATE_BODY_FULLNAME_dooms__graphics__Mesh(...) \
INHERITANCE_INFORMATION_dooms__graphics__Mesh \
CURRENT_TYPE_ALIAS_dooms__graphics__Mesh \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__Mesh \
TYPE_CHECK_FUNCTION_Mesh \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Mesh(...) GENERATE_BODY_FULLNAME_dooms__graphics__Mesh(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__Mesh(__VA_ARGS__)


//-------------------------------------------


