#include "EngineGUIAccessor.h"

#include <EngineGUI/imguiHelper/imguiWithReflection.h>
#include <GarbageCollector/GarbageCollectorManager.h>

void dooms::ui::EngineGUIAccessor::SetOwnerObject(DObject* const dObject)
{
	mOwnerDObject = dObject;
}

dooms::ui::EngineGUIAccessor::EngineGUIAccessor(DObject* const dObject)
	:mIsAddedToRootObjectList(false)
{
	SetOwnerObject(dObject);
}


bool dooms::ui::EngineGUIAccessor::AddToRootObjectList(const UINT32 level)
{
	D_ASSERT(IsStrongValid(mOwnerDObject) == true);
	return dooms::gc::GarbageCollectorManager::AddToRootsDObjectsList(mOwnerDObject, level);
}

void dooms::ui::EngineGUIAccessor::SetIsVisibleOnGUI(const bool isVisible)
{
	if(mIsVisibleOnGUI == true && isVisible == false)
	{
		dooms::ui::imguiWithReflection::RemoveFromVisibleOnGUIDObjectList(mOwnerDObject);
		mIsVisibleOnGUI = false;
	}
	else if(mIsVisibleOnGUI == false && isVisible == true)
	{
		dooms::ui::imguiWithReflection::AddToVisibleOnGUIDObjectList(mOwnerDObject);
		mIsVisibleOnGUI = true;
	}
}
