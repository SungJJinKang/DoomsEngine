#include "EveryCullingProfilerDebugger.h"

#include <Graphics/Acceleration/LinearData_ViewFrustumCulling/EveryCullingCore.h>
#include <Rendering/Pipeline/GraphicsPipeLine.h>

void dooms::graphics::EveryCullingProfilerDebugger::Initialize()
{
}

void dooms::graphics::EveryCullingProfilerDebugger::PreRender()
{
}

void dooms::graphics::EveryCullingProfilerDebugger::Render()
{
}

void dooms::graphics::EveryCullingProfilerDebugger::PostRender()
{
#if defined(PROFILING_CULLING) && defined(D_PROFILING)
	auto& profilingDatas = GraphicsPipeLine::GetSingleton()->mRenderingCullingManager.mCullingSystem->mEveryCullingProfiler.GetProfilingDatas();
	for (auto& data : profilingDatas)
	{
		const std::string cullingModuleTag{ data.first.data(), data.first.size() };
		dooms::profiling::profilingManager::AddProfilingData(cullingModuleTag.c_str(), (float)data.second.mElapsedTime);
	}
#endif
}

const char* dooms::graphics::EveryCullingProfilerDebugger::GetRenderingDebuggerModuleName()
{
	return "EveryCullingProfilerDebugger";
}
