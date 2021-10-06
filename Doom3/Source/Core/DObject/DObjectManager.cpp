#include "DObjectManager.h"

#include <cassert>
#include <iostream>

#include "DObject.h"

#include <chrono>
#include <UI/PrintText.h>

unsigned long long doom::DObjectManager::GenerateNewDObejctID()
{
    const unsigned long long newDObjectID = mDObjectCounter++;
   
    assert(newDObjectID != 0xFFFFFFFFFFFFFFFF);

    return newDObjectID;
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

    bool isSuccess = false;

    if (dObject != nullptr)
	{
        const unsigned long long newDObjectID = DObjectManager::GenerateNewDObejctID();
        SetDObjectID(dObject, newDObjectID);

        isSuccess = true;
    }
 

    return isSuccess;
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
    const unsigned long long dObjectID = dObject->GetDObjectID();
    
    std::unordered_map<doom::DObject*, unsigned long long>::iterator targetIter = SetDObjectID(dObject, INVALID_DOBJECT_ID);
    if (targetIter != mDObjectsList.end())
    {
        targetIter = mDObjectsList.erase(targetIter); //erasing iterator is much faster than not erasing
    }
  
    return true;
}


void doom::DObjectManager::DestroyAllDObjects(const bool force)
{
    std::unordered_map<doom::DObject*, unsigned long long>::iterator erasedIter = mDObjectsList.begin();

    while (erasedIter != mDObjectsList.end())
    {
		if (erasedIter->second != INVALID_DOBJECT_ID && ( force || erasedIter->first->GetDObjectFlag(eDObjectFlag::NewAllocated) == true ) )
		{
            //std::unordered_map<doom::DObject*, unsigned long long>::iterator deletedIter = erasedIter++;
			//delete deletedIter->first;

			delete erasedIter->first;
            erasedIter = mDObjectsList.begin(); //reset
		}
		else
		{
			++erasedIter;
		}
    }
}

bool doom::DObjectManager::IsDObjectValid(const DObject* const dObject)
{
	bool isValid = false;

	if (dObject != nullptr)
	{
		std::unordered_map<DObject*, unsigned long long>::const_iterator iter = mDObjectsList.find(const_cast<DObject *>(dObject));
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

