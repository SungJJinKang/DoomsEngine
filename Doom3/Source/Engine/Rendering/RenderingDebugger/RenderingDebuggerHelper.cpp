#include "RenderingDebuggerHelper.h"

#include "RenderingDebuggerModules/Modules/DebugDrawer.h"
#include "RenderingDebuggerModules/Modules/EveryCullingProfilerDebugger.h"
#include "RenderingDebuggerModules/Modules/MaskedOcclusionCullingTester.h"
#include "RenderingDebuggerModules/Modules/OverDrawVisualization.h"
#include "RenderingDebuggerModules/Modules/RendererAABBDebugger.h"

std::vector<dooms::graphics::RenderingDebuggerModule*> dooms::graphics::renderingDebuggerHelper::CreateDefeaultRenderingDebuggerModules()
{
	std::vector<dooms::graphics::RenderingDebuggerModule*> renderingDebuggerModules{};

	renderingDebuggerModules.emplace_back
	(
		dooms::CreateDObject<DebugDrawer>()
	);

	renderingDebuggerModules.emplace_back
	(
		dooms::CreateDObject<EveryCullingProfilerDebugger>()
	);

	renderingDebuggerModules.emplace_back
	(
		dooms::CreateDObject<MaskedOcclusionCullingTester>()
	);

	renderingDebuggerModules.emplace_back
	(
		dooms::CreateDObject<OverDrawVisualization>()
	);

	renderingDebuggerModules.emplace_back
	(
		dooms::CreateDObject<RendererAABBDebugger>()
	);
	
	return renderingDebuggerModules;
}