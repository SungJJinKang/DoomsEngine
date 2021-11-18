#pragma once

#include <type_traits>
#include <array>

#include <Macros/TypeDef.h>
#include <Macros/MacrosHelper.h>
#include <Macros/Assert.h>

#include "Reflection/Reflection.h"


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


/*
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
*/






/////////////////////////////////







//TODO : https://github.com/Celtoys/clReflect �̰� ��� ���� ( ������ ��ũ�� �߰����� �ʿ���� ���� ���� �ҽ����� �м��ؼ� �˾Ƽ� �м����ش� )