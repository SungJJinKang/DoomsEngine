#include "EveryCullingProfilerDebugger.h"

#include <Rendering/Culling/EveryCulling/EveryCullingCore.h>
#include <Rendering/Pipeline/PipeLines/DefaultGraphcisPipeLine.h>

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

	graphics::DefaultGraphcisPipeLine* defaultGraphicsPipeLine = CastTo<graphics::DefaultGraphcisPipeLine*>(dooms::graphics::GraphicsPipeLine::GetSingleton());
	D_ASSERT(IsValid(defaultGraphicsPipeLine));
	if (IsValid(defaultGraphicsPipeLine))
	{
		auto& profilingDatas = defaultGraphicsPipeLine->mRenderingCullingManager.mCullingSystem->mEveryCullingProfiler.GetProfilingDatas();
		for (auto& data : profilingDatas)
		{
			const std::string cullingModuleTag{ data.first.data(), data.first.size() };
			dooms::profiling::profilingManager::AddProfilingData(cullingModuleTag.c_str(), (float)data.second.mElapsedTime);
		}
	}

#endif
}

const char* dooms::graphics::EveryCullingProfilerDebugger::GetRenderingDebuggerModuleName()
{
	return "EveryCullingProfilerDebugger";
}
