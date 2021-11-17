#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\PerformanceTestController.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_PerformanceTestController_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\PerformanceTestController.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\GameLogic\CustomComponent\PerformanceTestController.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_GameLogic_CustomComponent_PerformanceTestController_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__PerformanceTestController
#error "GENERATE_BODY_FULLNAME_dooms__PerformanceTestController already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__PerformanceTestController
#define INHERITANCE_INFORMATION_dooms__PerformanceTestController \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 1214867969, 3576686641, 3040581954, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 4 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::PlainComponent Base;


#undef CLONE_OBJECT_dooms__PerformanceTestController
#define CLONE_OBJECT_dooms__PerformanceTestController \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::PerformanceTestController>::value == true) && (std::is_base_of<dooms::DObject, dooms::PerformanceTestController>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::PerformanceTestController>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__PerformanceTestController
#define CURRENT_TYPE_ALIAS_dooms__PerformanceTestController \
public : \
typedef dooms::PerformanceTestController Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PerformanceTestController
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PerformanceTestController \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1214867969; \
inline static const char* const TYPE_FULL_NAME = "dooms::PerformanceTestController"; \
inline static const char* const TYPE_SHORT_NAME = "PerformanceTestController"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_PerformanceTestController
#define TYPE_CHECK_FUNCTION_PerformanceTestController \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__PerformanceTestController
#define GENERATE_BODY_FULLNAME_dooms__PerformanceTestController(...) \
INHERITANCE_INFORMATION_dooms__PerformanceTestController \
CLONE_OBJECT_dooms__PerformanceTestController \
CURRENT_TYPE_ALIAS_dooms__PerformanceTestController \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__PerformanceTestController \
TYPE_CHECK_FUNCTION_PerformanceTestController \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_PerformanceTestController(...) GENERATE_BODY_FULLNAME_dooms__PerformanceTestController(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__PerformanceTestController(__VA_ARGS__)


//-------------------------------------------


