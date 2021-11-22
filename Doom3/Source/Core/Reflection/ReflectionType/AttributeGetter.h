#pragma once

#include <Macros/DllMarcos.h>
#include "../Reflection.h"

#include <vector>
#include <unordered_map>

D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	namespace reflection
	{
		class DOOM_API D_CLASS AttributeGetter /*: public dooms::DObject*/ // Dont Do this
		{
			// Cache Attribute List through static variable.
			// Field can have attribute , Type can have attribute
			// Field can have same name even it is declared in diffent class. So consider it.
		}
	}
}
