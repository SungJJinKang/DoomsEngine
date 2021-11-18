#pragma once

#include <type_traits>

#include <Macros/DllMarcos.h>
#include "../Reflection.h"


D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	struct DOOM_API D_STRUCT DPrimitive /*: public dooms::DObject*/ // Dont Do this
	{
		const clcpp::Primitive* const clPrimitive;

		FORCE_INLINE DPrimitive(const clcpp::Primitive* const _clPrimitive)
			: clPrimitive(_clPrimitive)
		{
		}

		FORCE_INLINE const char* GetPrimitiveFullName() const
		{
			return clPrimitive->name.text;
		}
		
		FORCE_INLINE const char* GetParentFullName() const
		{
			if(clPrimitive->parent != nullptr)
			{
				return clPrimitive->parent->name.text;
			}
			else
			{
				return nullptr;
			}			
		}
	};
}