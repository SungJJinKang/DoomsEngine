#pragma once

namespace doom
{
	class Tree
	{
	public:
		using traversal_test_func = bool (*)();
	private:

		virtual void SetFlagsOfDescents(unsigned int ancesterNodeIndex, unsigned int bitflags);


	public:

		virtual void TraverseForSettingBitflag(traversal_test_func* testFunction);
		
	};
}