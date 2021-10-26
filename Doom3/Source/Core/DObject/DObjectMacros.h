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

#define CLASS_FLAGS_FUNCTION(CLASS_TYPE, ...)																	\
		private:																								\
		constexpr static UINT32 __CLASS_CLASS_FLAGS = flag_or<eDOBJECT_ClassFlags::_Dummy, __VA_ARGS__>::value;	\
		public:																									\
		[[nodiscard]] FORCE_INLINE constexpr static UINT32 CLASS_FLAGS_STATIC() noexcept{						\
			return __CLASS_CLASS_FLAGS;																			\
		}																										\
        [[nodiscard]]  virtual UINT32 GetClassFlags() const noexcept { return CLASS_TYPE::CLASS_FLAGS_STATIC(); }

#endif

/////////////////////////////////

#ifndef _CREATE_DOBJECT

#define _CREATE_DOBJECT(CLASS_TYPE)															\
	public:																					\
	[[nodiscard]] static doom::DObject* CREATE_THIS_DOBJECT()								\
	{																						\
		doom::DObject* const newDObject = doom::CreateDObject<CLASS_TYPE>();				\
		D_ASSERT(newDObject != nullptr);													\
		return newDObject;																	\
	}																						\

#endif

#ifndef _CLONE_DOBJECT

#define _CLONE_DOBJECT(CLASS_TYPE)															\
	public:																					\
	[[nodiscard]] virtual CLASS_TYPE* CLONE_DOBJECT () const								\
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
///

#ifndef TYPE_ID_IMP

#define TYPE_ID_IMP(CLASS_TYPE)																							\
		public:																											\
		constexpr static const char* const __CLASS_TYPE_ID = MAKE_STRING(CLASS_TYPE);									\
		[[nodiscard]] FORCE_INLINE constexpr static const char* CLASS_TYPE_ID_STATIC() noexcept{						\
			return __CLASS_TYPE_ID;																						\
		}																												\
        [[nodiscard]] virtual const char* GetClassTypeID() const noexcept{												\
		static_assert(std::is_same_v<std::decay<decltype(*this)>::type, CLASS_TYPE> == true, "Wrong Current ClassType is passed");	\
		return CLASS_TYPE::CLASS_TYPE_ID_STATIC(); }		

#endif



/////////////////////////////////

namespace doom
{
	namespace details
	{
		//!!!!!!!!!!!!
		//Never change static to extern. static give hint to compiler that this definition is used only in source file(.cpp)
		//								 Then Compiler remove this functions definition from compiler if it is called only at compile time
		template <typename BASE_DOBJECT_TYPE_CLASS>
		static constexpr void BASE_CHAIN_HILLCLIMB_COUNT(SIZE_T& base_chain_count)
		{
			base_chain_count++;
			if constexpr (std::is_same_v<doom::DObject, BASE_DOBJECT_TYPE_CLASS> == false) {
				BASE_CHAIN_HILLCLIMB_COUNT<typename BASE_DOBJECT_TYPE_CLASS::Base>(base_chain_count);
			}
		}

		template <typename BASE_DOBJECT_TYPE_CLASS>
		static constexpr SIZE_T BASE_CHAIN_HILLCLIMB_COUNT()
		{
			SIZE_T base_chain_count = 1;
			if constexpr (std::is_same_v <doom::DObject, BASE_DOBJECT_TYPE_CLASS > == false) {
				BASE_CHAIN_HILLCLIMB_COUNT<typename BASE_DOBJECT_TYPE_CLASS::Base>(base_chain_count);
			}
			return base_chain_count;
		}

		template <typename BASE_DOBJECT_TYPE_CLASS, SIZE_T COUNT>
		static constexpr void BASE_CHAIN_HILLCLIMB_DATA(SIZE_T& count, std::array<const char*, COUNT>& chain_data)
		{
			chain_data[count] = BASE_DOBJECT_TYPE_CLASS::__CLASS_TYPE_ID;
			count++;
			if constexpr (std::is_same_v<doom::DObject, BASE_DOBJECT_TYPE_CLASS> == false) {
				BASE_CHAIN_HILLCLIMB_DATA<typename BASE_DOBJECT_TYPE_CLASS::Base>(count, chain_data);
			}
		}

