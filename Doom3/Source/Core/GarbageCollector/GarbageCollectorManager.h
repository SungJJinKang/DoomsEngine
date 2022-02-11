#pragma once
#include <Core.h>

#include <vector>
#include <memory>

#include "GarbageCollectorSolver.h"

#define GC_KEEP_FLAGS 0
#define GC_COLLECT_TIME_STEP 10

namespace dooms
{
	class DObject;

	namespace gc
	{
		struct RootObjectContainer
		{
			std::vector<DObject*> mRootsDObjectsList;
		};

		class DOOM_API D_CLASS GarbageCollectorManager
		{

		private:

			static garbageCollectorSolver::eGCMethod _GCMethod;

			static unsigned int mMaxSweepedObjectCountAtATime;

			static float mElapsedTime;

			// Max Level is long term alive object
			static float mCollectTimeStep;
			static std::unique_ptr<RootObjectContainer> _RootObjectContainer;

			static void InitializeCollectTimeStep();

			inline static dooms::gc::garbageCollectorSolver::eGCStage mNextGCStage{ dooms::gc::garbageCollectorSolver::eGCStage::ClearFlagsStage };
			
			static void ClearFlags(const garbageCollectorSolver::eGCMethod gcMethod = garbageCollectorSolver::eGCMethod::MultiThreadMark);
			static void Mark(const garbageCollectorSolver::eGCMethod gcMethod = garbageCollectorSolver::eGCMethod::MultiThreadMark);
			static void Sweep(const garbageCollectorSolver::eGCMethod gcMethod = garbageCollectorSolver::eGCMethod::MultiThreadMark);

		public:

			static void Init();
			static void TickGC();
			static void ResetElapsedTime();

			static void Collect(const garbageCollectorSolver::eGCMethod gcMethod = garbageCollectorSolver::eGCMethod::MultiThreadMark, const bool initialGC = false);
			static void Collect(const bool initialGC = false);
			
			
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


