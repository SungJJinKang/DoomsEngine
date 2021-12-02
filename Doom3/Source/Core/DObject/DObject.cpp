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

void dooms::DObject::CopyFlagsToThisDObject(const UINT32 flags)
{
	ResetDObjectFlag(flags & ~dooms::NotCopyedFlagsWhenCopyMoveConstruct);
}


void dooms::DObject::InitProperties(const DObjectContructorParams& params)
{
	ResetDObjectFlag(params.DObjectFlag);
	mDObjectProperties.mDObjectName = params.mDObjectName;
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

bool dooms::DObject::DestroySelf() const
{
	bool isSuccess = false;
	if(GetDObjectFlag(eDObjectFlag::NewAllocated) == true)
	{
		delete this;
		isSuccess = true;
	}

	return isSuccess;
}

dooms::DObject::DObject()
	: mDObjectProperties(), mEngineGUIAccessor(this)
{
	Construct_Internal();
}

dooms::DObject::DObject(const std::string& dObjectName)
	: mDObjectProperties(), mEngineGUIAccessor(this)
{
	mDObjectProperties.mDObjectName = dObjectName;
	Construct_Internal();
}

dooms::DObject::DObject(const DObject* const ownerDObject, const std::string& dObjectName)
	: mDObjectProperties(), mEngineGUIAccessor(this)
{
	mDObjectProperties.mDObjectName = dObjectName;
	mDObjectProperties.mOwnerDObject = ownerDObject;
	Construct_Internal();
}


dooms::DObject::DObject(const DObjectContructorParams& params)
	: mDObjectProperties(), mEngineGUIAccessor(this)
{
	InitProperties(params);
	Construct_Internal();

}



dooms::DObject::DObject(const DObject& dObject)
	: mDObjectProperties(dObject.mDObjectProperties), mEngineGUIAccessor(this)
{
	Construct_Internal();

	CopyFlagsToThisDObject(dObject.GetDObjectFlag());
}

dooms::DObject& dooms::DObject::operator=(const DObject& dObject)
{
	mDObjectProperties = dObject.mDObjectProperties;
	
	Construct_Internal();
	CopyFlagsToThisDObject(dObject.GetDObjectFlag());

	return *this;
}

dooms::DObject::DObject(DObject&& dObject) noexcept
	: mDObjectProperties(std::move(dObject.mDObjectProperties)), mEngineGUIAccessor(this)
{
	DObjectManager::ReplaceDObjectFromDObjectList(std::move(dObject), this);
	CopyFlagsToThisDObject(dObject.GetDObjectFlag());
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
	// TODO : This can be problem if object is static variable.
	//	      if DObjectManager's static variable hash table is destroyed before calling static variable dobject's destructor

	if(mIsAddedToRootObjectList == true)
	{
		dooms::gc::GarbageCollectorManager::RemoveFromDObjectsList(this);
	}
	
	DObjectManager::RemoveDObject(this);
}

bool dooms::DObject::AddToRootObjectList()
{
	bool isSuccess = false;

	D_ASSERT(mIsAddedToRootObjectList == false);
	if(mIsAddedToRootObjectList == false)
	{
		dooms::gc::GarbageCollectorManager::AddToRootsDObjectsList(this);

		mIsAddedToRootObjectList = true;
		isSuccess = true;
	}

	return isSuccess;
}



