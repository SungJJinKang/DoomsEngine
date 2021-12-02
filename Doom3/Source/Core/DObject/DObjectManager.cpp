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

    if (dObject != nullptr)
    {
        std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

         mDObjectsContainer.mDObjectList.push_back(dObject);
         mDObjectsContainer.mDObjectIDList.push_back(dObjectID);
         mDObjectsContainer.mDObjectFlagList.push_back(0);
         
		dObject->mDObjectProperties.mCurrentIndexInDObjectList = mDObjectsContainer.mDObjectList.size() - 1;


        assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
        assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
        assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());

        u_lock.unlock();
    }
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

    assert(mDObjectsContainer.mDObjectList[originalDObject.mDObjectProperties.mCurrentIndexInDObjectList] == &originalDObject);

    const UINT64 originalDObjectID = originalDObject.GetDObjectID();
    
    mDObjectsContainer.mDObjectIDList[originalDObject.mDObjectProperties.mCurrentIndexInDObjectList] = GenerateNewDObejctID();

    if(newDObject->mDObjectProperties.mCurrentIndexInDObjectList == (size_t)-1)
    {
        InsertDObjectID(newDObject, originalDObjectID);
    }
    else
    {
        D_ASSERT(mDObjectsContainer.mDObjectList[newDObject->mDObjectProperties.mCurrentIndexInDObjectList] == newDObject);
        mDObjectsContainer.mDObjectIDList[newDObject->mDObjectProperties.mCurrentIndexInDObjectList] = originalDObjectID;
    }
    
    return true;
}

bool dooms::DObjectManager::RemoveDObject(DObject* const dObject)
{
    assert(dObject != nullptr);

    bool isSuccess = false;

    if (dObject != nullptr)
    {
        if(dObject->mDObjectProperties.mCurrentIndexInDObjectList != (size_t)-1)
        {
            std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

            const size_t index = dObject->mDObjectProperties.mCurrentIndexInDObjectList;
            assert(index < mDObjectsContainer.mDObjectList.size());

            if (index != mDObjectsContainer.mDObjectList.size() - 1)
            {
                D_ASSERT(mDObjectsContainer.mDObjectList[index] == dObject);

                swap_popback::vector_swap_popback(mDObjectsContainer.mDObjectList, mDObjectsContainer.mDObjectList.begin() + index);
                swap_popback::vector_swap_popback(mDObjectsContainer.mDObjectIDList, mDObjectsContainer.mDObjectIDList.begin() + index);
                swap_popback::vector_swap_popback(mDObjectsContainer.mDObjectFlagList, mDObjectsContainer.mDObjectFlagList.begin() + index);

                mDObjectsContainer.mDObjectList[index]->mDObjectProperties.mCurrentIndexInDObjectList = index;
            }
            else
            {
                mDObjectsContainer.mDObjectList.pop_back();
                mDObjectsContainer.mDObjectIDList.pop_back();
                mDObjectsContainer.mDObjectFlagList.pop_back();
            }


            assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
            assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
            assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());

            u_lock.unlock();
        }
        
        dObject->mDObjectProperties.mCurrentIndexInDObjectList = (size_t)-1;

        isSuccess = true;

    }


    return isSuccess;
}


void dooms::DObjectManager::DestroyAllDObjects(const bool force)
{
    std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    INT64 newIndex = 0;

    for(INT64 i = 0 ; i < mDObjectsContainer.mDObjectList.size(); i++)
    {
        dooms::DObject* const targetDObject = mDObjectsContainer.mDObjectList[i];
        if (force || ( (mDObjectsContainer.mDObjectFlagList[i] & eDObjectFlag::NewAllocated) != 0 ) )
        {
            delete targetDObject;
            i = newIndex - 1;
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

    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());

    u_lock.unlock();


    //ClearConatiner(); Never Do this at here. When Static Object is destroyed, It access to mDObjectsHashmap in DObject's Destructor to reset DObject ID
}

void dooms::DObjectManager::ClearConatiner()
{
    std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    mDObjectsContainer.mDObjectList.~vector();
    mDObjectsContainer.mDObjectIDList.~vector();
    mDObjectsContainer.mDObjectFlagList.~vector();

    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectFlagList.size());
    assert(mDObjectsContainer.mDObjectIDList.size() == mDObjectsContainer.mDObjectFlagList.size());

    u_lock.unlock();
}

bool dooms::DObjectManager::IsDObjectStrongValid(const DObject* const dObject, const bool lock)
{
	bool isValid = false;

	if (dObject != nullptr)
	{
        if(lock == true)
        {
            DObjectListMutex.lock();
        }

        if(fast_find_simd::find_simd(mDObjectsContainer.mDObjectList.begin(), mDObjectsContainer.mDObjectList.end(), const_cast<dooms::DObject*>(dObject)) != mDObjectsContainer.mDObjectList.end())
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

        if (fast_find_simd::find_simd(mDObjectsContainer.mDObjectList.begin(), mDObjectsContainer.mDObjectList.end(), const_cast<dooms::DObject*>(dObject)) != mDObjectsContainer.mDObjectList.end())
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
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());

    return mDObjectsContainer.mDObjectList.empty();
}

size_t dooms::DObjectManager::GetDObjectCount()
{
    assert(mDObjectsContainer.mDObjectList.size() == mDObjectsContainer.mDObjectIDList.size());

    return mDObjectsContainer.mDObjectList.size();
}

