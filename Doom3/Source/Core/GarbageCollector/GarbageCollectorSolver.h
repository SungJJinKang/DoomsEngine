#pragma once

#include <vector>
#include <unordered_set>

#include "TypeDef.h"


// TODO : More optimization. references : http://gchandbook.org/, https://www.cs.kent.ac.uk/people/staff/rej/gcbib/, https://www.cs.kent.ac.uk/people/staff/rej/gcbook/      

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

			void StartSetUnreachableFlagStage(const eGCMethod gcMethod, std::unordered_set<DObject*>& dObjects);

			void StartMarkStage(const eGCMethod gcMethod, const UINT32 keepFlags, std::vector<dooms::DObject*>& rootDObjectList);

			/**
			 * \brief 
			 * \param gcMethod 
			 * \param keepFlags 
			 * \param dObjectList 
			 * \param maxSweepedObjectCount Maximum destroyed object count. Limit destroyed object at a time. This is for preventing performance drop from destroying a lot of objects
			 */
			void StartSweepStage(const eGCMethod gcMethod, const UINT32 keepFlags, std::unordered_set<dooms::DObject*>& dObjectList, const size_t maxSweepedObjectCount);

			// this may make bugs ( multithread delete can make a lot of bugs )
			//void StartParallelSweepStage(std::vector<dooms::DObject*>& dObjectList, const std::vector<UINT32>& flagList);

		}
	}
};

