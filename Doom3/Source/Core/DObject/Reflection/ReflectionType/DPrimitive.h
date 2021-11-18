#pragma once

#include <Macros/DllMarcos.h>
#include <Macros/Assert.h>

#include "../Reflection.h"

namespace dPrimitiveHelper
{
	// return short name
	// ex) dooms::graphics::GraphicsServer -> GraphicsServer
	// ex) dooms::graphics::eClor::Red -> Red
	const char* GetShortNamePointer(const char* const name);
}


D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	class DOOM_API D_STRUCT DPrimitive /*: public dooms::DObject*/ // Dont Do this
	{
	protected:

		const clcpp::Primitive* clPrimitive;

	public:

		FORCE_INLINE DPrimitive()
			:clPrimitive(nullptr)
		{
			
		}
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

		bool IsValid() const
		{
			return clPrimitive != nullptr;
		}
	};
}