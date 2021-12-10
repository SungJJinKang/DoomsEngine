#pragma once
#include <Core.h>

#include <vector>
#include <array>

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

			static garbageCollectorSolver::eGCMethod _GCMethod;

			static float mElapsedTime;

			// Max Level is long term alive object
			static float mCollectTimeStep;
			static std::vector<DObject*> mRootsDObjectsList;
			
			static void InitializeCollectTimeStep();

			inline static dooms::gc::garbageCollectorSolver::eGCStage mNextGCStage{ dooms::gc::garbageCollectorSolver::eGCStage::ClearFlagsStage };
			

		public:

			static void Init();
			static void TickGC();
			static void ResetElapsedTime();

			static void ClearFlags(const garbageCollectorSolver::eGCMethod gcMethod = garbageCollectorSolver::eGCMethod::MultiThreadMark);
			static void Mark(const garbageCollectorSolver::eGCMethod gcMethod = garbageCollectorSolver::eGCMethod::MultiThreadMark);
			static void Sweep(const garbageCollectorSolver::eGCMethod gcMethod = garbageCollectorSolver::eGCMethod::MultiThreadMark);
			static void Collect(const garbageCollectorSolver::eGCMethod gcMethod = garbageCollectorSolver::eGCMethod::MultiThreadMark);
			
			
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


