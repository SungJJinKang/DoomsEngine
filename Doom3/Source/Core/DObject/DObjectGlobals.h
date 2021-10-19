#pragma once

#include <type_traits>

#include "DObject.h"
#include "DObjectManager.h"

#include <CompilerMacros.h>
#include "DObjectMacros.h"
#include "Macros/Assert.h"

namespace doom
{
	template <typename DObjectType, typename... Args>
	DObjectType* CreateDObject(const DObjectContructorParams& dObjectConstructorParams, Args&&... args)
	{
		static_assert(IS_DOBJECT_TYPE(DObjectType) == true);

		//DObjectType's Constructor should be public function
		DObjectType* const newDObject = new DObjectType(std::forward<Args>(args)...);

		DObjectContructorParams params(dObjectConstructorParams);
		params.DObjectFlag |= doom::eDObjectFlag::NewAllocated;

		static_cast<DObject*>(newDObject)->InitProperties(params);

		return newDObject;
	}

	template <typename DObjectType, typename... Args>
	DObjectType* CreateDObject(Args&&... args)
	{
		static_assert(IS_DOBJECT_TYPE(DObjectType) == true);

		//DObjectType's Constructor should be public function
		DObjectType* const newDObject = new DObjectType(std::forward<Args>(args)...);

		DObjectContructorParams params{};
		params.DObjectFlag |= doom::eDObjectFlag::NewAllocated;

		static_cast<DObject*>(newDObject)->InitProperties(params);

		return newDObject;
	}

	FORCE_INLINE bool IsValid(const DObject* const dObject)
	{
		return doom::DObjectManager::IsDObjectValid(dObject);
	}

#define CASTING_STATIC_ASSERT(CASTING_TYPE)																													\
static_assert(std::is_pointer_v<CASTING_TYPE> == true, "Please Pass Pointer Type as IsA function's template argument");										\
static_assert(IS_DOBJECT_TYPE(std::remove_pointer_t<CASTING_TYPE>) == true, "Please Pass DObject's child Type as IsA function's template argument");		\


	template <typename CompareType>
	FORCE_INLINE bool IsA(const DObject* const dObject)
	{
		static_assert(std::is_pointer_v<CompareType> == false, "Don't Pass Pointer Type as IsA function's template argument");						\
		static_assert(IS_DOBJECT_TYPE(CompareType) == true, "Please Pass DObject's child Type as IsA function's template argument");		\
			
		return dObject->IsChildOf<CompareType>();
	}

	template <typename CompareType>
	FORCE_INLINE bool IsChildOf(const DObject* const dObject)
	{
		return IsA<CompareType>(dObject);
	}

	/// <summary>
	/// Cast passed dObject to CastingType ( template argument )
	///	This function support only up-down hierarchy
	///	Cant cast to sibling class
	///
	///	This function do type check using TypeID at runtime ( faster than dynamic_cast )
	///	If you ensure Casting will be success, Use CastToUnchecked
	/// </summary>
	/// <typeparam name="CastingType"></typeparam>
	/// <param name="dObject"></param>
	/// <returns></returns>
	template <typename CastingType>
	FORCE_INLINE CastingType CastTo(const DObject* const dObject)
	{
		CASTING_STATIC_ASSERT(CastingType);

		CastingType castedDObject = nullptr;

		D_ASSERT(IsA<std::remove_pointer_t<CastingType>>(dObject) == true);
		if(IsA<std::remove_pointer_t<CastingType>>(dObject) == true)
		{
			castedDObject = reinterpret_cast<CastingType>(dObject);
		}

		return castedDObject;
	}
	template <typename CastingType>
	FORCE_INLINE CastingType CastTo(DObject* const dObject)
	{
		CASTING_STATIC_ASSERT(CastingType);

		CastingType castedDObject = nullptr;

		D_ASSERT(IsA<std::remove_pointer_t<CastingType>>(dObject) == true);
		if (IsA<std::remove_pointer_t<CastingType>>(dObject) == true)
		{
			castedDObject = reinterpret_cast<CastingType>(dObject);
		}

		return castedDObject;
	}

	//TODO : 지금은 해당 타입의 원래 타입으로만 캐스팅 가능하다. 부모타입으로 캐스팅 못함

	/// <summary>
	/// Cast passed dObject to CastingType ( template argument )
	///	This function support only up-down hierarchy
	///	Cant cast to sibling class
	///
	///	This function don't type check at runtime ( but in debug mode, If casting fail, it make assert )
	/// </summary>
	/// <typeparam name="CastingType"></typeparam>
	/// <param name="dObject"></param>
	/// <returns></returns>
	template <typename CastingType>
	FORCE_INLINE CastingType CastToUnchecked(const DObject* const dObject)
	{
		CASTING_STATIC_ASSERT(CastingType);

		D_ASSERT(IsA<std::remove_pointer_t<CastingType>>(dObject) == true);
		return reinterpret_cast<CastingType>(dObject);
	}
	template <typename CastingType>
	FORCE_INLINE CastingType CastToUnchecked(DObject* const dObject)
	{
		CASTING_STATIC_ASSERT(CastingType);

		D_ASSERT(IsA<std::remove_pointer_t<CastingType>>(dObject) == true);
		return reinterpret_cast<CastingType>(dObject);
	}
}
