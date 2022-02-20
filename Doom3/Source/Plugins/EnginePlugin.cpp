#include "EnginePlugin.h"

#include "EnginePluginManager.h"

dooms::plugin::EnginePlugin::EnginePlugin()
{
	AddToRootObjectList();
}
dooms::plugin::EnginePlugin::~EnginePlugin()
{
	
}

const char* dooms::plugin::EnginePlugin::GetEnginePluginName()
{
	return GetTypeFullName();
}
