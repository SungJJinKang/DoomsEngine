#include "DObject.h"

#include <utility>

#include <Macros/Macros.h>

#include "DObjectManager.h"

void doom::DObject::Construct_Internal()
{
	if (mDObjectID == INVALID_DOBJECT_ID)
	{
		mDObjectID = DObjectManager::GenerateNewDObejctID();
		DObjectManager::AddDObject(this);
	}
}

void doom::DObject::InitProperties(const DObjectContructorParams& params)
{
	mDObjectProperties.mDObjectFlag |= params.DObjectFlag;
}


doom::DObject::DObject()
	:mDObjectID(INVALID_DOBJECT_ID), mDObjectProperties()
{
	Construct_Internal();
}

doom::DObject::DObject(const DObjectContructorParams& params)
	: mDObjectID(INVALID_DOBJECT_ID), mDObjectProperties{ }
{
	mDObjectProperties.mDObjectFlag = params.DObjectFlag;
	Construct_Internal();
}



doom::DObject::DObject(const DObject& dObject)
	:mDObjectID(INVALID_DOBJECT_ID), mDObjectProperties(mDObjectProperties)
{
	Construct_Internal();
}
doom::DObject& doom::DObject::operator=(const DObject& dObject)
{
	mDObjectID = INVALID_DOBJECT_ID;
	mDObjectProperties.mDObjectFlag = dObject.mDObjectProperties.mDObjectFlag;

	Construct_Internal();

	return *this;
}

doom::DObject::DObject(DObject&& dObject) noexcept
{
	DObjectManager::ReplaceDObject(dObject, this);
}



doom::DObject& doom::DObject::operator=(DObject&& dObject) noexcept
{
	DObjectManager::ReplaceDObject(dObject, this);
	return *this;
}

doom::DObject::~DObject()
{
	D_ASSERT(mDObjectID != INVALID_DOBJECT_ID);
	if (mDObjectID != INVALID_DOBJECT_ID)
	{
		DObjectManager::RemoveDObject(this);
	}
}



