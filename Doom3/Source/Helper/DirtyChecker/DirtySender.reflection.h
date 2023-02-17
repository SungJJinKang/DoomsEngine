#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : __Source_Helper_DirtyChecker_DirtySender_reflection_h


#ifdef __Source_Helper_DirtyChecker_DirtySender_reflection_h

#error "__Source_Helper_DirtyChecker_DirtySender_reflection_h already included, missing '#pragma once' in __Source_Helper_DirtyChecker_DirtySender_reflection_h"

#endif

#define __Source_Helper_DirtyChecker_DirtySender_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_DirtySender
#error "GENERATE_BODY_FULLNAME_DirtySender already included...."
#endif


#undef CURRENT_TYPE_ALIAS_DirtySender
#define CURRENT_TYPE_ALIAS_DirtySender \
public : \
typedef DirtySender Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_DirtySender
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_DirtySender \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1694308964; \
inline static const char* const TYPE_FULL_NAME = "DirtySender"; \
inline static const char* const TYPE_SHORT_NAME = "DirtySender"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_DirtySender
#define TYPE_CHECK_FUNCTION_DirtySender \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_DirtySender
#define GENERATE_BODY_FULLNAME_DirtySender(...) \
CURRENT_TYPE_ALIAS_DirtySender \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_DirtySender \
TYPE_CHECK_FUNCTION_DirtySender \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_DirtySender(...) GENERATE_BODY_FULLNAME_DirtySender(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_DirtySender(__VA_ARGS__)


//-------------------------------------------


