#pragma once
#include <Core.h>

#include <vector>
#include <array>

#include "RootObjectLevel.h"
#include "GarbageCollectorSolver.h"

#define GC_KEEP_FLAGS 0
#define GC_COLLECT_TIME_STEP 10

namespace dooms
{
	class DObject;

	namespace gc
	{
		class DOOM_API D_CLASS GarbageCollectorManager
		{

		private:
			
			static float mElapsedTime;

			// Max Level is long term alive object
			static float mCollectTimeStep;
			static std::vector<DObject*> mRootsDObjectsList;

			static void PoolRootsDObjectsList();
			static void InitializeCollectTimeStep();

			inline static dooms::gc::garbageCollectorSolver::GCStage mNextGCStage{ dooms::gc::garbageCollectorSolver::GCStage::ClearFlagsStage };
			

		public:

			static void Init();
			static void TickGC();

			static void ClearFlags();
			static void Mark();
			static void Sweep();
			static void Collect();
			
			
			/// <summary>
			/// 
			/// </summary>
			/// <param name="dObjet"></param>
			/// <param name="level"></param>
			/// <returns></returns>
			static bool AddToRootsDObjectsList(DObject* const dObjet);
			static bool RemoveFromDObjectsList(DObject* const dObjet);
		};
	}
	
}


