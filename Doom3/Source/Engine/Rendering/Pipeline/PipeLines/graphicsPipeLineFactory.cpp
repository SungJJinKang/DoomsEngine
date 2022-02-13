#include "graphicsPipeLineFactory.h"

#include <EngineConfigurationData/ConfigData.h>

dooms::graphics::GraphicsPipeLine* dooms::graphics::graphicsPipeLineFactory::CreateGraphicsPipeLineFromConfigFile()
{
	const std::string pipeLineType = ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("Graphics", "TARGET_GRAPHICS_PIPELINE");

	if(_stricmp(pipeLineType.c_str(), "PBR"))
	{
		
	}
	else if (_stricmp(pipeLineType.c_str(), "DEFERRED_RENDERING"))
	{

	}
	else
	{
		NEVER_HAPPEN;
	}
}
