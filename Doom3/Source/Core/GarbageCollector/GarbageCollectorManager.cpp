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
	dooms::gc::garbageCollectorSolver::Mark(0, mRootsDObjectsList);
}

void dooms::gc::GarbageCollectorManager::SetUnreachableFlagsToAllDObject()
{
	dooms::gc::garbageCollectorSolver::SetUnreachableFlag(dooms::DObjectManager::mDObjectsContainer.mDObjectFlagList);
	
}
*/

void dooms::gc::GarbageCollectorManager::Init()
{
	PoolRootsDObjectsList();
	InitializeCollectTimeStep();

	mNextGCStage = dooms::gc::garbageCollectorSolver::GCStage::SweepStage;
	
}

void dooms::gc::GarbageCollectorManager::TickGC()
{
	mElapsedTime += dooms::time::MainTimer::GetSingleton()->GetDeltaTime();

	if(mNextGCStage == dooms::gc::garbageCollectorSolver::GCStage::ClearFlagsStage)
	{
		D_START_PROFILING(GC_ClearFlagsStage);

		std::unique_lock<std::recursive_mutex> lock{ dooms::DObjectManager::DObjectListMutex };
		dooms::gc::garbageCollectorSolver::SetUnreachableFlag(dooms::DObjectManager::mDObjectsContainer.mDObjectFlagList);
		lock.unlock();

		D_END_PROFILING(GC_ClearFlagsStage);

		mNextGCStage = garbageCollectorSolver::GCStage::MarkStage;
	}
	else if (mNextGCStage == dooms::gc::garbageCollectorSolver::GCStage::MarkStage)
	{
		D_START_PROFILING(GC_MarkStage);
		
		D_END_PROFILING(GC_MarkStage);
	}
	else if (mNextGCStage == dooms::gc::garbageCollectorSolver::GCStage::SweepStage)
	{
		D_START_PROFILING(GC_SweepStage);

		D_END_PROFILING(GC_SweepStage);
	}
	else
	{
		D_ASSERT(false);
	}
}



bool dooms::gc::GarbageCollectorManager::AddToRootsDObjectsList(DObject* const dObjet)
{
	mRootsDObjectsList.push_back(dObjet);

	return true;
}

bool dooms::gc::GarbageCollectorManager::RemoveFromDObjectsList(DObject* const dObjet)
{
	const bool isSuccess = swap_popback::vector_find_swap_popback(mRootsDObjectsList, dObjet);
	
	return isSuccess;
}
