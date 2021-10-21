#pragma once

#include <typeinfo>
#include <type_traits>
#include <vector>

#include <Macros/TypeDef.h>
#include <Macros/MacrosHelper.h>
#include <Macros/Assert.h>

#include "DOBJECT_BASE_CHAIN.h"

namespace doom
{
	class DObject;
}

#define IS_DOBJECT_TYPE(TYPE) std::is_base_of_v<doom::DObject, TYPE>

#ifndef TYPE_ID_HASH_CODE

//#define TYPE_ID_HASH_CODE(CLASS_TYPE) typeid(CLASS_TYPE).hash_code()

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
	constexpr static UINT32 value = (static_cast<UINT32>(flags) | ...);
};

#ifndef CLASS_FLAGS_FUNCTION

#define CLASS_FLAGS_FUNCTION(CLASS_TYPE, ...)												\
		public:																				\
		FORCE_INLINE constexpr static UINT32 CLASS_FLAGS_STATIC() {							\
			return flag_or<eDOBJECT_ClassFlags::_Dummy, __VA_ARGS__>::value;				\
		}																					\
        virtual UINT32 GetClassFlags() const { return CLASS_TYPE::CLASS_FLAGS_STATIC(); }

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

#ifndef TYPE_ID_IMP

#define TYPE_ID_IMP(CLASS_TYPE)																							\
		public:																											\
		FORCE_INLINE constexpr static const char* CLASS_TYPE_ID_STATIC() {												\
			return MAKE_STRING(CLASS_TYPE);																				\
		}																												\
        virtual const char* GetClassTypeID() const { return CLASS_TYPE::CLASS_TYPE_ID_STATIC(); }		

#endif



/////////////////////////////////


//TODO : Make This Resolved at Compile Time!!!
#define DOBJECT_CLASS_BASE_CHAIN(BASE_DOBJECT_TYPE_CLASS)												\
	private:																							\
	using Base = BASE_DOBJECT_TYPE_CLASS; /* alias Base DObject Type Class */							\
	protected:																							\
	static DOBJECT_BASE_CHAIN BASE_CHAIN_HILLCLIMB() {													\
		D_ASSERT(CLASS_TYPE_ID_STATIC() != BASE_DOBJECT_TYPE_CLASS::CLASS_TYPE_ID_STATIC());			\
		DOBJECT_BASE_CHAIN base_chain{};																\
		BASE_DOBJECT_TYPE_CLASS::BASE_CHAIN_HILLCLIMB(base_chain);										\
		return base_chain;																				\
	}																									\
	static void BASE_CHAIN_HILLCLIMB(doom::DOBJECT_BASE_CHAIN& base_chain) {							\
		base_chain.Increment_BASE_CHAIN_COUNT();														\
		base_chain.BASE_CHAIN_TYPE_ID_LIST[base_chain.BASE_CHAIN_COUNT - 1] = CLASS_TYPE_ID_STATIC();	\
        BASE_DOBJECT_TYPE_CLASS::BASE_CHAIN_HILLCLIMB(base_chain);										\
	}																									\
	public:																								\
	FORCE_INLINE static const doom::DOBJECT_BASE_CHAIN& BASE_CHAIN_STATIC()									\
	{																									\
		static const doom::DOBJECT_BASE_CHAIN _BASE_CHAIN = BASE_CHAIN_HILLCLIMB();						\
		return _BASE_CHAIN;																				\
	}																									\
	virtual const doom::DOBJECT_BASE_CHAIN& GetBaseChain() const { return BASE_CHAIN_STATIC(); }



/////////////////////////////////



#ifndef CLASS_NAME_IMP

#define CLASS_NAME_IMP(CLASS_TYPE)																						\
		public:																											\
		FORCE_INLINE constexpr static const char* CLASS_NAME_STATIC() {													\
			/* doom::Renderer 이런식으로 타입 적었을 때 대비해야한다. 마지막 "::" 뒤의 문자열만 저장되어야한다   */		\
			return MAKE_STRING(CLASS_TYPE);																				\
		}																												\
        virtual const char* GetClassName() const { return CLASS_TYPE::CLASS_NAME_STATIC(); }		

#endif


/////////////////////////////////

#ifndef DCLASS_IMP

//TODO : If _BASE_CHAIN become resolved at compile time, Do This Also at Compile time
#include "DClass.h"
#define DCLASS_IMP(CLASS_TYPE)															\
		public :																		\
		FORCE_INLINE static doom::DClass StaticClass()									\
		{																				\
			return doom::CreateDClass<CLASS_TYPE>();									\
		}																				\
		virtual doom::DClass GetDClass() const { return CLASS_TYPE::StaticClass(); }

#endif

/////////////////////////////////

#ifndef DOBJECT_BODY_UNIFORM

#define DOBJECT_BODY_UNIFORM(CLASS_TYPE, ...)										\
		CLASS_FLAGS_FUNCTION(CLASS_TYPE, __VA_ARGS__)								\
		TYPE_ID_IMP(CLASS_TYPE)														\
		CLASS_NAME_IMP(CLASS_TYPE)													\
		DCLASS_IMP(CLASS_TYPE)														

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
		DOBJECT_BODY_UNIFORM(CLASS_TYPE, doom::eDOBJECT_ClassFlags::NonCopyable, doom::eDOBJECT_ClassFlags::NonMovable, doom::eDOBJECT_ClassFlags::IsAbstract, __VA_ARGS__)		\
		_CLONE_ABSTRACT_DOBJECT(CLASS_TYPE)											\

#endif



//TODO : https://github.com/Celtoys/clReflect 이거 사용 고려 ( 일일이 매크로 추가해줄 필요없이 빌드 전에 소스파일 분석해서 알아서 분석해준다 )