#pragma once

#include <vector>

namespace dooms
{
	class DObject;
	namespace gc
	{
		namespace garbageCollectorSolver
		{

			void SolveGC(std::vector<DObject*>& rootObjectList);

		}
	}
};

