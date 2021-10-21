#pragma once

#include <vector>

#include "Macros/TypeDef.h"

//BASE_CHAIN_COUNT가 아무리 컴파일 타임에 결정되어도 MAX_DOBJECT_BASE_CHAIN_DEPTH 값은 필요할 듯
// DOBJECT_BASE_CHAIN에 템플릿을 붙여서 BASE_CHAIN_TYPE_ID_LIST 사이즈를 클래스 타입마다 유동적으로 만들려면 코드 너무 더러워진다.
// 그냥 BASE_CHAIN_TYPE_ID_LIST의 array 길이는 내가 임의로 지정하자. 
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
