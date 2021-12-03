#include "DObjectGlobals.h"

bool dooms::DestroyDObject(DObject* const dObject)
{
	bool isSuccess = false;

	if(IsStrongValid(dObject) == true)
	{
		isSuccess = dObject->DestroySelf();
	}

	return isSuccess;
}
