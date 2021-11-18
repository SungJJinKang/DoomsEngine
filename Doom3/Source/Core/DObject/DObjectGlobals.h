#pragma once

#include <type_traits>

#include "DObject.h"
#include "DObjectManager.h"

#include <CompilerMacros.h>
#include "DObjectMacros.h"
#include "Macros/Assert.h"

#include "Reflection/ReflectionType/DClass.h"

#define REMOVE_POINTER_T(POINTER_TYPE) std::remove_pointer_t<POINTER_TYPE>
#define IS_POINTER_TYPE(POINTER_TYPE) std::is_pointer_v<POINTER_TYPE>

namespace dooms
{


	template <typename DObjectType, typename... Args>
	DObjectType* CreateDObject(const DObjectContructorParams& dObjectConstructorParams, Args&&... args)
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
	DObjectType* CreateDObject(Args&&... args)
	{
		//DObjectType's Constructor should be public function
		DObjectType* newDObject = new DObjectType(std::forward<Args>(args)...);

		DObjectContructorParams params{};
		params.DObjectFlag |= dooms::eDObjectFlag::NewAllocated;

		static_cast<DObject*>(newDObject)->InitProperties(params);

		return newDObject;
	}

	FORCE_INLINE bool IsValid(const DObject* const dObject)
	{
		return dooms::DObjectManager::IsDObjectValid(dObject);
	}

#define CASTING_STATIC_ASSERT(CASTING_TYPE)																													\
static_assert(IS_POINTER_TYPE(CASTING_TYPE) == true, "Please Pass Pointer Type as IsA function's template argument");										\
static_assert(IS_DOBJECT_TYPE(REMOVE_POINTER_T(CASTING_TYPE)) == true, "Please Pass DObject's child Type as IsA function's template argument");		\

#define CASTING_STATIC_ASSERT_PAIR(FROM_CASTING_TYPE, TO_CASTING_TYPE)		\
		CASTING_STATIC_ASSERT(FROM_CASTING_TYPE);							\
		CASTING_STATIC_ASSERT(TO_CASTING_TYPE);								\
		static_assert( ( std::conditional<std::is_const_v<REMOVE_POINTER_T(FROM_CASTING_TYPE)>, std::is_const<REMOVE_POINTER_T(TO_CASTING_TYPE)>, std::bool_constant<true>>::type::value ) == true, "If FromCasting Type is const-qualified type, ToCasting type should be const-qualified type")

	template <typename CompareType>
	FORCE_INLINE bool IsChildOf(const DObject* const dObject) noexcept
	{
		static_assert(std::is_pointer_v<CompareType> == false, "Don't Pass Pointer Type as IsA function's template argument");
		static_assert(IS_DOBJECT_TYPE(CompareType) == true, "Please Pass DObject's child Type as IsA function's template argument");
		D_ASSERT(IsValid(dObject) == true);

		return (IsValid(dObject) == true) && (dObject->IsChildOf<CompareType>());
	}

	namespace details
	{
		template<typename ToCastingType, typename FromCastingType>
		FORCE_INLINE ToCastingType CastToImp(FromCastingType dObject) noexcept
		{
			CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

			// if inherit at second pos, reinterpret_cast can make problem
			// ex) class GraphicsServer : public ISingleton, public DObject  <--- This can make problem!!
			return (IsChildOf<REMOVE_POINTER_T(ToCastingType)>(dObject) == true) ? ( reinterpret_cast<ToCastingType>(dObject) ) : ( nullptr );
		}

		template<typename ToCastingType, typename FromCastingType>
		FORCE_INLINE ToCastingType CastToUncheckedImp(FromCastingType dObject) noexcept
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
	FORCE_INLINE ToCastingType CastTo(FromCastingType dObject) noexcept
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

		ToCastingType* result = nullptr;

		D_ASSERT(dObject != nullptr);
		if(dObject != nullptr)
		{
			if constexpr (std::is_base_of_v<REMOVE_POINTER_T(ToCastingType), REMOVE_POINTER_T(FromCastingType)> == true)
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
	FORCE_INLINE ToCastingType CastToUnchecked(FromCastingType dObject) noexcept
	{
		CASTING_STATIC_ASSERT_PAIR(FromCastingType, ToCastingType);

		//In Unchecked Casting, Check if correct
		D_ASSERT_LOG( (dObject != nullptr) && (IsChildOf<REMOVE_POINTER_T(ToCastingType)>(dObject) == true) , "Unchecked Casting looks incorrect");

		return details::CastToUncheckedImp<ToCastingType>(dObject);
	}



	template <typename DOBJECT_TYPE>
	extern dooms::DClass CreateDClass()
	{
		static_assert(std::is_base_of_v<dooms::DObject, DOBJECT_TYPE> == true);

		/*dooms::DObject* (*_CREATE_DOBJECT_FUNCTION_PTR) () = nullptr;

		if constexpr (std::is_abstract_v<DOBJECT_TYPE> == false)
		{
			_CREATE_DOBJECT_FUNCTION_PTR = &DOBJECT_TYPE::CREATE_THIS_DOBJECT;
		}*/

		return dooms::DClass(DOBJECT_TYPE::TYPE_FULL_NAME_HASH_VALUE);
	}
}
