#include "DObjectManager.h"

#include "DObject.h"
#include <Macros/Assert.h>

#include <vector_erase_move_lastelement/vector_swap_popback.h>
#include <EngineGUI/PrintText.h>

dooms::DObjectsContainer::DObjectsContainer()
{
    mDObjectList.reserve(DEFUALT_DOBJECT_LIST_RESERVATION_SIZE);
    mDObjectFlagList.reserve(DEFUALT_DOBJECT_LIST_RESERVATION_SIZE);
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

        mDObjectsContainer.mDObjectList.emplace(dObject);

        size_t flagIndex;
        if (mDObjectsContainer.mEmptyIndexInFlagList.empty() == false)
        {
            flagIndex = mDObjectsContainer.mEmptyIndexInFlagList.back();
            mDObjectsContainer.mEmptyIndexInFlagList.pop_back();
            mDObjectsContainer.mDObjectFlagList[flagIndex] = DAFAULT_DOBJECT_FLAGS;
        }
        else
        {
            mDObjectsContainer.mDObjectFlagList.push_back(DAFAULT_DOBJECT_FLAGS);
            flagIndex = mDObjectsContainer.mDObjectList.size() - 1;
        }

       
		dObject->mDObjectProperties.mCurrentIndexInDObjectList = flagIndex;
        D_ASSERT(flagIndex < mDObjectsContainer.mDObjectFlagList.size());
        
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

    D_ASSERT(newDObject->mDObjectProperties.mCurrentIndexInDObjectList < mDObjectsContainer.mDObjectFlagList.size());
    D_ASSERT(originalDObject.mDObjectProperties.mCurrentIndexInDObjectList < mDObjectsContainer.mDObjectFlagList.size());

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
            D_ASSERT(index < mDObjectsContainer.mDObjectFlagList.size());

            mDObjectsContainer.mDObjectList.erase(dObject);
            mDObjectsContainer.mEmptyIndexInFlagList.push_back(index);
            
        }
        
        dObject->mDObjectProperties.mCurrentIndexInDObjectList = INVALID_CURRENT_INDEX_IN_DOBJECT_LIST;

        isSuccess = true;

    }


    return isSuccess;
}


void dooms::DObjectManager::DestroyAllDObjects(const bool force)
{
    std::scoped_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    INT64 newIndex = 0;

    auto iterBegin = mDObjectsContainer.mDObjectList.begin();
    auto iterEnd = mDObjectsContainer.mDObjectList.end();

    while(iterBegin != iterEnd)
    {
        dooms::DObject* const targetDObject = *iterBegin;
        if (force || ((targetDObject->GetDObjectFlag() & eDObjectFlag::NewAllocated) != 0))
        {
            targetDObject->DestroySelfInstantly();

            iterBegin = mDObjectsContainer.mDObjectList.begin();
            iterEnd = mDObjectsContainer.mDObjectList.end(); // TODO : OPTIMIZATION
        }
        else
        {
            targetDObject->SetIsPendingKill();
            iterBegin++;
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

    mDObjectsContainer.mDObjectList.~unordered_set();
    mDObjectsContainer.mDObjectFlagList.~vector();
    mDObjectsContainer.mEmptyIndexInFlagList.~vector();
    
}

bool dooms::DObjectManager::IsDObjectLowLevelValid(const DObject* const dObject, const bool lock)
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
        isValid = (dObject->GetIsPendingKill() == false);
    }


	return isValid;
}

bool dooms::DObjectManager::IsDObjectExist(const DObject* const dObject, const bool lock)
{
    bool isExist = false;

    if (dObject != nullptr)
    {
        if (lock == true)
        {
            DObjectListMutex.lock();
        }

        if (mDObjectsContainer.mDObjectList.find(const_cast<DObject*>(dObject)) != mDObjectsContainer.mDObjectList.end())
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

