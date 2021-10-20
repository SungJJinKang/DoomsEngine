#pragma once

#include <vector>

#include "Macros/TypeDef.h"

namespace doom
{
	struct DOBJECT_BASE_CHAIN
	{
		SIZE_T BASE_CHAIN_COUNT;
		std::vector<SIZE_T> BASE_CHAIN_TYPE_ID_LIST;

		DOBJECT_BASE_CHAIN() : BASE_CHAIN_COUNT(0), BASE_CHAIN_TYPE_ID_LIST()
		{}
	};
}
