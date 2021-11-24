#include "DObject.h"

#include <utility>

#include "DObjectManager.h"

#include <Reflection/ReflectionType/DClass.h>

void dooms::DObject::Construct_Internal()
{
	if (mDObjectID == INVALID_DOBJECT_ID)
	{
		DObjectManager::AddNewDObject(this);
	}
}

void dooms::DObject::InitProperties(const DObjectContructorParams& params)
{
	mDObjectProperties.mDObjectFlag = params.DObjectFlag;
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

dooms::DObject::DObject()
	:mDObjectID(INVALID_DOBJECT_ID), mDObjectProperties(), mEngineGUIAccessor(this)
{
	Construct_Internal();
}

dooms::DObject::DObject(const std::string& dObjectName)
	: mDObjectID(INVALID_DOBJECT_ID), mDObjectProperties(), mEngineGUIAccessor(this)
{
	mDObjectProperties.mDObjectName = dObjectName;
	Construct_Internal();
}

dooms::DObject::DObject(const DObject* const ownerDObject, const std::string& dObjectName)
	: mDObjectID(INVALID_DOBJECT_ID), mDObjectProperties(), mEngineGUIAccessor(this)
{
	mDObjectProperties.mDObjectName = dObjectName;
	mDObjectProperties.mOwnerDObject = ownerDObject;
	Construct_Internal();
}


dooms::DObject::DObject(const DObjectContructorParams& params)
	: mDObjectID(INVALID_DOBJECT_ID), mDObjectProperties(), mEngineGUIAccessor(this)
{
	InitProperties(params);
	Construct_Internal();
}



dooms::DObject::DObject(const DObject& dObject)
	:mDObjectID(INVALID_DOBJECT_ID), mDObjectProperties(dObject.mDObjectProperties), mEngineGUIAccessor(this)
{
	Construct_Internal();
}
dooms::DObject& dooms::DObject::operator=(const DObject& dObject)
{
	mDObjectProperties = dObject.mDObjectProperties;
	mDObjectID = INVALID_DOBJECT_ID;
	
	Construct_Internal();

	return *this;
}

dooms::DObject::DObject(DObject&& dObject) noexcept
	: mDObjectProperties(dObject.mDObjectProperties), mEngineGUIAccessor(this)
{
	DObjectManager::ReplaceDObjectFromDObjectList(std::move(dObject), this);
}



dooms::DObject& dooms::DObject::operator=(DObject&& dObject) noexcept
{
	mDObjectProperties.mDObjectFlag = dObject.mDObjectProperties.mDObjectFlag;
	DObjectManager::ReplaceDObjectFromDObjectList(std::move(dObject), this);
	
	return *this;
}

dooms::DObject::~DObject()
{
	DObjectManager::RemoveDObject(this);
}



