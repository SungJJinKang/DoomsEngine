#pragma once

#include <typeinfo>
#include <type_traits>

#ifndef TYPE_ID_HASH_CODE
#define TYPE_ID_HASH_CODE(CLASS_TYPE) typeid(CLASS_TYPE).hash_code()				
#endif



#ifndef _CLONE_DOBJECT

#define _CLONE_DOBJECT(CLASS_TYPE)													\
	public:																			\
	virtual CLASS_TYPE*	CLONE_OBJECT () const										\
	{																				\
		CLASS_TYPE* newObject = doom::CreateDObject<CLASS_TYPE>(*this);				\
		return newObject;															\
	}																				\

#endif



#ifndef _CLONE_ABSTRACT_DOBJECT

#define _CLONE_ABSTRACT_DOBJECT(CLASS_TYPE)											\
	public:																			\
	virtual CLASS_TYPE*	CLONE_OBJECT () const = 0;									\

#endif



#ifndef TYPE_ID_FUNCTION

#define TYPE_ID_FUNCTION(CLASS_TYPE)												\
		public:																		\
		virtual SIZE_T TYPE_ID() const { return TYPE_ID_HASH_CODE(CLASS_TYPE); }	\

#endif

virtual SIZE_T GetSubClassIDList() const
{
	
}


#ifndef _HAS_VIRTUAL_DESTRUCTOR

#define _HAS_VIRTUAL_DESTRUCTOR(CLASS_TYPE)																		\
	static_assert(std::has_virtual_destructor_v<CLASS_TYPE> == true, "Please put virtual(!!) to Destructor");	\

#endif



#ifndef DOBJECT_BODY

#define DOBJECT_BODY(CLASS_TYPE)													\
		_CLONE_DOBJECT(CLASS_TYPE)													\
		TYPE_ID_FUNCTION(CLASS_TYPE)												\

#endif



#ifndef DOBJECT_ABSTRACT_CLASS_BODY

#define DOBJECT_ABSTRACT_CLASS_BODY(CLASS_TYPE)										\
		_CLONE_ABSTRACT_DOBJECT(CLASS_TYPE)											\
		TYPE_ID_FUNCTION(CLASS_TYPE)												\
		
#endif