#pragma once

#include <Macros/DllMarcos.h>
#include <Macros/Assert.h>

#include "../Reflection.h"


D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	class DOOM_API D_STRUCT DPrimitive /*: public dooms::DObject*/ // Dont Do this
	{
	protected:

		const clcpp::Primitive* clPrimitive;

	public:

		FORCE_INLINE DPrimitive(const clcpp::Primitive* const _clPrimitive)
			: clPrimitive(_clPrimitive)
		{
			//D_ASSERT(clPrimitive != nullptr);
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