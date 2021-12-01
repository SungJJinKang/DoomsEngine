#include "DObjectGlobals.h"

bool dooms::DestroyDObject(const DObject* const dObject)
{
	bool isSuccess = false;

	if(IsStrongValid(dObject) == true)
	{
		dObject->DestroySelf();
		isSuccess = true;
	}

	return isSuccess;
}
