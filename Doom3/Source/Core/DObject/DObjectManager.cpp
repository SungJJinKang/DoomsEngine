#include "DObjectManager.h"

#include "DObject.h"
size_t doom::DObjectManager::GenerateNewDObejctID()
{
    mDObjectCounter++;
    return mDObjectCounter;
}

bool doom::DObjectManager::AddDObject(DObject* const dObject)
{
    bool isSuccess = false;

    D_ASSERT(dObject->GetDObjectID() != INVALID_DOBJECT_ID);

    auto dObjectIter = mDObjectsHashMap.find(dObject->GetDObjectID());
    if (dObjectIter == mDObjectsHashMap.end())
    {
        mDObjectsHashMap.emplace(dObject->GetDObjectID(), dObject);
        isSuccess = true;
    }

    D_ASSERT(isSuccess == true);

    return isSuccess;
}

bool doom::DObjectManager::ReplaceDObject(DObject& originalDObject, DObject* const newDObject)
{
    bool isSuccess = false;

    D_ASSERT(originalDObject.GetDObjectID() != INVALID_DOBJECT_ID);

    auto dObjectIter = mDObjectsHashMap.find(originalDObject.GetDObjectID());
    if (dObjectIter != mDObjectsHashMap.end())
    {
        dObjectIter->second = newDObject;
        newDObject->mDObjectID = originalDObject.GetDObjectID();
        originalDObject.mDObjectID = INVALID_DOBJECT_ID;

        isSuccess = true;
    }

    D_ASSERT(isSuccess == true);

    return isSuccess;
}

bool doom::DObjectManager::RemoveDObject(DObject* const dObject)
{
    bool isSuccess = false;

    D_ASSERT(dObject->GetDObjectID() != INVALID_DOBJECT_ID);

    auto dObjectIter = mDObjectsHashMap.find(dObject->GetDObjectID());
    if (dObjectIter != mDObjectsHashMap.end())
    {
        dObjectIter->second = nullptr;
        isSuccess = true;
    }

    D_ASSERT(isSuccess == true);

    return isSuccess;
}

doom::DObject* doom::DObjectManager::GetDObject(const size_t dObjectID)
{
    doom::DObject* dObject = nullptr;
    auto dObjectIter = mDObjectsHashMap.find(dObjectID);
    if (dObjectIter != mDObjectsHashMap.end())
    {
        dObject = dObjectIter->second;
    }
    return dObject;
}

void doom::DObjectManager::DestroyAllDObjects()
{
	for (auto dObject : mDObjectsHashMap)
	{
		if (dObject.second != nullptr)
		{
			delete dObject.second;
		}
	}
}

