#pragma once

#include <type_traits>

#include <Macros/DllMarcos.h>
#include "../Reflection.h"

#include "DPrimitive.h"

D_NAMESPACE(dooms)
namespace dooms
{
	class DObject;
	struct DOOM_API D_STRUCT DType : public DPrimitive /*: public dooms::DObject*/ // Dont Do this
	{
		const clcpp::Type* const clType;

		FORCE_INLINE DType(const clcpp::Type* const _clType)
			: DPrimitive(_clType), clType(_clType)
		{
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