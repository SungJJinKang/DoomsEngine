#include "SortFrontToBackSolver.h"

#include <algorithm>

#include <Rendering/Renderer/Renderer.h>
#include <Rendering/Renderer/RendererStaticIterator.h>
#include <Rendering/Camera.h>

void dooms::graphics::SortFrontToBackSolver::SortRenderer(std::vector<dooms::Renderer*>& rendereres, const size_t cameraIndex)
{
	std::sort(
		rendereres.begin(), rendereres.end(),
		[cameraIndex](const dooms::Renderer* const lhs, const dooms::Renderer* const rhs)
		{
			D_ASSERT(lhs != nullptr && rhs != nullptr);
			return lhs->GetDistanceToCamera(cameraIndex) < rhs->GetDistanceToCamera(cameraIndex);
		}
	);
}

/*
void dooms::graphics::SortFrontToBackSolver::CacheDistanceFromRenderersToCamera(
	std::vector<Renderer*>& rendereres,
	const std::vector<math::Vector3>& cameraPositions
)
{
	for(dooms::Renderer* renderer : rendereres)
	{
		for(size_t cameraIndex = 0 ; cameraIndex < cameraPositions.size() ; cameraIndex++)
		{
			renderer->CacheDistanceToCamera(cameraIndex, cameraPositions[cameraIndex]);
		}
	}
}
*/

void dooms::graphics::SortFrontToBackSolver::SortRenderer(const size_t cameraIndex)
{
	dooms::graphics::SortFrontToBackSolver::SortRenderer(
		dooms::RendererComponentStaticIterator::GetSingleton()->GetSortingRendererInLayer(),
		cameraIndex
	);
}

/*
void dooms::graphics::SortFrontToBackSolver::CacheDistanceFromRenderersToSpawnedCameras()
{
	const std::vector<dooms::Camera*>& spawnedCameraList = StaticContainer<dooms::Camera>::GetAllStaticComponents();
	std::vector<math::Vector3> cameraPositions;
	cameraPositions.reserve(spawnedCameraList.size());

	for(size_t cameraIndex = 0 ; cameraIndex < spawnedCameraList.size() ; cameraIndex++)
	{
		cameraPositions.push_back(spawnedCameraList[cameraIndex]->GetTransform()->GetPosition());
	}

	for (size_t layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
	{
		dooms::graphics::SortFrontToBackSolver::CacheDistanceFromRenderersToCamera(
			dooms::RendererComponentStaticIterator::GetSortedRendererInLayer(0, layerIndex),
			cameraPositions
		);
	}
}
*/
