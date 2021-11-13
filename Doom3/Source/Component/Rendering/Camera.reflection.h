#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Camera.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_Rendering_Camera_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Camera.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\Rendering\Camera.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_Rendering_Camera_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__Camera
#error "GENERATE_BODY_FULLNAME_dooms__Camera already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__Camera
#define INHERITANCE_INFORMATION_dooms__Camera \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 2550371324, 3576686641, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBastChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBastChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::PlainComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__Camera
#define CURRENT_TYPE_ALIAS_dooms__Camera \
public: typedef dooms::Camera Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Camera
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Camera \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2550371324; \
inline static const char* const TYPE_FULL_NAME = "dooms::Camera"; \
inline static const char* const TYPE_SHORT_NAME = "Camera"; 


#undef TYPE_CHECK_FUNCTION_Camera
#define TYPE_CHECK_FUNCTION_Camera \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__Camera
#define GENERATE_BODY_FULLNAME_dooms__Camera(...) \
INHERITANCE_INFORMATION_dooms__Camera \
CURRENT_TYPE_ALIAS_dooms__Camera \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Camera \
TYPE_CHECK_FUNCTION_Camera \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Camera(...) GENERATE_BODY_FULLNAME_dooms__Camera(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__Camera(__VA_ARGS__)


//-------------------------------------------


