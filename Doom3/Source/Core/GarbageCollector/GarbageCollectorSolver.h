#pragma once

#include <vector>

#include "TypeDef.h"

#define DELETE_DOBJECT_LIST_RESERVATION_COUNT 20


namespace dooms
{
	class DObject;
	namespace gc
	{
		namespace garbageCollectorSolver
		{
			enum GCStage : UINT32
			{
				ClearFlagsStage = 0, // StartSetUnreachableFlagStage to all DObjects
				MarkStage,
				SweepStage
			};

			void StartSetUnreachableFlagStage(std::vector<UINT32>& flags);

			void StartMarkStage(const UINT32 keepFlags, std::vector<dooms::DObject*>& rootDObjectList);
			
			void StartSweepStage(std::vector<dooms::DObject*>& dObjectList, std::vector<UINT32>& flagList);

			// this may make bugs ( multithread delete can make a lot of bugs )
			//void StartParallelSweepStage(std::vector<dooms::DObject*>& dObjectList, const std::vector<UINT32>& flagList);

		}
	}
};

