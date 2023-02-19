#include "graphicsPipeLineFactory.h"

#include <EngineConfigurationData/ConfigData.h>
#include <Rendering/Graphics_Server.h>
#include <Rendering/Pipeline/PipeLines/DeferredRendering/DeferredRenderingPipeLine.h>
#include <Rendering/Pipeline/PipeLines/PBR/ForwardPhysicsBasedRenderingPipeLine.h>


dooms::graphics::GraphicsPipeLine* dooms::graphics::graphicsPipeLineFactory::CreateGraphicsPipeLineFromConfigFile(Graphics_Server* const graphicsServer)
{
	D_ASSERT(IsValid(graphicsServer));

	dooms::graphics::GraphicsPipeLine* graphicsPipeLine = nullptr;

	if(IsValid(graphicsServer))
	{
		const std::string pipeLineType = ConfigData::GetSingleton()->GetConfigData().GetValue<std::string>("Graphics", "TARGET_GRAPHICS_PIPELINE");

		if
		(
			_stricmp(pipeLineType.c_str(), "PBR") == 0 ||
			_stricmp(pipeLineType.c_str(), "PHYSICSBASEDRENDERING") == 0 ||
			_stricmp(pipeLineType.c_str(), "PHYSICS_BASED_RENDERING") == 0
		)
		{
			graphicsPipeLine = dooms::CreateDObject<dooms::graphics::ForwardPhysicsBasedRenderingPipeLine>(*graphicsServer);
			D_RELEASE_LOG(eLogType::D_LOG, "Physics Base Rendering Graphics PipeLine is generated");
		}
		else if
		(
			_stricmp(pipeLineType.c_str(), "DEFERRED_RENDERING") == 0 ||
			_stricmp(pipeLineType.c_str(), "DEFERREDRENDERING") == 0
		)
		{
			graphicsPipeLine = dooms::CreateDObject<dooms::graphics::DeferredRenderingPipeLine>(*graphicsServer);
			D_RELEASE_LOG(eLogType::D_LOG, "Deferred Rendering Graphics PipeLine is generated");
		}
	}
	

	D_ASSERT(IsValid(graphicsPipeLine));

	return graphicsPipeLine;
}
