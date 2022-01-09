#include "RenderingDebugger.h"

#ifdef DEBUG_DRAWER

#include "../Graphics_Core.h"
#include "../graphicsSetting.h"
#include <Rendering/Renderer/RendererStaticIterator.h>
#include <Rendering/Renderer/Renderer.h>
#include <EngineGUI/PrintText.h>
#include "IO/UserInput_Server.h"



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

void dooms::graphics::RenderingDebugger::UpdateFPS()
{
	FLOAT64 currentTime = dooms::graphics::GraphicsAPI::GetTime();
	FrameCount++;

	const FLOAT64 timeInterval = currentTime - LastTIme;
	if(timeInterval >= 1.0)
	{
		FPS = (FLOAT64)FrameCount / timeInterval;
		FrameCount = 0;
		LastTIme = currentTime;
	}

	
}

void dooms::graphics::RenderingDebugger::Update()
{
	UpdateFPS();
}

void dooms::graphics::RenderingDebugger::PrintDrawCallCounter()
{
	dooms::ui::PrintText("Draw Call : %d", RenderingDebugger::PreviousFrameDrawCallCounter);
}

void dooms::graphics::RenderingDebugger::UpdateInputForPrintDrawCallCounter()
{

#ifdef DEBUG_MODE

	if (dooms::userinput::UserInput_Server::GetKeyUp(dooms::graphics::GraphicsAPIInput::eKEY_CODE::KEY_F5))
	{
		PrintDrawCallCounter();
	}

#endif

}

#endif