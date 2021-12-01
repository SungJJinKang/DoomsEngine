#include "GarbageCollectorManager.h"

#include "GarbageCollectorSolver.h"
#include <vector_erase_move_lastelement/vector_swap_popback.h>

dooms::gc::GarbageCollectorManager::GarbageCollectorManager()
	: mRootsDObjectsList()
{
}

void dooms::gc::GarbageCollectorManager::Init()
{
}

void dooms::gc::GarbageCollectorManager::Update()
{

}

void dooms::gc::GarbageCollectorManager::OnEndOfFrame()
{
}

bool dooms::gc::GarbageCollectorManager::AddToRootsDObjectsList(DObject* const dObjet, const int initialLevel)
{
	return true;
}

bool dooms::gc::GarbageCollectorManager::RemoveFromDObjectsList(DObject* const dObjet)
{
	bool isSuccess = false;
	for(int i = GC_HIERARCHY_MAX_LEVEL ; i >= 0 ; i--)
	{
		isSuccess = swap_popback::vector_find_swap_popback(mRootsDObjectsList[GC_HIERARCHY_MAX_LEVEL], dObjet);

		if(isSuccess == true)
		{
			break;
		}
	}

	return isSuccess;
}
