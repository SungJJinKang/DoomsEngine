#pragma once

// Utility Header File ( Don't Edit this )
// SourceFilePath : C:\Doom3FromScratch\Doom3\Source\Core\Scene\Entity.cpp


#ifdef C__Doom3FromScratch_Doom3_Source_Core_Scene_Entity_reflection_h

#error "C:\Doom3FromScratch\Doom3\Source\Core\Scene\Entity.reflection.h already included, missing '#pragma once' in C:\Doom3FromScratch\Doom3\Source\Core\Scene\Entity.reflection.h"

#endif

#define C__Doom3FromScratch_Doom3_Source_Core_Scene_Entity_reflection_h


#include <type_traits>
#include <cassert>


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__resource__ObjectPool
#error "GENERATE_BODY_FULLNAME_dooms__resource__ObjectPool already included...."
#endif


#undef CURRENT_TYPE_ALIAS_dooms__resource__ObjectPool
#define CURRENT_TYPE_ALIAS_dooms__resource__ObjectPool \
typedef dooms::resource::ObjectPool Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__resource__ObjectPool
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__resource__ObjectPool \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 235128460; \
inline static const char* const TYPE_FULL_NAME = "dooms::resource::ObjectPool"; \
inline static const char* const TYPE_SHORT_NAME = "ObjectPool"; \


#undef TYPE_CHECK_FUNCTION_ObjectPool
#define TYPE_CHECK_FUNCTION_ObjectPool \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__resource__ObjectPool
#define GENERATE_BODY_FULLNAME_dooms__resource__ObjectPool(...) \
CURRENT_TYPE_ALIAS_dooms__resource__ObjectPool \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__resource__ObjectPool \
TYPE_CHECK_FUNCTION_ObjectPool \


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_ObjectPool(...) GENERATE_BODY_FULLNAME_dooms__resource__ObjectPool(__VA_ARGS__)


//-------------------------------------------


#ifdef GENERATE_BODY_FULLNAME_dooms__Entity
#error "GENERATE_BODY_FULLNAME_dooms__Entity already included...."
#endif

#undef INHERITANCE_INFORMATION_dooms__Entity
#define INHERITANCE_INFORMATION_dooms__Entity \
public : \
inline static const unsigned long int BASE_CHAIN_LIST[] { 1983755528, 3969188510 }; \
inline static const unsigned long int BASE_CHAIN_LIST_LENGTH { 2 }; \
virtual const unsigned long int* GetBaseChainList() const { return BASE_CHAIN_LIST; } \
virtual unsigned long int GetBaseChainListLength() const { return BASE_CHAIN_LIST_LENGTH; } \
typedef dooms::DObject Base;


#undef CLONE_OBJECT_dooms__Entity
#define CLONE_OBJECT_dooms__Entity \
public : \
virtual dooms::DObject* CloneObject() const \
{ \
	dooms::DObject* clonedObject = nullptr; \
	/* std::vector<std::unique_ptr> can make false positive for std::is_copy_constructible<std::vector<std::unique_ptr>>::value. So Please explicitly delete copy constructor if you have this type variable */ \
	if constexpr( (std::is_copy_constructible<dooms::Entity>::value == true) && (std::is_base_of<dooms::DObject, dooms::Entity>::value == true) ) \
	{ \
		 clonedObject = dooms::CreateDObject<dooms::Entity>(*this); \
	} \
	assert(clonedObject != nullptr);	\
	return clonedObject;	\
}


#undef CURRENT_TYPE_ALIAS_dooms__Entity
#define CURRENT_TYPE_ALIAS_dooms__Entity \
public : \
typedef dooms::Entity Current;


#undef TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Entity
#define TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Entity \
public : \
inline static const unsigned long int TYPE_FULL_NAME_HASH_VALUE = 1983755528; \
inline static const char* const TYPE_FULL_NAME = "dooms::Entity"; \
inline static const char* const TYPE_SHORT_NAME = "Entity"; \
virtual unsigned long int GetTypeHashVlue() const { return TYPE_FULL_NAME_HASH_VALUE; } \
virtual const char* GetTypeFullName() const { return TYPE_FULL_NAME; } \
virtual const char* GetTypeShortName() const { return TYPE_SHORT_NAME; }


#undef TYPE_CHECK_FUNCTION_Entity
#define TYPE_CHECK_FUNCTION_Entity \
private : \
attrNoReflect void __TYPE_CHECK() { static_assert(std::is_same_v<std::remove_reference<decltype(*this)>::type, Current> == true, "ERROR : WRONG TYPE. Please Check GENERATED_~ MACROS");} \


#undef GENERATE_BODY_FULLNAME_dooms__Entity
#define GENERATE_BODY_FULLNAME_dooms__Entity(...) \
INHERITANCE_INFORMATION_dooms__Entity \
CLONE_OBJECT_dooms__Entity \
CURRENT_TYPE_ALIAS_dooms__Entity \
TYPE_FULLNAME_HASH_VALUE_NAME_STRING_dooms__Entity \
TYPE_CHECK_FUNCTION_Entity \
private:


//Type Short Name ( without namespace, only type name ) Version Macros.
#define GENERATE_BODY_Entity(...) GENERATE_BODY_FULLNAME_dooms__Entity(__VA_ARGS__)


#undef GENERATE_BODY
#define GENERATE_BODY(...) GENERATE_BODY_FULLNAME_dooms__Entity(__VA_ARGS__)


//-------------------------------------------


