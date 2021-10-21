#pragma once

#include <type_traits>
#include <array>

#include <Macros/TypeDef.h>
#include <Macros/MacrosHelper.h>
#include <Macros/Assert.h>


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
		constexpr static const char* const __CLASS_TYPE_ID = MAKE_STRING(CLASS_TYPE);									\
		public:																											\
		FORCE_INLINE constexpr static const char* CLASS_TYPE_ID_STATIC() {												\
			return __CLASS_TYPE_ID;																						\
		}																												\
        virtual const char* GetClassTypeID() const { return CLASS_TYPE::CLASS_TYPE_ID_STATIC(); }		

#endif



/////////////////////////////////

namespace doom
{
	namespace details
	{
		template <typename BASE_DOBJECT_TYPE_CLASS>
		extern constexpr void BASE_CHAIN_HILLCLIMB_COUNT(SIZE_T& base_chain_count)
		{
			base_chain_count++;
			if constexpr (std::is_same_v<doom::DObject, BASE_DOBJECT_TYPE_CLASS> == false) {
				BASE_CHAIN_HILLCLIMB_COUNT<typename BASE_DOBJECT_TYPE_CLASS::Base>(base_chain_count);
			}
		}

		template <typename BASE_DOBJECT_TYPE_CLASS>
		extern constexpr SIZE_T BASE_CHAIN_HILLCLIMB_COUNT()
		{
			SIZE_T base_chain_count = 1;
			if constexpr (std::is_same_v <doom::DObject, BASE_DOBJECT_TYPE_CLASS > == false) {
				BASE_CHAIN_HILLCLIMB_COUNT<typename BASE_DOBJECT_TYPE_CLASS::Base>(base_chain_count);
			}
			return base_chain_count;
		}

		template <typename BASE_DOBJECT_TYPE_CLASS, SIZE_T COUNT>
		extern constexpr void BASE_CHAIN_HILLCLIMB_DATA(SIZE_T& count, std::array<const char*, COUNT>& chain_data)
		{
			chain_data[count] = BASE_DOBJECT_TYPE_CLASS::__CLASS_TYPE_ID;
			count++;
			if constexpr (std::is_same_v<doom::DObject, BASE_DOBJECT_TYPE_CLASS> == false) {
				BASE_CHAIN_HILLCLIMB_DATA<typename BASE_DOBJECT_TYPE_CLASS::Base>(count, chain_data);
			}
		}

		template <typename BASE_DOBJECT_TYPE_CLASS, SIZE_T COUNT>
		extern constexpr std::array<const char*, COUNT> BASE_CHAIN_HILLCLIMB_DATA()
		{
			std::array<const char*, COUNT> chain_data{};
			chain_data[0] = BASE_DOBJECT_TYPE_CLASS::__CLASS_TYPE_ID;
			if constexpr (std::is_same_v <doom::DObject, BASE_DOBJECT_TYPE_CLASS > == false) {
				SIZE_T count = 1;
				BASE_CHAIN_HILLCLIMB_DATA<typename BASE_DOBJECT_TYPE_CLASS::Base>(count, chain_data);
			}
			return chain_data;
		}
	}
}





#define DOBJECT_CLASS_BASE_CHAIN(BASE_DOBJECT_TYPE_CLASS)													\
	static_assert(std::is_same_v<Current, BASE_DOBJECT_TYPE_CLASS> == false);								\
	public:																									\
	using Base = BASE_DOBJECT_TYPE_CLASS; /* alias Base DObject Type Class */								\
	private:																								\
	constexpr static SIZE_T _BASE_CHAIN_COUNT = doom::details::BASE_CHAIN_HILLCLIMB_COUNT<Current>();		\
	constexpr static std::array<const char*, _BASE_CHAIN_COUNT> _BASE_CHAIN_DATA = doom::details::BASE_CHAIN_HILLCLIMB_DATA<Current, _BASE_CHAIN_COUNT>();			\
	public:																									\
	FORCE_INLINE constexpr static SIZE_T BASE_CHAIN_COUNT_STATIC()											\
	{																										\
		return _BASE_CHAIN_COUNT;																			\
	}																										\
	FORCE_INLINE constexpr static const char* const * BASE_CHAIN_DATA_STATIC()								\
	{																										\
		return _BASE_CHAIN_DATA.data();																		\
	}																										\
	virtual SIZE_T GetBaseChainCount() const { return BASE_CHAIN_COUNT_STATIC(); }							\
	virtual const char* const * GetBaseChainData() const { return BASE_CHAIN_DATA_STATIC(); }


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
		public:																		\
		using Current = CLASS_TYPE;													\
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