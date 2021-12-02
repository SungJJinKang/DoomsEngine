#include "GarbageCollectorManager.h"

#include <Time/MainTimer.h>
#include <Game/ConfigData.h>

#include "GarbageCollectorSolver.h"
#include <vector_erase_move_lastelement/vector_swap_popback.h>

std::array<float, dooms::ROOT_OBJECT_HIERARCHY_MAX_LEVEL> dooms::gc::GarbageCollectorManager::mElapsedTime{};
std::array<float, dooms::ROOT_OBJECT_HIERARCHY_MAX_LEVEL> dooms::gc::GarbageCollectorManager::mCollectTimeStep{};
std::array<std::vector<dooms::DObject*>, dooms::ROOT_OBJECT_HIERARCHY_MAX_LEVEL> dooms::gc::GarbageCollectorManager::mRootsDObjectsList{};


void dooms::gc::GarbageCollectorManager::PoolRootsDObjectsList()
{
	mRootsDObjectsList[0].reserve(1000);
	mRootsDObjectsList[1].reserve(300);
	mRootsDObjectsList[2].reserve(100);
}

void dooms::gc::GarbageCollectorManager::InitializeCollectTimeStep()
{
	//mCollectTimeStep[0] = dooms::ConfigData::GetSingleton()->GetConfigData().GetValue<float>()

	mCollectTimeStep[0] = 3.0f;
	mCollectTimeStep[1] = 15.0f;
	mCollectTimeStep[2] = 30.0f;

	for(auto& elapsedTime : mElapsedTime)
	{
		elapsedTime = 0.0f;
	}
}

void dooms::gc::GarbageCollectorManager::Collect()
{
	for (int level = dooms::ROOT_OBJECT_HIERARCHY_MAX_LEVEL ; level >= 0 ; level--)
	{
		Collect(mRootsDObjectsList[level]);
	}
}

void dooms::gc::GarbageCollectorManager::Collect(const UINT32 level)
{
	Collect(mRootsDObjectsList[level]);
}

void dooms::gc::GarbageCollectorManager::Collect(std::vector<DObject*>& rootObjectList)
{
	dooms::gc::garbageCollectorSolver::SolveGC(rootObjectList);
}

void dooms::gc::GarbageCollectorManager::Init()
{
	PoolRootsDObjectsList();
	InitializeCollectTimeStep();
	
}

void dooms::gc::GarbageCollectorManager::TickGC()
{
	for (int level = 0 ; level < dooms::ROOT_OBJECT_HIERARCHY_MAX_LEVEL; level++)
	{
		mElapsedTime[level] += dooms::time::MainTimer::GetSingleton()->GetDeltaTime();
		if(mElapsedTime[level] >= mCollectTimeStep[level])
		{
			Collect(mRootsDObjectsList[level]);
			mElapsedTime[level] = 0.0f;
		}
	}
}



bool dooms::gc::GarbageCollectorManager::AddToRootsDObjectsList(DObject* const dObjet, const UINT32 initialLevel)
{
	D_ASSERT(initialLevel < dooms::ROOT_OBJECT_HIERARCHY_MAX_LEVEL);

	bool isSuccess = false;

	if(initialLevel < dooms::ROOT_OBJECT_HIERARCHY_MAX_LEVEL)
	{
		mRootsDObjectsList[initialLevel].push_back(dObjet);
		isSuccess = true;
	}

	return isSuccess;
}

bool dooms::gc::GarbageCollectorManager::RemoveFromDObjectsList(DObject* const dObjet)
{
	bool isSuccess = false;
	for(int level = dooms::ROOT_OBJECT_HIERARCHY_MAX_LEVEL; level >= 0 ; level--)
	{
		isSuccess = swap_popback::vector_find_swap_popback(mRootsDObjectsList[level], dObjet);

		if(isSuccess == true)
		{
			break;
		}
	}

	return isSuccess;
}
