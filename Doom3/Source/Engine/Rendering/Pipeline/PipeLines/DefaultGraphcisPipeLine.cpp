#include "DefaultGraphcisPipeLine.h"

#include <Graphics/graphicsSetting.h>
#include <Rendering/Renderer/RendererStaticIterator.h>
#include <Rendering/Acceleration/FrontToBackSorting/SortFrontToBackSolver.h>
#include <Rendering/Camera.h>
#include <ResourceManagement/JobSystem_cpp/JobSystem.h>
#include <Rendering/Renderer/Renderer.h>

dooms::graphics::DefaultGraphcisPipeLine::DefaultGraphcisPipeLine(dooms::graphics::Graphics_Server& graphicsServer)
	:
	GraphicsPipeLine(graphicsServer),
	mRenderingCullingManager(),
	mRenderingDebugger()
{
}

void dooms::graphics::DefaultGraphcisPipeLine::Initialize()
{
	GraphicsPipeLine::Initialize();

	mRenderingCullingManager.Initialize();
	mRenderingDebugger.Initialize();
}

void dooms::graphics::DefaultGraphcisPipeLine::LateInitialize()
{
	GraphicsPipeLine::LateInitialize();

	mRenderingDebugger.LateInitialize();
}


std::future<void> dooms::graphics::DefaultGraphcisPipeLine::PushFrontToBackSortJobToJobSystem
(
	dooms::Camera* const targetCamera, const UINT32 cameraIndex
)
{
	std::future<void> future{};

	if (graphicsSetting::IsSortObjectFrontToBack == true)
	{
		math::Vector3 cameraPos = targetCamera->GetTransform()->GetPosition();
		std::function<void()> FrontToBackSortJob = [cameraPos, cameraIndex]()
		{
			std::vector<Renderer*>& renderers = dooms::RendererComponentStaticIterator::GetSingleton()->GetSortingRendererInLayer();

			const size_t startRendererIndex = 0;
			const size_t rendererCount = renderers.size();

			for
				(
					size_t rendererIndex = startRendererIndex;
					rendererIndex < rendererCount;
					rendererIndex++
					)
			{
				D_ASSERT(IsValid(renderers[rendererIndex]));
				renderers[rendererIndex]->CacheDistanceToCamera(cameraIndex, cameraPos);
			}

			dooms::graphics::SortFrontToBackSolver::SortRenderer(cameraIndex);
		};

		future = resource::JobSystem::GetSingleton()->PushBackJobToPriorityQueue(FrontToBackSortJob);
	}

	return future;
}
