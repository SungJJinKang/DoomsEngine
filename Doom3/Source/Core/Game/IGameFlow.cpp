#include "IGameFlow.h"

using namespace dooms;

IGameFlow::IGameFlow()
{
	AddToRootObjectList();
	SetDObjectFlag(eDObjectFlag::NotCollectedByGC);
}

dooms::IGameFlow::~IGameFlow()
{
}
