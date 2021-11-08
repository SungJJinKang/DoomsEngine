#pragma once

#include <type_traits>

#include "Macros/TypeDef.h"

namespace dooms
{
	struct DOOM_API D_STRUCT DProperty /*: public dooms::DObject*/ // Dont Do this
	{
		D_PROPERTY()
		const char* const PROPERTY_NAME;

		D_PROPERTY()
		const char* const PROPERTY_TYPE_NAME;

		D_PROPERTY()
		const size_t PROPERTY_TYPE_SIZE;


		//������ : https://godbolt.org/z/57sqe6h4P  ,  https://youtu.be/abdeAew3gmQ
		constexpr DProperty()
		{
			
		}
	};
}
