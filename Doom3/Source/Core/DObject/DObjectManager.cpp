#include "DObjectManager.h"

#include <cassert>

#include "DObject.h"

#include <chrono>
#include <EngineGUI/PrintText.h>

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

    std::unordered_map<dooms::DObject*, UINT64>::iterator iter = mDObjectsHashmap.end();

    if (dObject != nullptr)
    {
        std::pair< std::unordered_map<dooms::DObject*, UINT64>::iterator, bool> result = mDObjectsHashmap.insert_or_assign(dObject, dObjectID);
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

    std::unordered_map<dooms::DObject*, UINT64>::iterator iter = mDObjectsHashmap.end();

    if (dObject != nullptr)
    {
        iter = mDObjectsHashmap.find(dObject);
        if(iter != mDObjectsHashmap.end())
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
    if (targetIter != mDObjectsHashmap.end())
    {
        targetIter = mDObjectsHashmap.erase(targetIter); //erasing iterator is much faster than not erasing
    }

    u_lock.unlock();
  
    return true;
}


void dooms::DObjectManager::DestroyAllDObjects(const bool force)
{
    std::unordered_map<dooms::DObject*, UINT64>::iterator erasedIter = mDObjectsHashmap.begin();

    std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    while (erasedIter != mDObjectsHashmap.end())
    {
		if (erasedIter->second != INVALID_DOBJECT_ID && ( force || erasedIter->first->GetDObjectFlag(eDObjectFlag::NewAllocated) == true ) )
		{
            //std::unordered_map<dooms::DObject*, UINT64>::iterator deletedIter = erasedIter++;
			//delete deletedIter->first;

			delete erasedIter->first;
            erasedIter = mDObjectsHashmap.begin(); //reset
		}
		else
		{
			++erasedIter;
		}
    }

    u_lock.unlock();

    //ClearConatiner(); Never Do this at here. When Static Object is destroyed, It access to mDObjectsHashmap in DObject's Destructor to reset DObject ID
}

void dooms::DObjectManager::ClearConatiner()
{
    std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    mDObjectsHashmap.~unordered_map();

    u_lock.unlock();
}

bool dooms::DObjectManager::IsDObjectStrongValid(const DObject* const dObject)
{
	bool isValid = false;

	if (dObject != nullptr)
	{
        std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

		std::unordered_map<DObject*, UINT64>::const_iterator iter = mDObjectsHashmap.find(const_cast<DObject*>(dObject));
		if (iter != mDObjectsHashmap.end() && iter->second != INVALID_DOBJECT_ID)
		{
			isValid = true;
		}

        u_lock.unlock();
	}

    if(isValid == true)
    {
        isValid = (dObject->GetIsPendingKill() == false);
    }


	return isValid;
}


bool dooms::DObjectManager::IsEmpty()
{
    return mDObjectsHashmap.empty();
}

size_t dooms::DObjectManager::GetDObjectCount()
{
    return mDObjectsHashmap.size();
}

