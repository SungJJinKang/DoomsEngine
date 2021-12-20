#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Graphics\Acceleration\CullDistance\CullDistanceRenderer.cpp


#ifdef _Source_Core_Graphics_Acceleration_CullDistance_CullDistanceRenderer_reflection_h

#error "_Source_Core_Graphics_Acceleration_CullDistance_CullDistanceRenderer_reflection_h already included, missing '#pragma once' in _Source_Core_Graphics_Acceleration_CullDistance_CullDistanceRenderer_reflection_h"

#endif

#define _Source_Core_Graphics_Acceleration_CullDistance_CullDistanceRenderer_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__graphics__CullDistanceRenderer
#error "GENERATE_BODY_FULLNAME_dooms__graphics__CullDistanceRenderer already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__graphics__CullDistanceRenderer
#define CURRENT_TYPE_ALIAS_dooms__graphics__CullDistanceRenderer \
public : \
typedef dooms::graphics::CullDistanceRenderer Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__CullDistanceRenderer
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__CullDistanceRenderer \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2080457096; \
inline static const char* const TYPE_FULL_NAME = "dooms::graphics::CullDistanceRenderer"; \
inline static const char* const TYPE_SHORT_NAME = "CullDistanceRenderer"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_CullDistanceRenderer
#define TYPE_CHECK_FUNCTION_CullDistanceRenderer \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__graphics__CullDistanceRenderer
#define GENERATE_BODY_FULLNAME_dooms__graphics__CullDistanceRenderer(...) \
CURRENT_TYPE_ALIAS_dooms__graphics__CullDistanceRenderer \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__graphics__CullDistanceRenderer \
TYPE_CHECK_FUNCTION_CullDistanceRenderer \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_CullDistanceRenderer(...) GENERATE_BODY_FULLNAME_dooms__graphics__CullDistanceRenderer(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__graphics__CullDistanceRenderer(__VA_ARGS__)


//-------------------------------------------


