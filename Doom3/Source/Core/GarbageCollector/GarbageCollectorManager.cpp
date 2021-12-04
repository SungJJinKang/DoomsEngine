#include "GarbageCollectorManager.h"

#include <Time/MainTimer.h>
#include <Game/ConfigData.h>

#include "GarbageCollectorSolver.h"
#include <vector_erase_move_lastelement/vector_swap_popback.h>

float dooms::gc::GarbageCollectorManager::mElapsedTime{};
float dooms::gc::GarbageCollectorManager::mCollectTimeStep{};
std::vector<dooms::DObject*> dooms::gc::GarbageCollectorManager::mRootsDObjectsList{};


void dooms::gc::GarbageCollectorManager::PoolRootsDObjectsList()
{
	mRootsDObjectsList.reserve(300);
}

void dooms::gc::GarbageCollectorManager::InitializeCollectTimeStep()
{
	//mCollectTimeStep[ = dooms::ConfigData::GetSingleton()->GetConfigData().GetValue<float>()

	mCollectTimeStep = 10.0f;
	mElapsedTime = 0.0f;
}

/*
void dooms::gc::GarbageCollectorManager::Collect()
{
	dooms::gc::garbageCollectorSolver::StartMarkStage(0, mRootsDObjectsList);
}

void dooms::gc::GarbageCollectorManager::SetUnreachableFlagsToAllDObject()
{
	dooms::gc::garbageCollectorSolver::StartSetUnreachableFlagStage(dooms::DObjectManager::mDObjectsContainer.mDObjectFlagList);
	
}
*/

void dooms::gc::GarbageCollectorManager::Init()
{
	PoolRootsDObjectsList();
	InitializeCollectTimeStep();

	mNextGCStage = dooms::gc::garbageCollectorSolver::GCStage::ClearFlagsStage;
	
}

void dooms::gc::GarbageCollectorManager::TickGC()
{
	mElapsedTime += dooms::time::MainTimer::GetSingleton()->GetDeltaTime();

	if(mElapsedTime > mCollectTimeStep)
	{
		Collect();

		/*if (mNextGCStage == dooms::gc::garbageCollectorSolver::GCStage::ClearFlagsStage)
		{
			

			mNextGCStage = garbageCollectorSolver::GCStage::MarkSweepStage;
		}
		else if (mNextGCStage == dooms::gc::garbageCollectorSolver::GCStage::MarkSweepStage)
		{
			Collect();

			mNextGCStage = garbageCollectorSolver::GCStage::ClearFlagsStage;
			//mNextGCStage = garbageCollectorSolver::GCStage::SweepStage;
		}
		/*else if (mNextGCStage == dooms::gc::garbageCollectorSolver::GCStage::SweepStage)
		{
			

			mNextGCStage = garbageCollectorSolver::GCStage::ClearFlagsStage;
		}#1#
		else
		{
			D_ASSERT(false);
		}*/

		mElapsedTime = 0.0f;
	}
	
}

void dooms::gc::GarbageCollectorManager::ClearFlags()
{
	D_START_PROFILING(GC_ClearFlagsStage, CPU);

	D_DEBUG_LOG(eLogType::D_LOG_TYPE12, "Execute GC_ClearFlagsStage");
	std::unique_lock<std::recursive_mutex> lock{ dooms::DObjectManager::DObjectListMutex };
	dooms::gc::garbageCollectorSolver::StartSetUnreachableFlagStage(dooms::DObjectManager::mDObjectsContainer.mDObjectFlagList);
	lock.unlock();

	D_END_PROFILING(GC_ClearFlagsStage);
}

void dooms::gc::GarbageCollectorManager::Mark()
{
	ClearFlags();

	D_START_PROFILING(GC_MarkStage, CPU);

	D_DEBUG_LOG(eLogType::D_LOG_TYPE12, "Execute GC_MarkStage");
	dooms::gc::garbageCollectorSolver::StartMarkStage(GC_KEEP_FLAGS, mRootsDObjectsList);

	D_END_PROFILING(GC_MarkStage);
}

void dooms::gc::GarbageCollectorManager::Sweep()
{
	D_START_PROFILING(GC_SweepStage, CPU);

	D_DEBUG_LOG(eLogType::D_LOG_TYPE12, "Execute GC_SweepStage");
	dooms::gc::garbageCollectorSolver::StartSweepStage(GC_KEEP_FLAGS, dooms::DObjectManager::mDObjectsContainer.mDObjectList);

	D_END_PROFILING(GC_SweepStage);
}

void dooms::gc::GarbageCollectorManager::Collect()
{
	D_DEBUG_LOG(eLogType::D_LOG_TYPE12, "Start GC");
	Mark();
	Sweep();
}


bool dooms::gc::GarbageCollectorManager::AddToRootsDObjectsList(DObject* const dObjet)
{
	D_ASSERT(IsStrongValid(dObjet) == true);
	dObjet->SetDObjectFlag(eDObjectFlag::IsRootObject);
	mRootsDObjectsList.push_back(dObjet);

	return true;
}

bool dooms::gc::GarbageCollectorManager::RemoveFromDObjectsList(DObject* const dObjet)
{
	const bool isSuccess = swap_popback::vector_find_swap_popback(mRootsDObjectsList, dObjet);
	
	return isSuccess;
}
