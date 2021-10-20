#pragma once

#include <type_traits>

namespace doom
{
	class DObject;
	struct DClass /*: public doom::DObject*/ // Dont Do this
	{

		/*
		DOBJECT_CLASS_BODY(DClass) // Dont Do this
		DOBJECT_CLASS_BASE_CHAIN(DObject) // Dont Do this
		*/


	};

	template <typename DOBJECT_TYPE>
	extern DClass CreateDClass()
	{
		static_assert(std::is_base_of_v<doom::DObject, DOBJECT_TYPE> == true);

	}
}