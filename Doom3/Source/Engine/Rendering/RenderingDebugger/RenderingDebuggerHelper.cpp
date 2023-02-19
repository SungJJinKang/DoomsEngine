#include "RenderingDebuggerHelper.h"

#include "RenderingDebuggerModules/Modules/EveryCullingProfilerDebugger.h"
#include "RenderingDebuggerModules/Modules/MaskedOcclusionCullingTester.h"
#include "RenderingDebuggerModules/Modules/OverDrawVisualization.h"
#include "RenderingDebuggerModules/Modules/RendererAABBDebugger.h"

#include <EngineConfigurationData/ConfigData.h>

std::vector<dooms::graphics::RenderingDebuggerModule*> dooms::graphics::renderingDebuggerHelper::CreateDefeaultRenderingDebuggerModules()
{
	std::vector<dooms::graphics::RenderingDebuggerModule*> renderingDebuggerModules{};

	renderingDebuggerModules.emplace_back
	(
		dooms::CreateDObject<EveryCullingProfilerDebugger>()
	);

	renderingDebuggerModules.emplace_back
	(
		dooms::CreateDObject<MaskedOcclusionCullingTester>()
	);

	if (dooms::ConfigData::GetSingleton()->GetConfigData().GetValue<bool>("Graphics", "OVERDRAW_VISUALIZATION"))
	{
		renderingDebuggerModules.emplace_back
		(
			dooms::CreateDObject<OverDrawVisualization>()
		);
	}

	renderingDebuggerModules.emplace_back
	(
		dooms::CreateDObject<RendererAABBDebugger>()
	);

	return renderingDebuggerModules;
}
