#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\DeferredRenderingDrawer.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Graphics_DeferredRenderingDrawer_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Graphics\DeferredRenderingDrawer.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Graphics\DeferredRenderingDrawer.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Graphics_DeferredRenderingDrawer_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__DeferredRenderingDrawer
#error "GENERATE_BODY_FULLNAME_dooms__graphics__DeferredRenderingDrawer already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__graphics__DeferredRenderingDrawer
#define INHERITANCE_INFORMATION_dooms__graphics__DeferredRenderingDrawer \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3774730794, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::DObject Base;


#undef CURRENT_TYPE_ALIAS_dooms__graphics__DeferredRenderingDrawer
#define CURRENT_TYPE_ALIAS_dooms__graphics__DeferredRenderingDrawer \
public: typedef dooms::graphics::DeferredRenderingDrawer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__DeferredRenderingDrawer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__DeferredRenderingDrawer \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3774730794; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::DeferredRenderingDrawer"; \
inline static const char* const TYPE_SHORT_NAME = "DeferredRenderingDrawer"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_DeferredRenderingDrawer
#define TYPE_CHECK_FUNCTION_DeferredRenderingDrawer \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__DeferredRenderingDrawer
#define GENERATE_BODY_FULLNAME_dooms__graphics__DeferredRenderingDrawer(...) \
INHERITANCE_INFORMATION_dooms__graphics__DeferredRenderingDrawer \
CURRENT_TYPE_ALIAS_dooms__graphics__DeferredRenderingDrawer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__DeferredRenderingDrawer \
TYPE_CHECK_FUNCTION_DeferredRenderingDrawer \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DeferredRenderingDrawer(...) GENERATE_BODY_FULLNAME_dooms__graphics__DeferredRenderingDrawer(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__DeferredRenderingDrawer(__VA_ARGS__)


//-------------------------------------------


