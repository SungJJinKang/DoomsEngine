#pragma once

#include <type_traits>

namespace doom
{


	template <typename DObjectType, typename... Args>
	DObjectType* CreateDObject(Args... args)
	{
		static_assert(std::is_base_of_v<doom::DObject, DObjectType> == true);

		//DObjectType's Constructor should be public function
		DObjectType* const newDObject = new DObjectType(std::forward<Args>(args)...);

		DObjectContructorParams params;
		params.DObjectFlag |= doom::eDObjectFlag::NewAllocated;

		InitDObjectPropertiesGlobal(static_cast<DObject*>(newDObject), params);

		return newDObject;
	}
}
