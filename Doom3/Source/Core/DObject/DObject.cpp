#include "DObject.h"

#include "DObjectManager.h"
#include <utility>

doom::DObject::DObject()
	:mDObjectID(INVALID_DOBJECT_ID)
{
	InitializeDObject();
}

void doom::DObject::InitializeDObject()
{
	mDObjectID = DObjectManager::GetSingleton()->GenerateNewDObejctID();
	DObjectManager::GetSingleton()->AddDObject(this);
}

doom::DObject::DObject(const DObject& dObject)
{
	InitializeDObject();
}

doom::DObject::DObject(DObject&& dObject) noexcept
{
	DObjectManager::GetSingleton()->ReplaceDObject(dObject, this);
}

doom::DObject& doom::DObject::operator=(const DObject& dObject)
{
	InitializeDObject();
	return *this;
}

doom::DObject& doom::DObject::operator=(DObject&& dObject) noexcept
{
	DObjectManager::GetSingleton()->ReplaceDObject(dObject, this);
	return *this;
}

doom::DObject::~DObject()
{
	if (mDObjectID != INVALID_DOBJECT_ID)
	{
		DObjectManager::GetSingleton()->RemoveDObject(this);
	}
}
