#include "DObjectManager.h"

#include <cassert>

#include "DObject.h"

size_t doom::DObjectManager::GenerateNewDObejctID()
{
    mDObjectCounter++;
    
    return mDObjectCounter;
}

std::unordered_map<doom::DObject*, unsigned long long>::iterator  doom::DObjectManager::SetDObjectID(DObject* const dObject, const unsigned long long dObjectID)
{
    assert(dObject != nullptr);

    std::unordered_map<doom::DObject*, unsigned long long>::iterator iter = mDObjectsList.end();

    if (dObject != nullptr)
    {
        std::pair< std::unordered_map<doom::DObject*, unsigned long long>::iterator, bool> result = mDObjectsList.insert_or_assign(dObject, dObjectID);
        iter = result.first;

		dObject->mDObjectID = dObjectID;
    }

    return iter;	
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
    std::unordered_map<doom::DObject*, unsigned long long>::iterator targetIter = SetDObjectID(dObject, INVALID_DOBJECT_ID);
    if (targetIter != mDObjectsList.end())
    {
        targetIter = mDObjectsList.erase(targetIter);
    }
  

    return true;
}


void doom::DObjectManager::DestroyAllDObjects(const bool force)
{

    //TODO : add circular reference checker

    std::unordered_map<doom::DObject*, unsigned long long>::iterator erasedIter = mDObjectsList.begin();

    while (erasedIter != mDObjectsList.end())
    {
		if (erasedIter->second != INVALID_DOBJECT_ID && ( force || erasedIter->first->GetDObjectFlag(eDObjectFlag::NewAllocated) == true ) )
		{
			delete erasedIter->first;
            erasedIter = mDObjectsList.begin(); //reset
		}
		else
		{
			++erasedIter;
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

bool doom::DObjectManager::IsEmpty()
{
    return mDObjectsList.empty();
}

size_t doom::DObjectManager::GetDObjectCount()
{
    return mDObjectsList.size();
}

