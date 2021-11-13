#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Random.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Random_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Random.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Random.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Random_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__random__Random
#error "GENERATE_BODY_FULLNAME_dooms__random__Random already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__random__Random
#define CURRENT_TYPE_ALIAS_dooms__random__Random \
public: typedef dooms::random::Random Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__random__Random
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__random__Random \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 379285917; \
inline static const char* const TYPE_FULL_NAME = "dooms::random::Random"; \
inline static const char* const TYPE_SHORT_NAME = "Random"; 


#undef TYPE_CHECK_FUNCTION_Random
#define TYPE_CHECK_FUNCTION_Random \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__random__Random
#define GENERATE_BODY_FULLNAME_dooms__random__Random(...) \
CURRENT_TYPE_ALIAS_dooms__random__Random \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__random__Random \
TYPE_CHECK_FUNCTION_Random \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Random(...) GENERATE_BODY_FULLNAME_dooms__random__Random(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__random__Random(__VA_ARGS__)


//-------------------------------------------


