#include "DObjectManager.h"

#include <cassert>

#include "DObject.h"

size_t doom::DObjectManager::GenerateNewDObejctID()
{
    mDObjectCounter++;
    
    return mDObjectCounter;
}

void doom::DObjectManager::SetDObjectID(DObject* const dObject, const unsigned long long dObjectID)
{
    assert(dObject != nullptr);

    if (dObject != nullptr)
    {
        //not thread safe
		mDObjectsList[dObject] = dObjectID;
		dObject->mDObjectID = dObjectID;
    }
	
}

bool doom::DObjectManager::AddNewDObject(DObject* const dObject)
{
    assert(dObject != nullptr);

    if (dObject != nullptr)
	{
        const unsigned long long newDObjectID = DObjectManager::GenerateNewDObejctID();
        SetDObjectID(dObject, newDObjectID);
    }
 

    return true;
}

bool doom::DObjectManager::ReplaceDObjectFromDObjectList(DObject&& originalDObject, DObject* const newDObject)
{
    assert(originalDObject.GetDObjectID() != INVALID_DOBJECT_ID);
    assert(&originalDObject != newDObject);

    const unsigned long long originalDObjectID = originalDObject.GetDObjectID();

    SetDObjectID(newDObject, originalDObjectID);

    SetDObjectID(&originalDObject, INVALID_DOBJECT_ID);

    return true;
}

bool doom::DObjectManager::RemoveDObject(DObject* const dObject)
{
    SetDObjectID(dObject, INVALID_DOBJECT_ID);

    return true;
}


void doom::DObjectManager::DestroyAllDObjects()
{
	for (auto dObject : mDObjectsList)
	{
		if (dObject.second != INVALID_DOBJECT_ID && dObject.first->GetDObjectFlag(eDObjectFlag::NewAllocated) == true)
		{
 			delete dObject.first;
		}
	}
}

bool doom::DObjectManager::IsDObjectValid(DObject* const dObject)
{
	bool isValid = false;

	if (dObject != nullptr)
	{
		std::unordered_map<DObject*, unsigned long long>::const_iterator iter = mDObjectsList.find(dObject);
		if (iter != mDObjectsList.end() && iter->second != INVALID_DOBJECT_ID)
		{
			isValid = true;
		}
	}


	return isValid;
}

