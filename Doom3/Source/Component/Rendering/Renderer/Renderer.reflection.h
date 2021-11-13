#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Renderer\Renderer.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_Rendering_Renderer_Renderer_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Renderer\Renderer.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Renderer\Renderer.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_Rendering_Renderer_Renderer_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__Renderer
#error "GENERATE_BODY_FULLNAME_dooms__Renderer already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__Renderer
#define INHERITANCE_INFORMATION_dooms__Renderer \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3346461073, 1503232071, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::ServerComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__Renderer
#define CURRENT_TYPE_ALIAS_dooms__Renderer \
public: typedef dooms::Renderer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Renderer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Renderer \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3346461073; \
inline static const char* const TYPE_FULL_NAME = "dooms::Renderer"; \
inline static const char* const TYPE_SHORT_NAME = "Renderer"; 


#undef TYPE_CHECK_FUNCTION_Renderer
#define TYPE_CHECK_FUNCTION_Renderer \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__Renderer
#define GENERATE_BODY_FULLNAME_dooms__Renderer(...) \
INHERITANCE_INFORMATION_dooms__Renderer \
CURRENT_TYPE_ALIAS_dooms__Renderer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Renderer \
TYPE_CHECK_FUNCTION_Renderer \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Renderer(...) GENERATE_BODY_FULLNAME_dooms__Renderer(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__Renderer(__VA_ARGS__)


//-------------------------------------------


