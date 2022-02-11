#include "RenderingDebugger.h"

#include <Rendering/Renderer/RendererStaticIterator.h>
#include "IO/UserInput_Server.h"
#include <Time/MainTimer.h>

#include "RenderingDebuggerModules/RenderingDebuggerModule.h"
#include "RenderingDebuggerHelper.h"

/*
void dooms::graphics::RenderingDebugger::DrawRenderingBoundingBox()
{
	if (graphics::graphicsSetting::DrawRenderingBoundingBox == true)
	{
		const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetSingleton()->GetSortedRendererInLayer(0);
		for (size_t rendererIndex = 0; rendererIndex < renderersInLayer.size(); rendererIndex++)
		{
			renderersInLayer[rendererIndex]->ColliderUpdater<dooms::physics::AABB3D>::DrawWorldColliderCache();
		}
	}
}
*/

void dooms::graphics::RenderingDebugger::UpdateFPS()
{
	FLOAT64 currentTime = MainTimer::GetSingleton()->GetCurrentTime();
	FrameCount++;

	const FLOAT64 timeInterval = currentTime - LastTIme;
	if(timeInterval >= 1.0)
	{
		FPS = (FLOAT64)FrameCount / timeInterval;
		FrameCount = 0;
		LastTIme = currentTime;
	}

	
}

dooms::graphics::RenderingDebugger::RenderingDebugger()
	: mRenderingDebuggerModule()
{
}

void dooms::graphics::RenderingDebugger::AppendDefaultRenderingDebuggerModules()
{
	std::vector<dooms::graphics::RenderingDebuggerModule*> defaultRenderingDebuggerModules = renderingDebuggerHelper::CreateDefeaultRenderingDebuggerModules();
	mRenderingDebuggerModule.insert(mRenderingDebuggerModule.end(), defaultRenderingDebuggerModules.begin(), defaultRenderingDebuggerModules.end());

	for(dooms::graphics::RenderingDebuggerModule* renderingDebuggerModule : defaultRenderingDebuggerModules)
	{
		renderingDebuggerModule->Initialize();
	}
}

void dooms::graphics::RenderingDebugger::Initialize()
{
	AppendDefaultRenderingDebuggerModules();
}

void dooms::graphics::RenderingDebugger::LateInitialize()
{
}

void dooms::graphics::RenderingDebugger::Update()
{
	UpdateFPS();
}

void dooms::graphics::RenderingDebugger::PreRender()
{
	for(RenderingDebuggerModule* renderingDebuggerModule : mRenderingDebuggerModule)
	{
		if(IsValid(renderingDebuggerModule) && renderingDebuggerModule->mIsEnabled == true)
		{
			renderingDebuggerModule->PreRender();
		}	
	}
}

void dooms::graphics::RenderingDebugger::Render()
{
	for (RenderingDebuggerModule* renderingDebuggerModule : mRenderingDebuggerModule)
	{
		if (IsValid(renderingDebuggerModule) && renderingDebuggerModule->mIsEnabled == true)
		{
			renderingDebuggerModule->Render();
		}
	}

	for (RenderingDebuggerModule* renderingDebuggerModule : mRenderingDebuggerModule)
	{
		if (IsValid(renderingDebuggerModule) && renderingDebuggerModule->mIsEnabled == true)
		{
			renderingDebuggerModule->LateRender();
		}
	}
}

void dooms::graphics::RenderingDebugger::PostRender()
{
	for (RenderingDebuggerModule* renderingDebuggerModule : mRenderingDebuggerModule)
	{
		if (IsValid(renderingDebuggerModule) && renderingDebuggerModule->mIsEnabled == true)
		{
			renderingDebuggerModule->PostRender();
		}
	}
}

/*
void dooms::graphics::RenderingDebugger::PrintDrawCallCounter()
{
	dooms::ui::PrintText("Draw Call : %d", RenderingDebugger::PreviousFrameDrawCallCounter);
}
*/
