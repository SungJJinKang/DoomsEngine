#pragma once



#define _CLONE_DOBJECT(CLASS_TYPE)													\
	public:																			\
	virtual CLASS_TYPE*	CLONE_OBJECT () const										\
	{																				\
		CLASS_TYPE* newObject = doom::CreateDObject<CLASS_TYPE>(*this);				\
		return newObject;															\
	}																											\

#define _CLONE_ABSTRACT_DOBJECT(CLASS_TYPE)											\
	public:																			\
	virtual CLASS_TYPE*	CLONE_OBJECT () const = 0;									\



#define DOBJECT_BODY(CLASS_TYPE)													\
		_CLONE_DOBJECT(CLASS_TYPE)

#define DOBJECT_ABSTRACT_CLASS_BODY(CLASS_TYPE)										\
		_CLONE_ABSTRACT_DOBJECT(CLASS_TYPE)			