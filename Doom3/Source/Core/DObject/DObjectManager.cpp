#include "DObjectManager.h"

#include <cassert>

#include "DObject.h"

#include <chrono>
#include <UI/PrintText.h>

UINT64 dooms::DObjectManager::GenerateNewDObejctID()
{
    const UINT64 newDObjectID = mDObjectCounter++;
   
    assert(newDObjectID != 0xFFFFFFFFFFFFFFFF);

    return newDObjectID;
}

std::unordered_map<dooms::DObject*, UINT64>::iterator  dooms::DObjectManager::InsertDObjectID(DObject* const dObject, const UINT64 dObjectID)
{
    assert(dObject != nullptr);

    std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    std::unordered_map<dooms::DObject*, UINT64>::iterator iter = mDObjectsList.end();

    if (dObject != nullptr)
    {
        std::pair< std::unordered_map<dooms::DObject*, UINT64>::iterator, bool> result = mDObjectsList.insert_or_assign(dObject, dObjectID);
        iter = result.first;

		dObject->mDObjectID = dObjectID;
    }

    u_lock.unlock();

    return iter;	
}

std::unordered_map<dooms::DObject*, UINT64>::iterator  dooms::DObjectManager::InsertDObjectIDIfExist(DObject* const dObject, const UINT64 dObjectID)
{
    assert(dObject != nullptr);
    
    std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    std::unordered_map<dooms::DObject*, UINT64>::iterator iter = mDObjectsList.end();

    if (dObject != nullptr)
    {
        iter = mDObjectsList.find(dObject);
        if(iter != mDObjectsList.end())
        {
            iter->second = dObjectID;
        }
        dObject->mDObjectID = dObjectID;
    }

    u_lock.unlock();

    return iter;
}



bool dooms::DObjectManager::AddNewDObject(DObject* const dObject)
{
    assert(dObject != nullptr);

    bool isSuccess = false;

    if (dObject != nullptr)
	{
        const UINT64 newDObjectID = DObjectManager::GenerateNewDObejctID();
        InsertDObjectID(dObject, newDObjectID);

        isSuccess = true;
    }
 

    return isSuccess;
}

bool dooms::DObjectManager::ReplaceDObjectFromDObjectList(DObject&& originalDObject, DObject* const newDObject)
{
    assert(originalDObject.GetDObjectID() != INVALID_DOBJECT_ID);
    assert(&originalDObject != newDObject);

    const UINT64 originalDObjectID = originalDObject.GetDObjectID();

    InsertDObjectID(newDObject, originalDObjectID);

    InsertDObjectIDIfExist(&originalDObject, INVALID_DOBJECT_ID);

    return true;
}

bool dooms::DObjectManager::RemoveDObject(DObject* const dObject)
{
    const UINT64 dObjectID = dObject->GetDObjectID();

    std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    std::unordered_map<dooms::DObject*, UINT64>::iterator targetIter = InsertDObjectIDIfExist(dObject, INVALID_DOBJECT_ID);
    if (targetIter != mDObjectsList.end())
    {
        targetIter = mDObjectsList.erase(targetIter); //erasing iterator is much faster than not erasing
    }

    u_lock.unlock();
  
    return true;
}


void dooms::DObjectManager::DestroyAllDObjects(const bool force)
{
    std::unordered_map<dooms::DObject*, UINT64>::iterator erasedIter = mDObjectsList.begin();

    std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    while (erasedIter != mDObjectsList.end())
    {
		if (erasedIter->second != INVALID_DOBJECT_ID && ( force || erasedIter->first->GetDObjectFlag(eDObjectFlag::NewAllocated) == true ) )
		{
            //std::unordered_map<dooms::DObject*, UINT64>::iterator deletedIter = erasedIter++;
			//delete deletedIter->first;

			delete erasedIter->first;
            erasedIter = mDObjectsList.begin(); //reset
		}
		else
		{
			++erasedIter;
		}
    }

    u_lock.unlock();

    //ClearConatiner(); Never Do this at here. When Static Object is destroyed, It access to mDObjectsList in DObject's Destructor to reset DObject ID
}

void dooms::DObjectManager::ClearConatiner()
{
    std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    mDObjectsList.~unordered_map();

    u_lock.unlock();
}


bool dooms::DObjectManager::IsEmpty()
{
    return mDObjectsList.empty();
}

size_t dooms::DObjectManager::GetDObjectCount()
{
    return mDObjectsList.size();
}

