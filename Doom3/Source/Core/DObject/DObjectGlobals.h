#pragma once

#include <type_traits>

#include "DObject.h"
#include "DObjectManager.h"

namespace doom
{
	template <typename DObjectType, typename... Args>
	DObjectType* CreateDObject(const DObjectContructorParams& dObjectConstructorParams, Args... args)
	{
		static_assert(std::is_base_of_v<doom::DObject, DObjectType> == true);

		//DObjectType's Constructor should be public function
		DObjectType* const newDObject = new DObjectType(std::forward<Args>(args)...);

		DObjectContructorParams params(dObjectConstructorParams);
		params.DObjectFlag |= doom::eDObjectFlag::NewAllocated;

		static_cast<DObject*>(newDObject)->InitProperties(params);

		return newDObject;
	}

	template <typename DObjectType, typename... Args>
	DObjectType* CreateDObject(Args... args)
	{
		static_assert(std::is_base_of_v<doom::DObject, DObjectType> == true);

		//DObjectType's Constructor should be public function
		DObjectType* const newDObject = new DObjectType(std::forward<Args>(args)...);

		DObjectContructorParams params{};
		params.DObjectFlag |= doom::eDObjectFlag::NewAllocated;

		static_cast<DObject*>(newDObject)->InitProperties(params);

		return newDObject;
	}

	inline bool IsValid(const DObject* const dObject)
	{
		return doom::DObjectManager::IsDObjectValid(dObject);
	}
}
