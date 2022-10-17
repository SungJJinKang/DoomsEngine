#include "DObject.h"

#include <utility>

#include "DObjectManager.h"

#include <Reflection/ReflectionType/DClass.h>
#include <GarbageCollector/GarbageCollectorManager.h>

void dooms::DObject::Construct_Internal()
{
	if (GetDObjectID() == INVALID_DOBJECT_ID)
	{
		DObjectManager::AddNewDObject(this);
	}
}

void dooms::DObject::CopyFlagsToThisDObject(const UINT64 flags)
{
	ResetDObjectFlag(flags & ~dooms::NotCopyedFlagsWhenCopyMoveConstruct);
}


void dooms::DObject::InitProperties(const DObjectContructorParams& params)
{
	SetDObjectFlag(params.DObjectFlag);
	mDObjectProperties.mDObjectName = params.mDObjectName;
	// TODO : Add code setting nullptr to raw pointer member variable ( gc doesn't run every tick. so before gc run, Invalid raw pointer can be referenced. it makes exception.
	//	  Stack allocated object's raw pointer member variable can't be reset to nullptr, but most of DObjects is not that case.
}


const std::string& dooms::DObject::GetDObjectName() const
{
	return mDObjectProperties.mDObjectName;
}

void dooms::DObject::ChangeDObjectName(const std::string& dObjectName)
{
	mDObjectProperties.mDObjectName = dObjectName;
}

void dooms::DObject::ChangeDObjectName(const char* const dObjectName)
{
	mDObjectProperties.mDObjectName = dObjectName;
}

void dooms::DObject::SetOwnerDObject(const DObject* const ownerDObject)
{
	mDObjectProperties.mOwnerDObject = ownerDObject;
}

dooms::reflection::DClass dooms::DObject::GetDClass() const
{
	return dooms::reflection::DClass(GetTypeHashVlue());
}

bool dooms::DObject::DestroySelf()
{
	bool isSuccess = SetIsPendingKill();

	return isSuccess;
}

bool dooms::DObject::DestroySelfInstantly()
{
	bool isSucess = false;

	SetIsPendingKill();
	if(GetIsNewAllocated() == true)
	{
		delete this;
		isSucess = true;
	}
	
	return isSucess;
}

dooms::DObject::DObject()
	: mDObjectProperties()
{
	Construct_Internal();
}

dooms::DObject::DObject(const std::string& dObjectName)
	: mDObjectProperties()
{
	mDObjectProperties.mDObjectName = dObjectName;
	Construct_Internal();
}

dooms::DObject::DObject(const DObject* const ownerDObject, const std::string& dObjectName)
	: mDObjectProperties()
{
	mDObjectProperties.mDObjectName = dObjectName;
	mDObjectProperties.mOwnerDObject = ownerDObject;
	Construct_Internal();
}


dooms::DObject::DObject(const DObjectContructorParams& params)
	: mDObjectProperties()
{
	InitProperties(params);
	Construct_Internal();

}



dooms::DObject::DObject(const DObject& dObject)
	: mDObjectProperties(dObject.mDObjectProperties)
{
	const UINT64 originalObjectFlag = dObject.GetDObjectFlag();

	Construct_Internal();
	CopyFlagsToThisDObject(dObject.GetDObjectFlag());

	if((originalObjectFlag & dooms::eDObjectFlag::IsRootObject) != 0)
	{
		AddToRootObjectList();
	}
}

dooms::DObject::DObject(DObject&& dObject) noexcept
	: mDObjectProperties(std::move(dObject.mDObjectProperties))
{
	const UINT64 originalObjectFlag = dObject.GetDObjectFlag();

	DObjectManager::ReplaceDObjectFromDObjectList(std::move(dObject), this);
	CopyFlagsToThisDObject(dObject.GetDObjectFlag());
	
	if ((originalObjectFlag & dooms::eDObjectFlag::IsRootObject) != 0)
	{
		AddToRootObjectList();
	}
	Construct_Internal();
}


dooms::DObject& dooms::DObject::operator=(const DObject& dObject)
{
	mDObjectProperties = dObject.mDObjectProperties;
	
	CopyFlagsToThisDObject(dObject.GetDObjectFlag());

	return *this;
}

dooms::DObject& dooms::DObject::operator=(DObject&& dObject) noexcept
{
	mDObjectProperties = std::move(dObject.mDObjectProperties);
	DObjectManager::ReplaceDObjectFromDObjectList(std::move(dObject), this);
	CopyFlagsToThisDObject(dObject.GetDObjectFlag());
	
	return *this;
}

dooms::DObject::~DObject()
{
	SetDObjectFlag(eDObjectFlag::IsPendingKill, std::memory_order_relaxed);
	
	if(GetDObjectFlag(eDObjectFlag::IsRootObject) == true)
	{
		dooms::gc::GarbageCollectorManager::RemoveFromDObjectsList(this);
	}
	
	DObjectManager::RemoveDObject(this);
}

void dooms::DObject::OnSetPendingKill_Internal()
{
	if (GetDObjectFlag(eDObjectFlag::IsRootObject) == true)
	{
		dooms::gc::GarbageCollectorManager::RemoveFromDObjectsList(this);
	}
}

bool dooms::DObject::AddToRootObjectList()
{
	bool isSuccess = false;
	
	if(GetDObjectFlag(eDObjectFlag::IsRootObject) == false)
	{
		dooms::gc::GarbageCollectorManager::AddToRootsDObjectsList(this);
		isSuccess = true;
	}

	return isSuccess;
}

bool dooms::DObject::GetIsRootObject() const
{
	return GetDObjectFlag(eDObjectFlag::IsRootObject);
}



