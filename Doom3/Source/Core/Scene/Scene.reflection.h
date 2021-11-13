#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Scene\Scene.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Scene_Scene_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Scene\Scene.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Scene\Scene.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Scene_Scene_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__Scene
#error "GENERATE_BODY_FULLNAME_dooms__Scene already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__Scene
#define INHERITANCE_INFORMATION_dooms__Scene \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 2506784763, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::DObject Base;


#undef CURRENT_TYPE_ALIAS_dooms__Scene
#define CURRENT_TYPE_ALIAS_dooms__Scene \
public: typedef dooms::Scene Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Scene
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Scene \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2506784763; \
inline static const char* const TYPE_FULL_NAME = "dooms::Scene"; \
inline static const char* const TYPE_SHORT_NAME = "Scene"; 


#undef TYPE_CHECK_FUNCTION_Scene
#define TYPE_CHECK_FUNCTION_Scene \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__Scene
#define GENERATE_BODY_FULLNAME_dooms__Scene(...) \
INHERITANCE_INFORMATION_dooms__Scene \
CURRENT_TYPE_ALIAS_dooms__Scene \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Scene \
TYPE_CHECK_FUNCTION_Scene \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Scene(...) GENERATE_BODY_FULLNAME_dooms__Scene(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__Scene(__VA_ARGS__)


//-------------------------------------------


