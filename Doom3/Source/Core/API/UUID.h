#pragma once

#include "../../dependency/uuid/sole/sole.hpp"

namespace Doom
{
	using D_UUID = sole::uuid;
	inline D_UUID GenerateUUID()
	{
		return sole::uuid0();
	}
}