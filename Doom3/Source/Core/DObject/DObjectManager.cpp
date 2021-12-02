#include "DObjectManager.h"

#include <cassert>

#include "DObject.h"

#include <vector_erase_move_lastelement/vector_swap_popback.h>
#include <EngineGUI/PrintText.h>

dooms::DObjectsContainer::DObjectsContainer()
{
    mDObjectsList.reserve(DEFUALT_DOBJECT_LIST_RESERVATION_SIZE);
    mDObjectsIDList.reserve(DEFUALT_DOBJECT_LIST_RESERVATION_SIZE);
}

bool dooms::DObjectsContainer::IsEmpty() const
{
    assert(mDObjectsList.size() == mDObjectsIDList.size());
    return mDObjectsList.empty() && mDObjectsIDList.empty();
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
    assert(mDObjectsContainer.mDObjectsList.size() == mDObjectsContainer.mDObjectsIDList.size());
    
    if (dObject != nullptr)
    {
        std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

         mDObjectsContainer.mDObjectsList.push_back(dObject);
         mDObjectsContainer.mDObjectsIDList.push_back(dObjectID);

		dObject->mDObjectID = dObjectID;

        u_lock.unlock();
    }
}

void dooms::DObjectManager::InsertDObjectIDIfExist(DObject* const dObject)
{
    assert(dObject != nullptr);
    assert(dObject->GetDObjectID() != INVALID_DOBJECT_ID);
    assert(mDObjectsContainer.mDObjectsList.size() == mDObjectsContainer.mDObjectsIDList.size());
    
    if (dObject != nullptr)
    {
        std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

        mDObjectsContainer.mDObjectsList.push_back(dObject);
        mDObjectsContainer.mDObjectsIDList.push_back(dObject->GetDObjectID());
        
        u_lock.unlock();
    }
}



bool dooms::DObjectManager::AddNewDObject(DObject* const dObject)
{
    assert(mDObjectsContainer.mDObjectsList.size() == mDObjectsContainer.mDObjectsIDList.size());

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
    assert(mDObjectsContainer.mDObjectsList.size() == mDObjectsContainer.mDObjectsIDList.size());

    assert(originalDObject.GetDObjectID() != INVALID_DOBJECT_ID);
    assert(&originalDObject != newDObject);

    const UINT64 originalDObjectID = originalDObject.GetDObjectID();

    InsertDObjectID(newDObject, originalDObjectID);

    RemoveDObject(&originalDObject);

    return true;
}

bool dooms::DObjectManager::RemoveDObject(DObject* const dObject)
{

    assert(mDObjectsContainer.mDObjectsList.size() == mDObjectsContainer.mDObjectsIDList.size());

    assert(dObject != nullptr);

    bool isSuccess = false;

    if (dObject != nullptr)
    {
        std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

        const std::vector<dooms::DObject*>::iterator iter = fast_find_simd::find_simd(mDObjectsContainer.mDObjectsList.begin(), mDObjectsContainer.mDObjectsList.end(), const_cast<dooms::DObject*>(dObject));
        if(iter != mDObjectsContainer.mDObjectsList.end())
        {
            const size_t index = iter - mDObjectsContainer.mDObjectsList.begin();
            swap_popback::vector_swap_popback(mDObjectsContainer.mDObjectsList, iter);
            swap_popback::vector_swap_popback(mDObjectsContainer.mDObjectsIDList, mDObjectsContainer.mDObjectsIDList.begin() + index);

            isSuccess = true;
        }
    }


    return isSuccess;
}


void dooms::DObjectManager::DestroyAllDObjects(const bool force)
{
    assert(mDObjectsContainer.mDObjectsList.size() == mDObjectsContainer.mDObjectsIDList.size());

    std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    size_t newIndex = 0;
    for(size_t i = 0 ; i < mDObjectsContainer.mDObjectsList.size() ; i++)
    {
        dooms::DObject* const targetDObject = mDObjectsContainer.mDObjectsList[i];
        if (force || targetDObject->GetDObjectFlag(eDObjectFlag::NewAllocated) == true)
        {
            delete targetDObject;
        }
        else
        {
            if(newIndex != i)
            {
                mDObjectsContainer.mDObjectsList[newIndex] = mDObjectsContainer.mDObjectsList[i];
                mDObjectsContainer.mDObjectsIDList[newIndex] = mDObjectsContainer.mDObjectsIDList[i];
            }
            
            newIndex++;
        }
    }

    mDObjectsContainer.mDObjectsList.resize(newIndex);
    mDObjectsContainer.mDObjectsIDList.resize(newIndex);

    u_lock.unlock();

    //ClearConatiner(); Never Do this at here. When Static Object is destroyed, It access to mDObjectsHashmap in DObject's Destructor to reset DObject ID
}

void dooms::DObjectManager::ClearConatiner()
{
    assert(mDObjectsContainer.mDObjectsList.size() == mDObjectsContainer.mDObjectsIDList.size());

    std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

    mDObjectsContainer.mDObjectsList.~vector();
    mDObjectsContainer.mDObjectsIDList.~vector();

    u_lock.unlock();
}

bool dooms::DObjectManager::IsDObjectStrongValid(const DObject* const dObject)
{
    assert(mDObjectsContainer.mDObjectsList.size() == mDObjectsContainer.mDObjectsIDList.size());

	bool isValid = false;

	if (dObject != nullptr)
	{
        std::unique_lock<std::recursive_mutex> u_lock{ DObjectListMutex };

        if(fast_find_simd::find_simd(mDObjectsContainer.mDObjectsList.begin(), mDObjectsContainer.mDObjectsList.end(), const_cast<dooms::DObject*>(dObject)) != mDObjectsContainer.mDObjectsList.end())
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
    assert(mDObjectsContainer.mDObjectsList.size() == mDObjectsContainer.mDObjectsIDList.size());
    return mDObjectsContainer.mDObjectsList.empty();
}

size_t dooms::DObjectManager::GetDObjectCount()
{
    assert(mDObjectsContainer.mDObjectsList.size() == mDObjectsContainer.mDObjectsIDList.size());
    return mDObjectsContainer.mDObjectsList.size();
}

