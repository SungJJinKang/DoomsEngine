#pragma once

#include <type_traits>

#include "DObject.h"
#include "DObjectManager.h"

#include <CompilerMacros.h>
#include "DObjectMacros.h"
#include "Macros/Assert.h"

#define REMOVE_POINTER_T(POINTER_TYPE) std::remove_pointer_t<POINTER_TYPE>
#define IS_POINTER_TYPE(POINTER_TYPE) std::is_pointer_v<POINTER_TYPE>

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
static_assert(IS_POINTER_TYPE(CASTING_TYPE) == true, "Please Pass Pointer Type as IsA function's template argument");										\
static_assert(IS_DOBJECT_TYPE(REMOVE_POINTER_T(CASTING_TYPE)) == true, "Please Pass DObject's child Type as IsA function's template argument");		\

#define CASTING_STATIC_ASSERT_PAIR(FROM_CASTING_TYPE, TO_CASTING_TYPE)		\
		CASTING_STATIC_ASSERT(FROM_CASTING_TYPE);							\
		CASTING_STATIC_ASSERT(TO_CASTING_TYPE);								\
		static_assert( ( std::conditional<std::is_const_v<REMOVE_POINTER_T(FROM_CASTING_TYPE)>, std::is_const<REMOVE_POINTER_T(TO_CASTING_TYPE)>, std::bool_constant<true>>::type::value ) == true, "If FromCasting Type is const-qualified type, ToCasting type should be const-qualified type")

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

	namespace details
	{
		template<typename ToCastingType, typename FromCastingType>
		FORCE_INLINE ToCastingType CastToImp(FromCastingType dObject)
		{
			CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

			return (dObject != nullptr && IsA<REMOVE_POINTER_T(ToCastingType)>(dObject) == true) ? reinterpret_cast<ToCastingType>(dObject) : nullptr;
		}

		template<typename ToCastingType, typename FromCastingType>
		FORCE_INLINE ToCastingType CastToUncheckedImp(FromCastingType dObject)
		{
			CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

			return reinterpret_cast<ToCastingType>(dObject);
		}
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
	template<typename ToCastingType, typename FromCastingType>
	FORCE_INLINE ToCastingType CastTo(FromCastingType dObject)
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

		if constexpr(std::is_base_of_v<REMOVE_POINTER_T(ToCastingType), REMOVE_POINTER_T(FromCastingType)> == true)
		{
			return details::CastToUncheckedImp<ToCastingType>(dObject);
		}
		else
		{
			return details::CastToImp<ToCastingType>(dObject);
		}
	}
	
	template<typename ToCastingType, typename FromCastingType>
	FORCE_INLINE ToCastingType CastToUnchecked(FromCastingType dObject)
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

		//In Unchecked Casting, Check if correct
		D_ASSERT_LOG( (dObject != nullptr) && (IsA<REMOVE_POINTER_T(ToCastingType)>(dObject) == true) , "Unchecked Casting looks incorrect");

		return details::CastToUncheckedImp<ToCastingType>(dObject);
	}
}
