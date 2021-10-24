#pragma once

#include <type_traits>

#include "Macros/TypeDef.h"

namespace doom
{
	struct DProperty /*: public doom::DObject*/ // Dont Do this
	{
		const char* const PROPERTY_NAME;
		const char* const PROPERTY_TYPE_NAME;
		const SIZE_T PROPERTY_TYPE_SIZE;


		//¿¬±¸Áß : https://godbolt.org/z/57sqe6h4P  ,  https://youtu.be/abdeAew3gmQ
		constexpr DProperty()
		{
			
		}
	};
}
