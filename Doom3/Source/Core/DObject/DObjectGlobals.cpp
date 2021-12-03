#include "DObjectGlobals.h"

bool dooms::DestroyDObject(DObject* const dObject)
{
	bool isSuccess = false;

	if(IsValid(dObject) == true)
	{
		isSuccess = dObject->DestroySelf();
	}

	return isSuccess;
}
