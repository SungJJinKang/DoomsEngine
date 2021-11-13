#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Profiler\ProfilerUI.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Profiler_ProfilerUI_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Profiler\ProfilerUI.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Profiler\ProfilerUI.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Profiler_ProfilerUI_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__ProfilerUI
#error "GENERATE_BODY_FULLNAME_dooms__ProfilerUI already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__ProfilerUI
#define CURRENT_TYPE_ALIAS_dooms__ProfilerUI \
public: typedef dooms::ProfilerUI Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ProfilerUI
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ProfilerUI \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2337363164; \
inline static const char* const TYPE_FULL_NAME = "dooms::ProfilerUI"; \
inline static const char* const TYPE_SHORT_NAME = "ProfilerUI"; 


#undef TYPE_CHECK_FUNCTION_ProfilerUI
#define TYPE_CHECK_FUNCTION_ProfilerUI \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__ProfilerUI
#define GENERATE_BODY_FULLNAME_dooms__ProfilerUI(...) \
CURRENT_TYPE_ALIAS_dooms__ProfilerUI \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__ProfilerUI \
TYPE_CHECK_FUNCTION_ProfilerUI \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ProfilerUI(...) GENERATE_BODY_FULLNAME_dooms__ProfilerUI(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__ProfilerUI(__VA_ARGS__)


//-------------------------------------------


