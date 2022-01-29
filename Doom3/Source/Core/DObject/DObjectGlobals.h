#pragma once

#include <type_traits>

#include "DObject.h"
#include "DObjectManager.h"

#include <CompilerMacros.h>
#include "DObjectMacros.h"
#include "Macros/Assert.h"

#include "Reflection/ReflectionType/DClass.h"

namespace dooms
{
	/// <summary>
	/// Check if passed address isn't dummy address or already deleted dObject address ,
	///	if it's valid address, check if dobject is on pending kill.
	/// </summary>
	/// <param name="dObject"></param>
	/// <returns></returns>
	extern FORCE_INLINE bool IsLowLevelValid(const DObject* const dObject, const bool lock = false, const std::memory_order memoryOrder = std::memory_order_seq_cst)
	{
		return dooms::DObjectManager::IsDObjectLowLevelValid(dObject, lock, memoryOrder);
	}

	/// <summary>
	/// weak valid check
	///	Check if passed pointer isn't null pointer.
	///	if not, check dObject isn't on pending kill
	/// </summary>
	/// <param name="dObject"></param>
	/// <returns></returns>
	extern FORCE_INLINE bool IsValid(const DObject* const dObject, const std::memory_order memoryOrder = std::memory_order_relaxed)
	{
		return (dObject != nullptr) && (dObject->GetIsPendingKill(memoryOrder) == false);
	}

	template <typename DObjectType, typename... Args>
	extern DObjectType* CreateDObject(const DObjectContructorParams& dObjectConstructorParams, Args&&... args)
	{
		static_assert(IS_DOBJECT_TYPE(DObjectType) == true);

		//DObjectType's Constructor should be public function
		DObjectType* newDObject = new DObjectType(std::forward<Args>(args)...);

		DObjectContructorParams params(dObjectConstructorParams);
		params.DObjectFlag |= dooms::eDObjectFlag::NewAllocated;

		static_cast<DObject*>(newDObject)->InitProperties(params);

		return newDObject;
	}

	template <typename DObjectType, typename... Args>
	extern DObjectType* CreateDObject(Args&&... args)
	{
		static_assert(IS_DOBJECT_TYPE(DObjectType) == true);

		//DObjectType's Constructor should be public function
		DObjectType* newDObject = new DObjectType(std::forward<Args>(args)...);

		DObjectContructorParams params{};
		params.DObjectFlag |= dooms::eDObjectFlag::NewAllocated;

		static_cast<DObject*>(newDObject)->InitProperties(params);

		return newDObject;
	}
	
	extern bool DestroyDObject(DObject* const dObject);


#define CASTING_STATIC_ASSERT(CASTING_TYPE)																													\
static_assert(std::is_pointer_v<CASTING_TYPE> == true, "Please Pass Pointer Type as IsA function's template argument");										\
static_assert(IS_DOBJECT_TYPE(std::remove_pointer_t<CASTING_TYPE>) == true, "Please Pass DObject's child Type as IsA function's template argument");		\

#define CASTING_STATIC_ASSERT_PAIR(FROM_CASTING_TYPE, TO_CASTING_TYPE)		\
		CASTING_STATIC_ASSERT(FROM_CASTING_TYPE);							\
		CASTING_STATIC_ASSERT(TO_CASTING_TYPE);								\
		static_assert( ( std::conditional<std::is_const_v<std::remove_pointer_t<FROM_CASTING_TYPE>>, std::is_const<std::remove_pointer_t<TO_CASTING_TYPE>>, std::bool_constant<true>>::type::value ) == true, "If FromCasting Type is const-qualified type, ToCasting type should be const-qualified type")

	template <typename CompareType>
	extern FORCE_INLINE bool IsChildOf(const DObject* const dObject) noexcept
	{
		static_assert(std::is_pointer_v<CompareType> == false, "Don't Pass Pointer Type as IsA function's template argument");
		static_assert(IS_DOBJECT_TYPE(CompareType) == true, "Please Pass DObject's child Type as IsA function's template argument");
		D_ASSERT(IsValid(dObject) == true);

		return (IsValid(dObject) == true) && (dObject->IsChildOf<CompareType>());
	}

	namespace details
	{
		template<typename ToCastingType, typename FromCastingType>
		extern FORCE_INLINE ToCastingType CastToImp(FromCastingType dObject) noexcept
		{
			CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

			// if inherit at second pos, reinterpret_cast can make problem
			// ex) class GraphicsServer : public ISingleton, public DObject  <--- This can make problem!!
			return (IsChildOf<std::remove_pointer_t<ToCastingType>>(dObject) == true) ? ( reinterpret_cast<ToCastingType>(dObject) ) : ( nullptr );
		}

		template<typename ToCastingType, typename FromCastingType>
		extern FORCE_INLINE ToCastingType CastToUncheckedImp(FromCastingType dObject) noexcept
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
	extern FORCE_INLINE ToCastingType CastTo(FromCastingType dObject) noexcept
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

		ToCastingType result = nullptr;

		D_ASSERT(dObject != nullptr);
		if(dObject != nullptr)
		{
			if constexpr (std::is_base_of_v<std::remove_pointer_t<ToCastingType>, std::remove_pointer_t<FromCastingType>> == true)
			{
				result = details::CastToUncheckedImp<ToCastingType>(dObject);
			}
			else
			{
				result = details::CastToImp<ToCastingType>(dObject);
			}
		}

		return result;
	}
	
	template<typename ToCastingType, typename FromCastingType>
	extern FORCE_INLINE ToCastingType CastToUnchecked(FromCastingType dObject) noexcept
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

		//In Unchecked Casting, Check if correct
		D_ASSERT_LOG( (dObject != nullptr) && (IsChildOf<std::remove_pointer_t<ToCastingType>>(dObject) == true) , "Unchecked Casting looks incorrect");

		return details::CastToUncheckedImp<ToCastingType>(dObject);
	}



	
}
