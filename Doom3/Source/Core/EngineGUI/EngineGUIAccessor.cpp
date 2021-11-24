#include "EngineGUIAccessor.h"

#include <EngineGUI/imguiHelper/imguiWithReflection.h>

dooms::ui::EngineGUIAccessor::EngineGUIAccessor(DObject* const dObject)
	: mOwnerDObject(dObject)
{
}

void dooms::ui::EngineGUIAccessor::SetIsVisibleOnGUI(const bool isVisible)
{
	if(IsVisibleOnGUI == true && isVisible == false)
	{
		//dooms::ui::imguiWithReflection::RemoveFromVisibleOnGUIDObjectList(mOwnerDObject);
		IsVisibleOnGUI = false;
	}
	else if(IsVisibleOnGUI == false && isVisible == true)
	{
		//dooms::ui::imguiWithReflection::AddToVisibleOnGUIDObjectList(mOwnerDObject);
		IsVisibleOnGUI = true;
	}
}
