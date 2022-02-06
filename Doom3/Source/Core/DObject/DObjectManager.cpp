#include "DObjectManager.h"

#include "DObject.h"
#include <Macros/Assert.h>

#include <vector_erase_move_lastelement/vector_swap_popback.h>
#include <EngineGUI/PrintText.h>

dooms::DObjectsContainer::DObjectsContainer()
{
    mDObjectList.reserve(DEFUALT_DOBJECT_LIST_RESERVATION_SIZE);
}

bool dooms::DObjectsContainer::IsEmpty() const
{
    return mDObjectList.empty();
}



UINT64 dooms::DObjectManager::GenerateNewDObejctID()
{
    const UINT64 newDObjectID = mDObjectCounter++;
   
    D_ASSERT(newDObjectID != 0xFFFFFFFFFFFFFFFF);

    return newDObjectID;
}

void dooms::DObjectManager::InsertDObjectID(DObject* const dObject, const UINT64 dObjectID)
{
    D_ASSERT(dObject != nullptr);

    if (dObject != nullptr)
    {
        std::scoped_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

        dObject->mDObjectProperties.mDObjectID = dObjectID;

        mDObjectsContainer.mDObjectList.emplace_back(dObject);
		dObject->mDObjectProperties.mCurrentIndexInDObjectList = mDObjectsContainer.mDObjectList.size() - 1;
        
    }
}


bool dooms::DObjectManager::AddNewDObject(DObject* const dObject)
{
    D_ASSERT(dObject != nullptr);

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
    D_ASSERT(originalDObject.GetDObjectID() != INVALID_DOBJECT_ID);
    D_ASSERT(&originalDObject != newDObject);
    
    const UINT64 originalDObjectID = originalDObject.GetDObjectID();
    
    originalDObject.mDObjectProperties.mDObjectID = GenerateNewDObejctID();

    if(newDObject->mDObjectProperties.mCurrentIndexInDObjectList == INVALID_CURRENT_INDEX_IN_DOBJECT_LIST)
    {
        InsertDObjectID(newDObject, originalDObjectID);
    }
    else
    {
        newDObject->mDObjectProperties.mDObjectID = originalDObjectID;
    }
    

    return true;
}

bool dooms::DObjectManager::RemoveDObject(DObject* const dObject)
{
    D_ASSERT(dObject != nullptr);

    bool isSuccess = false;

    if (dObject != nullptr)
    {
        if(dObject->mDObjectProperties.mCurrentIndexInDObjectList != INVALID_CURRENT_INDEX_IN_DOBJECT_LIST)
        {
            std::scoped_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

            const size_t index = dObject->mDObjectProperties.mCurrentIndexInDObjectList;
            D_ASSERT(mDObjectsContainer.mDObjectList.empty() == false);
            D_ASSERT(mDObjectsContainer.mDObjectList[index] == dObject);

            if(mDObjectsContainer.mDObjectList.size() > 1 && mDObjectsContainer.mDObjectList.back() != dObject)
            {
                mDObjectsContainer.mDObjectList[index] = mDObjectsContainer.mDObjectList.back();
                mDObjectsContainer.mDObjectList[index]->mDObjectProperties.mCurrentIndexInDObjectList = index;
            }

            mDObjectsContainer.mDObjectList.pop_back();
        }
        
        dObject->mDObjectProperties.mCurrentIndexInDObjectList = INVALID_CURRENT_INDEX_IN_DOBJECT_LIST;

        isSuccess = true;

    }


    return isSuccess;
}


void dooms::DObjectManager::DestroyAllDObjects(const bool force)
{
    std::scoped_lock<std::recursive_mutex> u_lock{ DObjectListMutex };
    {
        INT64 dObjectCount = mDObjectsContainer.mDObjectList.size();
        for (INT64 i = 0; i < dObjectCount; i++)
        {
            if(dObjectCount != mDObjectsContainer.mDObjectList.size())
            {
                dObjectCount = mDObjectsContainer.mDObjectList.size();
                i = -1;
                continue;
            }
            mDObjectsContainer.mDObjectList[i]->SetIsPendingKill();
        }
    }

    {
        for (INT64 i = 0; i < mDObjectsContainer.mDObjectList.size(); i++)
        {
            mDObjectsContainer.mDObjectList[i]->SetIsPendingKill();

            if (force || mDObjectsContainer.mDObjectList[i]->GetIsNewAllocated())
            {
                mDObjectsContainer.mDObjectList[i]->DestroySelfInstantly();
                i = -1;
            }
        }
    }
    /*
    size_t pullIndex = 0;
    for(size_t i = 0 ; i < aliveDObjectIndexs.size() ; i++)
    {
        mDObjectsContainer.mDObjectList[pullIndex] = mDObjectsContainer.mDObjectList[aliveDObjectIndexs[i]];
        mDObjectsContainer.mDObjectIDList[pullIndex] = mDObjectsContainer.mDObjectIDList[aliveDObjectIndexs[i]];
        mDObjectsContainer.mDObjectFlagList[pullIndex] = mDObjectsContainer.mDObjectFlagList[aliveDObjectIndexs[i]];

        pullIndex++;
    }

    mDObjectsContainer.mDObjectList.resize(aliveDObjectIndexs.size());
    mDObjectsContainer.mDObjectIDList.resize(aliveDObjectIndexs.size());
    mDObjectsContainer.mDObjectFlagList.resize(aliveDObjectIndexs.size());
    */
    
    //ClearConatiner(); Never Do this at here. When Static Object is destroyed, It access to mDObjectsHashmap in DObject's Destructor to reset DObject ID
}

void dooms::DObjectManager::ClearConatiner()
{
    std::scoped_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    mDObjectsContainer.mDObjectList.~vector();    
}

/*
bool dooms::DObjectManager::IsDObjectLowLevelValid(const DObject* const dObject, const bool lock, const std::memory_order memoryOrder)
{
	bool isValid = false;

	if (dObject != nullptr)
	{
        if(lock == true)
        {
            DObjectListMutex.lock();
        }

        // TODO : optimization. make this function fast
        if(mDObjectsContainer.mDObjectList.find(const_cast<DObject*>(dObject)) != mDObjectsContainer.mDObjectList.end())
        {
            isValid = true;
        }

        if (lock == true)
        {
            DObjectListMutex.unlock();
        }
	}

    if(isValid == true)
    {
        isValid = (dObject->GetIsPendingKill(memoryOrder) == false);
    }


	return isValid;
}
*/

bool dooms::DObjectManager::IsDObjectExist(const DObject* const dObject, const bool lock)
{
    bool isExist = false;

    if (dObject != nullptr)
    {
        if (lock == true)
        {
            DObjectListMutex.lock();
        }

        if (fast_find_simd::find_simd(mDObjectsContainer.mDObjectList.begin(), mDObjectsContainer.mDObjectList.end(), const_cast<DObject*>(dObject)) != mDObjectsContainer.mDObjectList.end())
        {
            isExist = true;
        }

        if (lock == true)
        {
            DObjectListMutex.unlock();
        }
    }

    return isExist;
}


bool dooms::DObjectManager::IsEmpty()
{
    return mDObjectsContainer.mDObjectList.empty();
}

size_t dooms::DObjectManager::GetDObjectCount()
{
    return mDObjectsContainer.mDObjectList.size();
}

std::vector<dooms::DObject*>& dooms::DObjectManager::GetDObjectList()
{
    return mDObjectsContainer.mDObjectList;
}

