#pragma once

#include "../../dependency/uuid/sole/sole.hpp"

namespace Doom
{
	using UUID = sole::uuid;
	inline UUID GenerateUUID()
	{
		return sole::uuid0();
	}
}