#include "DObjectManager.h"

#include "DObject.h"
size_t doom::DObjectManager::GenerateNewDObejctID()
{
    mDObjectCounter++;
    
    return mDObjectCounter;
}

bool doom::DObjectManager::AddDObject(DObject* const dObject)
{
    D_ASSERT(dObject->GetDObjectID() != INVALID_DOBJECT_ID);

	if (mDObjectsList.size() <= dObject->GetDObjectID())
	{
		mDObjectsList.resize(mDObjectsList.size() * 2 - 1, nullptr);
	}


    mDObjectsList[dObject->GetDObjectID()] = dObject;

    return true;
}

bool doom::DObjectManager::ReplaceDObjectFromDObjectList(DObject&& originalDObject, DObject* const newDObject)
{
    D_ASSERT(originalDObject.GetDObjectID() != INVALID_DOBJECT_ID);

    const unsigned long long originalDObjectID = originalDObject.GetDObjectID();

	mDObjectsList[originalDObjectID] = newDObject;
	newDObject->mDObjectID = originalDObjectID;
	originalDObject.mDObjectID = INVALID_DOBJECT_ID;

    return true;
}

bool doom::DObjectManager::RemoveDObject(DObject* const dObject)
{
    D_ASSERT(dObject->GetDObjectID() != INVALID_DOBJECT_ID);

    mDObjectsList[dObject->GetDObjectID()] = nullptr;
    dObject->mDObjectID = INVALID_DOBJECT_ID;

    return true;
}

doom::DObject* doom::DObjectManager::GetDObject(const size_t dObjectID)
{
    doom::DObject* dObject = nullptr;
    if (mDObjectsList.size() > dObjectID)
    {
        dObject = mDObjectsList[dObjectID];
    }
  
    return dObject;
}

void doom::DObjectManager::DestroyAllDObjects()
{
	for (auto dObject : mDObjectsList)
	{
		if (dObject != nullptr)
		{
			delete dObject;
		}
	}
}

