#pragma once

#include <vector>
#include <unordered_set>

#include "TypeDef.h"

#define DELETE_DOBJECT_LIST_RESERVATION_COUNT 20


namespace dooms
{
	class DObject;
	namespace gc
	{
		namespace garbageCollectorSolver
		{
			enum class eGCMethod : UINT32
			{
				SingleThreadMark,
				MultiThreadMark,
			};

			enum eGCStage : UINT32
			{
				ClearFlagsStage = 0, // StartSetUnreachableFlagStage to all DObjects
				MarkSweepStage,
				SweepStage
			};

			void StartSetUnreachableFlagStage(const eGCMethod gcMethod, std::vector<UINT32>& flags);

			void StartMarkStage(const eGCMethod gcMethod, const UINT32 keepFlags, std::vector<dooms::DObject*>& rootDObjectList);
			
			void StartSweepStage(const eGCMethod gcMethod, const UINT32 keepFlags, std::unordered_set<dooms::DObject*>& dObjectList);

			// this may make bugs ( multithread delete can make a lot of bugs )
			//void StartParallelSweepStage(std::vector<dooms::DObject*>& dObjectList, const std::vector<UINT32>& flagList);

		}
	}
};

