#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\Rigidbody\Rigidbody.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Component_PhysicsComponent_Rigidbody_Rigidbody_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\Rigidbody\Rigidbody.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Component\PhysicsComponent\Rigidbody\Rigidbody.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Component_PhysicsComponent_Rigidbody_Rigidbody_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__Rigidbody
#error "GENERATE_BODY_FULLNAME_dooms__Rigidbody already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__Rigidbody
#define INHERITANCE_INFORMATION_dooms__Rigidbody \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 2189472633, 1503232071, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::ServerComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__Rigidbody
#define CURRENT_TYPE_ALIAS_dooms__Rigidbody \
public: typedef dooms::Rigidbody Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Rigidbody
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Rigidbody \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 2189472633; \
inline static const char* const TYPE_FULL_NAME = "dooms::Rigidbody"; \
inline static const char* const TYPE_SHORT_NAME = "Rigidbody"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Rigidbody
#define TYPE_CHECK_FUNCTION_Rigidbody \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__Rigidbody
#define GENERATE_BODY_FULLNAME_dooms__Rigidbody(...) \
INHERITANCE_INFORMATION_dooms__Rigidbody \
CURRENT_TYPE_ALIAS_dooms__Rigidbody \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Rigidbody \
TYPE_CHECK_FUNCTION_Rigidbody \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Rigidbody(...) GENERATE_BODY_FULLNAME_dooms__Rigidbody(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__Rigidbody(__VA_ARGS__)


//-------------------------------------------


