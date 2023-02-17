#include "DObjectGlobals.h"

#include <cstdlib>
#include <cstring>

bool dooms::IsDObjectValidLowLevel(const DObject* const dObject, const bool lock, const std::memory_order memoryOrder)
{
	bool bIsDObjectValid = false;

	if(dObject != nullptr)
	{
		if(dObject->IsValidLowLevel())
		{
			bIsDObjectValid = true;
		}
	}

	return bIsDObjectValid;
}

void* dooms::details::AllocateMemoryForDObject(const size_t AllocationSize)
{
	void* const AllocatedMemory = std::malloc(AllocationSize);

	std::memset(AllocatedMemory, 0, AllocationSize);

	return AllocatedMemory;
}

bool dooms::DestroyDObject(DObject* const dObject)
{
	bool isSuccess = false;

	if(IsValid(dObject) == true)
	{
		isSuccess = dObject->DestroySelf();
	}

	return isSuccess;
}
