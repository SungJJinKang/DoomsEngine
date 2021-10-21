#pragma once

#include <vector>

#include "Macros/TypeDef.h"

//BASE_CHAIN_COUNT�� �ƹ��� ������ Ÿ�ӿ� �����Ǿ MAX_DOBJECT_BASE_CHAIN_DEPTH ���� �ʿ��� ��
// DOBJECT_BASE_CHAIN�� ���ø��� �ٿ��� BASE_CHAIN_TYPE_ID_LIST ����� Ŭ���� Ÿ�Ը��� ���������� ������� �ڵ� �ʹ� ����������.
// �׳� BASE_CHAIN_TYPE_ID_LIST�� array ���̴� ���� ���Ƿ� ��������. 
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
