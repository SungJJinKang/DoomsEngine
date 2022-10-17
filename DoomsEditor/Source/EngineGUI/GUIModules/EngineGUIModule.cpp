#include "EngineGUIModule.h"

dooms::ui::EngineGUIModule::EngineGUIModule()
	: mIsEnabled(true), bmIsInitialized(false)
{
}

void dooms::ui::EngineGUIModule::Init()
{
	D_ASSERT(bmIsInitialized == false);

	bmIsInitialized = true;
}

void dooms::ui::EngineGUIModule::InitIfNotInitialized()
{
	if(bmIsInitialized == false)
	{
		Init();
	}
}
