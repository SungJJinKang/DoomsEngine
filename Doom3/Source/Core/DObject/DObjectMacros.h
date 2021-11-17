#pragma once

#include <type_traits>
#include <array>

#include <Macros/TypeDef.h>
#include <Macros/MacrosHelper.h>
#include <Macros/Assert.h>



namespace dooms
{
	class DObject;
}

#define IS_DOBJECT_TYPE(TYPE) std::is_base_of_v<dooms::DObject, TYPE>

#ifndef TYPE_ID_HASH_CODE

//#define TYPE_ID_HASH_CODE(CLASS_TYPE) typeid(CLASS_TYPE).hash_code()

#endif

/////////////////////////////////

namespace dooms
{
	enum D_ENUM eDOBJECT_ClassFlags : UINT32
	{
		_Dummy = 0,
		NonCopyable = 1 << 0,
		NonMovable = 1 << 1,
		IsAbstract = 1 << 2
	};
}



template<dooms::eDOBJECT_ClassFlags...flags> struct flag_or {
	constexpr static UINT32 value = (static_cast<UINT32>(flags) | ...);
};

#ifndef CLASS_FLAGS_FUNCTION

#define CLASS_FLAGS_FUNCTION(CLASS_TYPE, ...)																	\
		private:																								\
		constexpr static UINT32 __CLASS_CLASS_FLAGS = flag_or<eDOBJECT_ClassFlags::_Dummy, __VA_ARGS__>::value;	\
		public:																									\
		NO_DISCARD FORCE_INLINE constexpr static UINT32 CLASS_FLAGS_STATIC() noexcept{						\
			return __CLASS_CLASS_FLAGS;																			\
		}																										\
        NO_DISCARD  virtual UINT32 GetClassFlags() const noexcept { return CLASS_TYPE::CLASS_FLAGS_STATIC(); }

#endif

/////////////////////////////////

#ifndef _CREATE_DOBJECT

#define _CREATE_DOBJECT(CLASS_TYPE)															\
	public:																					\
	NO_DISCARD static dooms::DObject* CREATE_THIS_DOBJECT()								\
	{																						\
		dooms::DObject* const newDObject = dooms::CreateDObject<CLASS_TYPE>();				\
		D_ASSERT(newDObject != nullptr);													\
		return newDObject;																	\
	}																						\

#endif






/////////////////////////////////

#include "Reflection/ReflectionType/DClass.h"

namespace dooms
{
	namespace details
	{
		template <typename DOBJECT_TYPE>
		extern ::dooms::DClass CreateDClass()
		{
			static_assert(std::is_base_of_v<dooms::DObject, DOBJECT_TYPE> == true);

			dooms::DObject* (*_CREATE_DOBJECT_FUNCTION_PTR) () = nullptr;

			if constexpr(std::is_abstract_v<DOBJECT_TYPE> == false)
			{
				_CREATE_DOBJECT_FUNCTION_PTR = &DOBJECT_TYPE::CREATE_THIS_DOBJECT;
			}

			return ::dooms::DClass(
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





//TODO : https://github.com/Celtoys/clReflect �̰� ��� ���� ( ������ ��ũ�� �߰����� �ʿ���� ���� ���� �ҽ����� �м��ؼ� �˾Ƽ� �м����ش� )