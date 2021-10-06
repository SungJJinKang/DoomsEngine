#include "DObject.h"

#include <utility>

#include <Macros/Macros.h>

#include "DObjectManager.h"

void doom::DObject::Construct_Internal()
{
	if (mDObjectID == INVALID_DOBJECT_ID)
	{
		DObjectManager::AddNewDObject(this);
	}
}

void doom::DObject::InitProperties(const DObjectContructorParams& params)
{
	mDObjectProperties.mDObjectFlag = params.DObjectFlag;
	mDObjectProperties.mDObjectName = params.mDObjectName;
}


void doom::DObject::ChangeDObjectName(const std::string& dObjectName)
{
	mDObjectProperties.mDObjectName = dObjectName;
}

void doom::DObject::SetOwnerDObject(const DObject* const ownerDObject)
{
	mDObjectProperties.mOwnerDObject = ownerDObject;
}

doom::DObject::DObject()
	:mDObjectID(INVALID_DOBJECT_ID), mDObjectProperties()
{
	Construct_Internal();
}

doom::DObject::DObject(const std::string& dObjectName)
	: mDObjectID(INVALID_DOBJECT_ID), mDObjectProperties()
{
	mDObjectProperties.mDObjectName = dObjectName;
	Construct_Internal();
}

doom::DObject::DObject(const DObject* const ownerDObject, const std::string& dObjectName)
	: mDObjectID(INVALID_DOBJECT_ID), mDObjectProperties()
{
	mDObjectProperties.mDObjectName = dObjectName;
	mDObjectProperties.mOwnerDObject = ownerDObject;
	Construct_Internal();
}


doom::DObject::DObject(const DObjectContructorParams& params)
	: mDObjectID(INVALID_DOBJECT_ID), mDObjectProperties()
{
	InitProperties(params);
	Construct_Internal();
}



doom::DObject::DObject(const DObject& dObject)
	:mDObjectID(INVALID_DOBJECT_ID), mDObjectProperties(dObject.mDObjectProperties)
{
	Construct_Internal();
}
doom::DObject& doom::DObject::operator=(const DObject& dObject)
{
	mDObjectProperties = dObject.mDObjectProperties;
	mDObjectID = INVALID_DOBJECT_ID;
	
	Construct_Internal();

	return *this;
}

doom::DObject::DObject(DObject&& dObject) noexcept
	: mDObjectProperties(dObject.mDObjectProperties)
{
	DObjectManager::ReplaceDObjectFromDObjectList(std::move(dObject), this);
}



doom::DObject& doom::DObject::operator=(DObject&& dObject) noexcept
{
	mDObjectProperties.mDObjectFlag = dObject.mDObjectProperties.mDObjectFlag;
	DObjectManager::ReplaceDObjectFromDObjectList(std::move(dObject), this);
	
	return *this;
}

doom::DObject::~DObject()
{
	DObjectManager::RemoveDObject(this);
}