		template <typename BASE_DOBJECT_TYPE_CLASS, SIZE_T COUNT>
		static constexpr std::array<const char*, COUNT> BASE_CHAIN_HILLCLIMB_DATA()
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

#define DOBJECT_ROOT_CLASS_BASE_CHAIN																				\
private:																											\
	constexpr static SIZE_T _BASE_CHAIN_COUNT = 1;																	\
	constexpr static const std::array<const char*, 1> _BASE_CHAIN_DATA{ __CLASS_TYPE_ID };							\
public:																												\
	[[nodiscard]] FORCE_INLINE constexpr static SIZE_T BASE_CHAIN_COUNT_STATIC() noexcept							\
	{																												\
		return 1;																									\
	}																												\
	[[nodiscard]] FORCE_INLINE constexpr static const char* const* BASE_CHAIN_DATA_STATIC() noexcept				\
	{																												\
		return _BASE_CHAIN_DATA.data();																				\
	}																												\
	[[nodiscard]] virtual SIZE_T GetBaseChainCount() const noexcept { return BASE_CHAIN_COUNT_STATIC(); }			\
	[[nodiscard]] virtual const char* const* GetBaseChainData() const noexcept { return BASE_CHAIN_DATA_STATIC(); }


#define DOBJECT_CLASS_BASE_CHAIN(BASE_DOBJECT_TYPE_CLASS)													\
	static_assert(std::is_base_of_v<doom::DObject, BASE_DOBJECT_TYPE_CLASS> == true);						\
	static_assert(std::is_same_v<Current, BASE_DOBJECT_TYPE_CLASS> == false);								\
	public:																									\
	using Base = BASE_DOBJECT_TYPE_CLASS; /* alias Base DObject Type Class */								\
	private:																								\
	constexpr static SIZE_T _BASE_CHAIN_COUNT = doom::details::BASE_CHAIN_HILLCLIMB_COUNT<Current>();		\
	constexpr static const std::array<const char*, _BASE_CHAIN_COUNT> _BASE_CHAIN_DATA = doom::details::BASE_CHAIN_HILLCLIMB_DATA<Current, _BASE_CHAIN_COUNT>();			\
	public:																									\
	[[nodiscard]] FORCE_INLINE constexpr static SIZE_T BASE_CHAIN_COUNT_STATIC() noexcept					\
	{																										\
		return _BASE_CHAIN_COUNT;																			\
	}																										\
	[[nodiscard]] FORCE_INLINE constexpr static const char* const * BASE_CHAIN_DATA_STATIC() noexcept		\
	{																										\
		return _BASE_CHAIN_DATA.data();																		\
	}																										\
	[[nodiscard]] virtual SIZE_T GetBaseChainCount() const noexcept { return BASE_CHAIN_COUNT_STATIC(); }	\
	[[nodiscard]] virtual const char* const * GetBaseChainData() const noexcept {							\
	static_assert(std::is_base_of_v<BASE_DOBJECT_TYPE_CLASS, std::decay<decltype(*this)>::type> == true, "Current Class Type is not derived from Passed Base ClassType is passed");	\
	return BASE_CHAIN_DATA_STATIC(); }


/////////////////////////////////



#ifndef CLASS_NAME_IMP

#define CLASS_NAME_IMP(CLASS_TYPE)																						\
		public:																											\
		[[nodiscard]] FORCE_INLINE constexpr static const char* CLASS_NAME_STATIC() noexcept {							\
			/* doom::Renderer 이런식으로 타입 적었을 때 대비해야한다. 마지막 "::" 뒤의 문자열만 저장되어야한다   */		\
			return __CLASS_TYPE_ID;																						\
		}																												\
        [[nodiscard]] virtual const char* GetClassName() const noexcept { return CLASS_TYPE::CLASS_NAME_STATIC(); }		

#endif


/////////////////////////////////

#include "DClass.h"

namespace doom
{
	namespace details
	{
		template <typename DOBJECT_TYPE>
		extern ::doom::DClass CreateDClass()
		{
			static_assert(std::is_base_of_v<doom::DObject, DOBJECT_TYPE> == true);

			doom::DObject* (*_CREATE_DOBJECT_FUNCTION_PTR) () = nullptr;

			if constexpr(std::is_abstract_v<DOBJECT_TYPE> == false)
			{
				_CREATE_DOBJECT_FUNCTION_PTR = &DOBJECT_TYPE::CREATE_THIS_DOBJECT;
			}

			return ::doom::DClass(
				sizeof(DOBJECT_TYPE),
				DOBJECT_TYPE::CLASS_TYPE_ID_STATIC(),
				DOBJECT_TYPE::BASE_CHAIN_COUNT_STATIC(),
				DOBJECT_TYPE::BASE_CHAIN_DATA_STATIC(),
				DOBJECT_TYPE::CLASS_NAME_STATIC(),
				DOBJECT_TYPE::CLASS_FLAGS_STATIC(),
				_CREATE_DOBJECT_FUNCTION_PTR
			);
		}
	}
}


#ifndef DCLASS_IMP

//TODO : If _BASE_CHAIN become resolved at compile time, Do This Also at Compile time

#define DCLASS_IMP(CLASS_TYPE)																			\
		public :																						\
		[[nodiscard]] FORCE_INLINE static doom::DClass* StaticClass()									\
		{																								\
			static doom::DClass _CLASS_DCLASS = doom::details::CreateDClass<CLASS_TYPE>();				\
			return &_CLASS_DCLASS;																		\
		}																								\
		[[nodiscard]] virtual doom::DClass* GetDClass() const { return CLASS_TYPE::StaticClass(); }

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
		_CREATE_DOBJECT(CLASS_TYPE)													\

#endif

/////////////////////////////////

#ifndef DOBJECT_ABSTRACT_CLASS_BODY

#define DOBJECT_ABSTRACT_CLASS_BODY(CLASS_TYPE, ...)								\
		DOBJECT_BODY_UNIFORM(CLASS_TYPE, doom::eDOBJECT_ClassFlags::NonCopyable, doom::eDOBJECT_ClassFlags::NonMovable, doom::eDOBJECT_ClassFlags::IsAbstract, __VA_ARGS__)		\
		_CLONE_ABSTRACT_DOBJECT(CLASS_TYPE)											\

#endif



//TODO : https://github.com/Celtoys/clReflect 이거 사용 고려 ( 일일이 매크로 추가해줄 필요없이 빌드 전에 소스파일 분석해서 알아서 분석해준다 )