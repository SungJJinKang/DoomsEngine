#include "RenderingDebuggerHelper.h"

#include "RenderingDebuggerModules/DebugDrawer.h"
#include "RenderingDebuggerModules/EveryCullingProfilerDebugger.h"
#include "RenderingDebuggerModules/MaskedOcclusionCullingTester.h"
#include "RenderingDebuggerModules/OverDrawVisualization.h"

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

	return renderingDebuggerModules;
}
