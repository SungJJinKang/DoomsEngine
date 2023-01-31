#include "DObjectGlobals.h"

#include <Windows.h>

bool dooms::IsLowLevelValid(const DObject* const dObject, const bool lock, const std::memory_order memoryOrder)
{
	bool isDObjectValid = false;

	// Use SEH. If address of dObject is invalid, it makes read access violation exception.
#if _MSC_VER
	__try
	{
#else
#error Unsupported Compiler
#endif
		isDObjectValid = IsValid(dObject);
		
		// todo : this is not enough... 
#if _MSC_VER
	}
	__except (_exception_code() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		isDObjectValid = false;
	}
#endif

	return isDObjectValid;
	//return dooms::DObjectManager::IsDObjectLowLevelValid(dObject, lock, memoryOrder);
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
