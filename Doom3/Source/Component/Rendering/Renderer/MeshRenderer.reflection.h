#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Renderer\MeshRenderer.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_Rendering_Renderer_MeshRenderer_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Renderer\MeshRenderer.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Renderer\MeshRenderer.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_Rendering_Renderer_MeshRenderer_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__MeshRenderer
#error "GENERATE_BODY_FULLNAME_dooms__MeshRenderer already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__MeshRenderer
#define INHERITANCE_INFORMATION_dooms__MeshRenderer \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3778871520, 3346461073, 1503232071, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 5 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::Renderer Base;


#undef CURRENT_TYPE_ALIAS_dooms__MeshRenderer
#define CURRENT_TYPE_ALIAS_dooms__MeshRenderer \
public: typedef dooms::MeshRenderer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshRenderer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshRenderer \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3778871520; \
inline static const char* const TYPE_FULL_NAME = "dooms::MeshRenderer"; \
inline static const char* const TYPE_SHORT_NAME = "MeshRenderer"; 


#undef TYPE_CHECK_FUNCTION_MeshRenderer
#define TYPE_CHECK_FUNCTION_MeshRenderer \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__MeshRenderer
#define GENERATE_BODY_FULLNAME_dooms__MeshRenderer(...) \
INHERITANCE_INFORMATION_dooms__MeshRenderer \
CURRENT_TYPE_ALIAS_dooms__MeshRenderer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__MeshRenderer \
TYPE_CHECK_FUNCTION_MeshRenderer \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_MeshRenderer(...) GENERATE_BODY_FULLNAME_dooms__MeshRenderer(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__MeshRenderer(__VA_ARGS__)


//-------------------------------------------


