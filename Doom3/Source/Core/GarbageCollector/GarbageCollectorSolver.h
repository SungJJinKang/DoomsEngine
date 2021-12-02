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
			enum GCStage : UINT32
			{
				ClearFlagsStage, // SetUnreachableFlag to all DObjects
				MarkStage,
				SweepStage
			};

			void SetUnreachableFlag(std::vector<UINT32>& flags);

			void Mark(const UINT32 keepFlags, std::vector<dooms::DObject*>& rootDObjectList);
			void Mark(const UINT32 keepFlags, dooms::DObject* const rootObject);

			void Sweep(std::vector<dooms::DObject*>& dObjectList);

		}
	}
};

