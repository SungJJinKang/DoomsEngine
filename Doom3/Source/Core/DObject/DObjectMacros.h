#pragma once

#include <typeinfo>
#include <type_traits>

#include <Macros/TypeDef.h>
#include <Macros/MacrosHelper.h>
#include <Macros/Assert.h>

#ifndef TYPE_ID_HASH_CODE

#define TYPE_ID_HASH_CODE(CLASS_TYPE) typeid(CLASS_TYPE).hash_code()

#endif

/////////////////////////////////

namespace doom
{
	enum eDOBJECT_ClassFlags : UINT32
	{
		_Dummy = 0,
		NonCopyable = 1 << 0,
		NonMovable = 1 << 1,
		IsAbstract = 1 << 2
	};
}



template<doom::eDOBJECT_ClassFlags...flags> struct flag_or {
	static constexpr UINT32 value = (static_cast<UINT32>(flags) | ...);
};

#ifndef CLASS_FLAGS_FUNCTION

#define CLASS_FLAGS_FUNCTION(...)																			\
		public:																								\
		constexpr static UINT32 CLASS_FLAGS_STATIC() {														\
			return flag_or<eDOBJECT_ClassFlags::_Dummy, __VA_ARGS__>::value;								\
		}																									\
        virtual UINT32 CLASS_FLAGS() const { return CLASS_FLAGS_STATIC(); }									\

#endif

/////////////////////////////////

#ifndef _CLONE_DOBJECT

#define _CLONE_DOBJECT(CLASS_TYPE)															\
	public:																					\
	virtual CLASS_TYPE*	CLONE_DOBJECT () const												\
	{																						\
		CLASS_TYPE* newObject = nullptr;													\
		if constexpr( (CLASS_FLAGS_STATIC() & eDOBJECT_ClassFlags::NonCopyable) == false )	\
		{																					\
			newObject = doom::CreateDObject<CLASS_TYPE>(*this);								\
		}																					\
		D_ASSERT(newObject != nullptr);														\
		return newObject;																	\
	}																						\

#endif

/////////////////////////////////

#ifndef _CLONE_ABSTRACT_DOBJECT

#define _CLONE_ABSTRACT_DOBJECT(CLASS_TYPE)											\
	public:																			\
	virtual CLASS_TYPE*	CLONE_DOBJECT () const = 0;									\

#endif

/////////////////////////////////

#ifndef TYPE_ID_FUNCTION

#define TYPE_ID_FUNCTION(CLASS_TYPE)												\
		public:																		\
		static SIZE_T TYPE_ID_STATIC() {											\
			static const SIZE_T TYPE_ID##CLASS_TYPE = TYPE_ID_HASH_CODE(CLASS_TYPE);\
			return TYPE_ID##CLASS_TYPE;												\
		}																			\
        virtual SIZE_T TYPE_ID() const { return TYPE_ID_STATIC(); }					\

#endif

/*
virtual SIZE_T GetSubClassIDList() const
{
	
}*/
/////////////////////////////////


#ifndef _HAS_VIRTUAL_DESTRUCTOR

#define _HAS_VIRTUAL_DESTRUCTOR(CLASS_TYPE)																		\
	static_assert(std::has_virtual_destructor_v<CLASS_TYPE> == true, "Please put virtual(!!) to Destructor");	\

#endif

/////////////////////////////////

#ifndef _CHECK_DOBJECT_PARAMETER_TYPE_CORRECT

#define _CHECK_DOBJECT_PARAMETER_TYPE_CORRECT(CLASS_TYPE)																				\
		D_ASSERT_LOG(TYPE_ID_HASH_CODE(*this) == TYPE_ID_HASH_CODE(CLASS_TYPE), "Incorrect typeid ( %s )", MAKE_STRING(CLASS_TYPE));	\
		D_ASSERT_LOG(TYPE_ID_HASH_CODE(*this) == TYPE_ID_STATIC(), "Incorrect typeid ( %s )", MAKE_STRING(CLASS_TYPE));					\
		D_ASSERT_LOG(TYPE_ID_HASH_CODE(*this) == TYPE_ID(), "Incorrect typeid ( %s )", MAKE_STRING(CLASS_TYPE));						\
		D_ASSERT_LOG(TYPE_ID_HASH_CODE(CLASS_TYPE) == TYPE_ID(), "Incorrect typeid ( %s )", MAKE_STRING(CLASS_TYPE));					\
		D_ASSERT_LOG(TYPE_ID_STATIC() == TYPE_ID(), "Incorrect typeid ( %s )", MAKE_STRING(CLASS_TYPE));								\

#endif

/////////////////////////////////

#if defined(DEBUG_MODE)



#undef _RUNTIME_CHECKER

#define _RUNTIME_CHECKER(CLASS_TYPE)													\
	private:																			\
	bool _dobject_runtime_checker() const												\
	{																					\
		_CHECK_DOBJECT_PARAMETER_TYPE_CORRECT(CLASS_TYPE);								\
		return true;																	\
	}																					\
	bool CONCAT(_runtime_checker_valid_,CLASS_TYPE) = _dobject_runtime_checker();		\

#else

#undef _RUNTIME_CHECKER
#define _RUNTIME_CHECKER(CLASS_TYPE)

#endif


/////////////////////////////////

#ifndef DOBJECT_BODY_UNIFORM

#define DOBJECT_BODY_UNIFORM(CLASS_TYPE, ...)										\
		CLASS_FLAGS_FUNCTION(__VA_ARGS__)											\
		TYPE_ID_FUNCTION(CLASS_TYPE)												\
		_RUNTIME_CHECKER(CLASS_TYPE)												\

#endif

/////////////////////////////////

#ifndef DOBJECT_CLASS_BODY

#define DOBJECT_CLASS_BODY(CLASS_TYPE, ...)											\
		DOBJECT_BODY_UNIFORM(CLASS_TYPE, __VA_ARGS__)								\
		_CLONE_DOBJECT(CLASS_TYPE)													\

#endif

/////////////////////////////////

#ifndef DOBJECT_ABSTRACT_CLASS_BODY

#define DOBJECT_ABSTRACT_CLASS_BODY(CLASS_TYPE, ...)								\
		DOBJECT_BODY_UNIFORM(CLASS_TYPE, __VA_ARGS__)								\
		_CLONE_ABSTRACT_DOBJECT(CLASS_TYPE)											\

#endif