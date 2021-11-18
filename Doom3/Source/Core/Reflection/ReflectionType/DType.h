#pragma once

#include <Macros/Assert.h>
#include <Macros/DllMarcos.h>

#include "../Reflection.h"


#include "DPrimitive.h"


D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	namespace reflection
	{
		class DOOM_API D_STRUCT DType : public DPrimitive /*: public dooms::DObject*/ // Dont Do this
		{
		protected:

			const clcpp::Type * clType;

		public:

			FORCE_INLINE DType(const clcpp::Type* const _clType)
				: DPrimitive(_clType), clType(_clType)
			{
				//D_ASSERT(clType != nullptr);
			}

			FORCE_INLINE const char* GetTypeFullName() const
			{
				return DPrimitive::GetPrimitiveFullName();
			}

			FORCE_INLINE size_t GetTypeSize() const
			{
				return clType->size;
			}

		};
	}
}