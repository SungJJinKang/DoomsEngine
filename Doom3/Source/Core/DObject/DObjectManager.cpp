#include "DObjectManager.h"

#include <cassert>

#include "DObject.h"

#include <vector_erase_move_lastelement/vector_swap_popback.h>
#include <EngineGUI/PrintText.h>

dooms::DObjectsContainer::DObjectsContainer()
{
    mDObjectList.reserve(DEFUALT_DOBJECT_LIST_RESERVATION_SIZE);
    mDObjectIDList.reserve(DEFUALT_DOBJECT_LIST_RESERVATION_SIZE);
    mDObjectFlagList.reserve(DEFUALT_DOBJECT_LIST_RESERVATION_SIZE);
}

bool dooms::DObjectsContainer::IsEmpty() const
{
    assert(mDObjectList.size() == mDObjectIDList.size() == mDObjectFlagList.size());
    return mDObjectList.empty();
}

UINT64 dooms::DObjectManager::GenerateNewDObejctID()
{
    const UINT64 newDObjectID = mDObjectCounter++;
   
    assert(newDObjectID != 0xFFFFFFFFFFFFFFFF);

    return newDObjectID;
}

void dooms::DObjectManager::InsertDObjectID(DObject* const dObject, const UINT64 dObjectID)
{
    assert(dObject != nullptr);
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());

    if (dObject != nullptr)
    {
        std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

         mDObjectsContainer.mDObjectList.push_back(dObject);
         mDObjectsContainer.mDObjectIDList.push_back(dObjectID);
         mDObjectsContainer.mDObjectFlagList.push_back(0);

		dObject->mDObjectProperties.mDObjectID = dObjectID;
		dObject->mDObjectProperties.mCurrentIndexInDObjectList = mDObjectsContainer.mDObjectList.size() - 1;

        u_lock.unlock();
    }

    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());

}

void dooms::DObjectManager::InsertDObjectIDIfExist(DObject* const dObject)
{
    assert(dObject != nullptr);
    assert(dObject->GetDObjectID() != INVALID_DOBJECT_ID);
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());
    
    if (dObject != nullptr)
    {
        std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

        mDObjectsContainer.mDObjectList.push_back(dObject);
        mDObjectsContainer.mDObjectIDList.push_back(dObject->GetDObjectID());
        mDObjectsContainer.mDObjectFlagList.push_back(0);
        dObject->mDObjectProperties.mCurrentIndexInDObjectList = mDObjectsContainer.mDObjectList.size() - 1;
        
        u_lock.unlock();
    }

    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());

}



bool dooms::DObjectManager::AddNewDObject(DObject* const dObject)
{
    assert(dObject != nullptr);
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());

    bool isSuccess = false;

    if (dObject != nullptr)
	{
        const UINT64 newDObjectID = DObjectManager::GenerateNewDObejctID();
        InsertDObjectID(dObject, newDObjectID);

        isSuccess = true;
    }

    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());


    return isSuccess;
}

bool dooms::DObjectManager::ReplaceDObjectFromDObjectList(DObject&& originalDObject, DObject* const newDObject)
{
    assert(originalDObject.GetDObjectID() != INVALID_DOBJECT_ID);
    assert(&originalDObject != newDObject);
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());


    const UINT64 originalDObjectID = originalDObject.GetDObjectID();

    InsertDObjectID(newDObject, originalDObjectID);

    RemoveDObject(&originalDObject);

    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());

    return true;
}

bool dooms::DObjectManager::RemoveDObject(DObject* const dObject)
{
    assert(dObject != nullptr);
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());

    bool isSuccess = false;

    if (dObject != nullptr)
    {
        std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

        const std::vector<dooms::DObject*>::iterator iter = fast_find_simd::find_simd(mDObjectsContainer.mDObjectList.begin(), mDObjectsContainer.mDObjectList.end(), const_cast<dooms::DObject*>(dObject));
        if(iter != mDObjectsContainer.mDObjectList.end())
        {
            const size_t index = iter - mDObjectsContainer.mDObjectList.begin();

            assert(index < mDObjectsContainer.mDObjectList.size());

            swap_popback::vector_swap_popback(mDObjectsContainer.mDObjectList, iter);
            swap_popback::vector_swap_popback(mDObjectsContainer.mDObjectIDList, mDObjectsContainer.mDObjectIDList.begin() + index);
            swap_popback::vector_swap_popback(mDObjectsContainer.mDObjectFlagList, mDObjectsContainer.mDObjectFlagList.begin() + index);

            mDObjectsContainer.mDObjectList[index]->mDObjectProperties.mCurrentIndexInDObjectList = index;

            isSuccess = true;
        }

        dObject->mDObjectProperties.mDObjectID = INVALID_DOBJECT_ID;
    }

    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());

    return isSuccess;
}


void dooms::DObjectManager::DestroyAllDObjects(const bool force)
{
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());

    std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    size_t newIndex = 0;

    const size_t originalDObjectCount = mDObjectsContainer.mDObjectList.size();
    for(size_t i = 0 ; i < originalDObjectCount; i++)
    {
        dooms::DObject* const targetDObject = mDObjectsContainer.mDObjectList[i];
        if (force || ( (mDObjectsContainer.mDObjectFlagList[i] & eDObjectFlag::NewAllocated) != 0 ) )
        {
            delete targetDObject;
        }
        else
        {
            if(newIndex != i)
            {
                mDObjectsContainer.mDObjectList[newIndex] = mDObjectsContainer.mDObjectList[i];
                mDObjectsContainer.mDObjectIDList[newIndex] = mDObjectsContainer.mDObjectIDList[i];
                mDObjectsContainer.mDObjectFlagList[newIndex] = mDObjectsContainer.mDObjectFlagList[i];
                mDObjectsContainer.mDObjectList[newIndex]->mDObjectProperties.mCurrentIndexInDObjectList = newIndex;
            }
            
            newIndex++;
        }
    }

    mDObjectsContainer.mDObjectList.resize(newIndex);
    mDObjectsContainer.mDObjectIDList.resize(newIndex);
    mDObjectsContainer.mDObjectFlagList.resize(newIndex);

    u_lock.unlock();

    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());

    //ClearConatiner(); Never Do this at here. When Static Object is destroyed, It access to mDObjectsHashmap in DObject's Destructor to reset DObject ID
}

void dooms::DObjectManager::ClearConatiner()
{
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());

    std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    mDObjectsContainer.mDObjectList.~vector();
    mDObjectsContainer.mDObjectIDList.~vector();
    mDObjectsContainer.mDObjectFlagList.~vector();

    u_lock.unlock();

    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());
}

bool dooms::DObjectManager::IsDObjectStrongValid(const DObject* const dObject)
{
	bool isValid = false;

	if (dObject != nullptr)
	{
        std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

        if(fast_find_simd::find_simd(mDObjectsContainer.mDObjectList.begin(), mDObjectsContainer.mDObjectList.end(), const_cast<dooms::DObject*>(dObject)) != mDObjectsContainer.mDObjectList.end())
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
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());

    return mDObjectsContainer.mDObjectList.empty();
}

size_t dooms::DObjectManager::GetDObjectCount()
{
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());

    return mDObjectsContainer.mDObjectList.size();
}

