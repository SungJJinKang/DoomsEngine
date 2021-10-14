#pragma once

namespace doom
{
	class Tree
	{
	public:
		using traversal_test_func = bool (*)();
	private:

		virtual void SetFlagsOfDescents(UINT32 ancesterNodeIndex, UINT32 bitflags);


	public:

		virtual void TraverseForSettingBitflag(traversal_test_func* testFunction);
		
	};
}