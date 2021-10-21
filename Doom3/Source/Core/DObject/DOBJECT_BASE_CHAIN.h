#pragma once

#include <vector>

#include "Macros/TypeDef.h"

#define MAX_DOBJECT_BASE_CHAIN_DEPTH 15

namespace doom
{
	struct DOBJECT_BASE_CHAIN
	{
		SIZE_T BASE_CHAIN_COUNT = 0;
		
		const char* BASE_CHAIN_TYPE_ID_LIST[MAX_DOBJECT_BASE_CHAIN_DEPTH];

		//TODO : Make This Resolved at Compile Time!!!
		DOBJECT_BASE_CHAIN() : BASE_CHAIN_COUNT(0)
		{}

		FORCE_INLINE void Increment_BASE_CHAIN_COUNT()
		{
			BASE_CHAIN_COUNT++;
			D_ASSERT_LOG(BASE_CHAIN_COUNT < MAX_DOBJECT_BASE_CHAIN_DEPTH, "BaseChain Depth is over MAX_DOBJECT_BASE_CHAIN_DEPTH, Plase set higher value to MAX_DOBJECT_BASE_CHAIN_DEPTH");
		}
	};
}
