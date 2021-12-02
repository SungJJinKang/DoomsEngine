#pragma once

#include <vector>

#include "TypeDef.h"

namespace dooms
{
	class DObject;
	namespace gc
	{
		namespace garbageCollectorSolver
		{

			void SolveGC(const UINT32 keepFlags, std::vector<DObject*>& rootObjectList);

		}
	}
};

