#pragma once
#include <type_traits>
#include <cstring>

#include <Macros/DllMarcos.h>
#include "../Reflection.h"

#include "DType.h"

D_NAMESPACE(dooms)
namespace dooms
{
	namespace dEnumHelper
	{
		// return short name
		// ex) dooms::graphics::GraphicsServer -> GraphicsServer
		// ex) dooms::graphics::eClor::Red -> Red
		const char* GetShortNamePointer(const char* const name);
	}

	class DObject;
	struct DOOM_API D_STRUCT DEnum : public DType /*: public dooms::DObject*/ // Dont Do this
	{
		const clcpp::Enum* const clEnum;

		DEnum(const UINT32 nameHash);

		FORCE_INLINE const char* GetValueName(const INT32 value)
		{
			return clEnum->GetValueName(value);
		}

		// if value is found, return true
		const bool GetValue(const char* const valueName, INT32& result);
	};
}