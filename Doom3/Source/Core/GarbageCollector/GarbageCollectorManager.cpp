#include "GarbageCollectorManager.h"

#include <Time/MainTimer.h>
#include <EngineConfigurationData/ConfigData.h>

#include "GarbageCollectorSolver.h"
#include <vector_erase_move_lastelement/vector_swap_popback.h>

dooms::gc::garbageCollectorSolver::eGCMethod dooms::gc::GarbageCollectorManager::_GCMethod{ dooms::gc::garbageCollectorSolver::eGCMethod ::MultiThreadMark};
float dooms::gc::GarbageCollectorManager::mElapsedTime{};
unsigned int dooms::gc::GarbageCollectorManager::mMaxSweepedObjectCountAtATime{};
float dooms::gc::GarbageCollectorManager::mCollectTimeStep{};
std::unique_ptr<dooms::gc::RootObjectContainer> dooms::gc::GarbageCollectorManager::_RootObjectContainer{};


void dooms::gc::GarbageCollectorManager::InitializeCollectTimeStep()
{
	//mCollectTimeStep[ = dooms::ConfigData::GetSingleton()->GetConfigData().GetValue<float>()

	mCollectTimeStep = dooms::ConfigData::GetSingleton()->GetConfigData().GetValue<FLOAT64>("SYSTEM", "GC_TIME_STEP");
	mMaxSweepedObjectCountAtATime = dooms::ConfigData::GetSingleton()->GetConfigData().GetValue<INT64>("SYSTEM", "GC_MAX_SWEEPED_OBJECT_COUNT_AT_A_TIME");
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
	InitializeCollectTimeStep();

	if (dooms::ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("SYSTEM", "GC_MULTITHREAD_ENABLED"))
	{
		_GCMethod = garbageCollectorSolver::eGCMethod::MultiThreadMark;
	}
	else
	{
		_GCMethod = garbageCollectorSolver::eGCMethod::SingleThreadMark;
	}


	mNextGCStage = dooms::gc::garbageCollectorSolver::eGCStage::ClearFlagsStage;
	
}

void dooms::gc::GarbageCollectorManager::TickGC()
{
	mElapsedTime += dooms::time::MainTimer::GetSingleton()->GetDeltaTime();

	if(mElapsedTime > mCollectTimeStep)
	{
		Collect(_GCMethod);

		/*if (mNextGCStage == dooms::gc::garbageCollectorSolver::eGCStage::ClearFlagsStage)
		{
			

			mNextGCStage = garbageCollectorSolver::eGCStage::MarkSweepStage;
		}
		else if (mNextGCStage == dooms::gc::garbageCollectorSolver::eGCStage::MarkSweepStage)
		{
			Collect();

			mNextGCStage = garbageCollectorSolver::eGCStage::ClearFlagsStage;
			//mNextGCStage = garbageCollectorSolver::eGCStage::SweepStage;
		}
		/*else if (mNextGCStage == dooms::gc::garbageCollectorSolver::eGCStage::SweepStage)
		{
			

			mNextGCStage = garbageCollectorSolver::eGCStage::ClearFlagsStage;
		}#1#
		else
		{
			D_ASSERT(false);
		}*/

		mElapsedTime = 0.0f;
	}
	
}

void dooms::gc::GarbageCollectorManager::ResetElapsedTime()
{
	mElapsedTime = 0.0f;
}

void dooms::gc::GarbageCollectorManager::ClearFlags(const garbageCollectorSolver::eGCMethod gcMethod)
{
	D_START_PROFILING(GC_ClearFlagsStage, CPU);

	D_DEBUG_LOG(eLogType::D_LOG_TYPE12, "Execute GC_ClearFlagsStage");
	//std::scoped_lock<std::recursive_mutex> lock{ dooms::DObjectManager::DObjectListMutex };

	dooms::gc::garbageCollectorSolver::StartSetUnreachableFlagStage(gcMethod, dooms::DObjectManager::GetDObjectList());

	D_END_PROFILING(GC_ClearFlagsStage);
}

void dooms::gc::GarbageCollectorManager::Mark(const garbageCollectorSolver::eGCMethod gcMethod)
{
	D_START_PROFILING(GC_MarkStage, CPU);

	D_DEBUG_LOG(eLogType::D_LOG_TYPE12, "Execute GC_MarkStage");
	dooms::gc::garbageCollectorSolver::StartMarkStage(gcMethod, GC_KEEP_FLAGS,  _RootObjectContainer->mRootsDObjectsList);

	D_END_PROFILING(GC_MarkStage);
}

void dooms::gc::GarbageCollectorManager::Sweep(const garbageCollectorSolver::eGCMethod gcMethod)
{
	D_START_PROFILING(GC_SweepStage, CPU);

	D_DEBUG_LOG(eLogType::D_LOG_TYPE12, "Execute GC_SweepStage");
	dooms::gc::garbageCollectorSolver::StartSweepStage(gcMethod, GC_KEEP_FLAGS, dooms::DObjectManager::mDObjectsContainer.mDObjectList, mMaxSweepedObjectCountAtATime);

	D_END_PROFILING(GC_SweepStage);
}

void dooms::gc::GarbageCollectorManager::Collect(const garbageCollectorSolver::eGCMethod gcMethod, const bool initialGC)
{
	D_START_PROFILING(GC_Collect, CPU);


	D_DEBUG_LOG(eLogType::D_LOG_TYPE12, "Start GC");
	if(initialGC == true)
	{
		ClearFlags(gcMethod);
	}
	
	Mark(gcMethod);
	Sweep(gcMethod);


	D_END_PROFILING(GC_Collect);
}

void dooms::gc::GarbageCollectorManager::Collect(const bool initialGC)
{
	Collect(_GCMethod, initialGC);
}


bool dooms::gc::GarbageCollectorManager::AddToRootsDObjectsList(DObject* const dObjet)
{
	bool isSuccess = false;

	D_ASSERT(IsDObjectValidLowLevel(dObjet, true) == true);
	dObjet->SetDObjectFlag(eDObjectFlag::IsRootObject);

	if(static_cast<bool>(_RootObjectContainer) == false)
	{
		_RootObjectContainer = std::make_unique<dooms::gc::RootObjectContainer>();
	}

	D_ASSERT(fast_find_simd::find_simd_raw(_RootObjectContainer->mRootsDObjectsList.data(), _RootObjectContainer->mRootsDObjectsList.data() + _RootObjectContainer->mRootsDObjectsList.size(), dObjet) == _RootObjectContainer->mRootsDObjectsList.data() + _RootObjectContainer->mRootsDObjectsList.size());
	_RootObjectContainer->mRootsDObjectsList.push_back(dObjet);
	isSuccess = true;

	return isSuccess;
}

bool dooms::gc::GarbageCollectorManager::RemoveFromDObjectsList(DObject* const dObjet)
{
	bool isSuccess = false;

	if (static_cast<bool>(_RootObjectContainer) == false)
	{
		_RootObjectContainer = std::make_unique<dooms::gc::RootObjectContainer>();
	}

	if(_RootObjectContainer->mRootsDObjectsList.empty() == false)
	{
		isSuccess = swap_popback::vector_find_swap_popback(_RootObjectContainer->mRootsDObjectsList, dObjet);
	}
	
	return isSuccess;
}
