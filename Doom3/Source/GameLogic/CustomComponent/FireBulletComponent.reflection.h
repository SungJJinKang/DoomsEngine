#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\FireBulletComponent.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_FireBulletComponent_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\FireBulletComponent.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\FireBulletComponent.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_FireBulletComponent_reflection_h


#include <type_traits>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__FireBulletComponent
#error "GENERATE_BODY_FULLNAME_dooms__FireBulletComponent already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__FireBulletComponent
#define INHERITANCE_INFORMATION_dooms__FireBulletComponent \
public: inline static const unsigned long int BASE_CHAIN_LIST[] { 3111448023, 3576686641, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
public: typedef dooms::PlainComponent Base;


#undef CURRENT_TYPE_ALIAS_dooms__FireBulletComponent
#define CURRENT_TYPE_ALIAS_dooms__FireBulletComponent \
public: typedef dooms::FireBulletComponent Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__FireBulletComponent
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__FireBulletComponent \
public: \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 3111448023; \
inline static const char* const TYPE_FULL_NAME = "dooms::FireBulletComponent"; \
inline static const char* const TYPE_SHORT_NAME = "FireBulletComponent"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_FireBulletComponent
#define TYPE_CHECK_FUNCTION_FireBulletComponent \
private: \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::decay<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__FireBulletComponent
#define GENERATE_BODY_FULLNAME_dooms__FireBulletComponent(...) \
INHERITANCE_INFORMATION_dooms__FireBulletComponent \
CURRENT_TYPE_ALIAS_dooms__FireBulletComponent \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__FireBulletComponent \
TYPE_CHECK_FUNCTION_FireBulletComponent \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_FireBulletComponent(...) GENERATE_BODY_FULLNAME_dooms__FireBulletComponent(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__FireBulletComponent(__VA_ARGS__)


//-------------------------------------------


