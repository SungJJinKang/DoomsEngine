#include "RendererAABBDebugger.h"

#include <Graphics/GraphicsSetting.h>
#include <Rendering/Renderer/Renderer.h>

void dooms::graphics::RendererAABBDebugger::Initialize()
{
}

void dooms::graphics::RendererAABBDebugger::PreRender()
{
}

void dooms::graphics::RendererAABBDebugger::Render()
{
	if (graphics::graphicsSetting::DrawRenderingBoundingBox == true)
	{
		const std::vector<Renderer*>& renderersInLayer = RendererComponentStaticIterator::GetSingleton()->GetSortedRendererInLayer();
		for (size_t rendererIndex = 0; rendererIndex < renderersInLayer.size(); rendererIndex++)
		{
			renderersInLayer[rendererIndex]->ColliderUpdater<dooms::physics::AABB3D>::DrawWorldColliderCache();
		}
	}
}

void dooms::graphics::RendererAABBDebugger::PostRender()
{
}

const char* dooms::graphics::RendererAABBDebugger::GetRenderingDebuggerModuleName()
{
	return "RendererAABBDebugger";
}
