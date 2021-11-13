#pragma once

#include <type_traits>

#include "Macros/TypeDef.h"
#include <Macros/DllMarcos.h>
#include "../Reflection.h"

namespace dooms
{
	struct DOOM_API D_STRUCT DProperty /*: public dooms::DObject*/ // Dont Do this
	{
		// TODO : Implement this ( 2021/11/14 )
		D_PROPERTY()
		const char* const PROPERTY_NAME;

		D_PROPERTY()
		const char* const PROPERTY_TYPE_NAME;

		D_PROPERTY()
		const size_t PROPERTY_TYPE_SIZE;

		
		constexpr DProperty()
		{
			
		}
	};
}
