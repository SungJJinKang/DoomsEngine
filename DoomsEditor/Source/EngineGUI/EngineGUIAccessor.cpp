#include "EngineGUIAccessor.h"

#include "imguiHelper/imguiWithReflection.h"
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
