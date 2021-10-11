#include "SortFrontToBackSolver.h"

#include <algorithm>

#include <Rendering/Renderer/Renderer.h>
#include <Rendering/Renderer/RendererStaticIterator.h>
#include <Rendering/Camera.h>

void doom::graphics::SortFrontToBackSolver::SortRenderer(std::vector<doom::Renderer*>& rendereres, const size_t cameraIndex)
{
	std::sort(
		rendereres.begin(), rendereres.end(),
		[cameraIndex](const doom::Renderer* const lhs, const doom::Renderer* const rhs)
		{
			return lhs->GetDistanceToCamera(cameraIndex) < rhs->GetDistanceToCamera(cameraIndex);
		}
	);
}

/*
void doom::graphics::SortFrontToBackSolver::CacheDistanceFromRenderersToCamera(
	std::vector<Renderer*>& rendereres,
	const std::vector<math::Vector3>& cameraPositions
)
{
	for(doom::Renderer* renderer : rendereres)
	{
		for(size_t cameraIndex = 0 ; cameraIndex < cameraPositions.size() ; cameraIndex++)
		{
			renderer->CacheDistanceToCamera(cameraIndex, cameraPositions[cameraIndex]);
		}
	}
}
*/

void doom::graphics::SortFrontToBackSolver::SortRenderer(const size_t cameraIndex)
{
	for (size_t layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
	{
		doom::graphics::SortFrontToBackSolver::SortRenderer(
			doom::RendererComponentStaticIterator::GetSortedRendererInLayer(cameraIndex, layerIndex),
			cameraIndex
		);
	}
}

/*
void doom::graphics::SortFrontToBackSolver::CacheDistanceFromRenderersToSpawnedCameras()
{
	const std::vector<doom::Camera*>& spawnedCameraList = StaticContainer<doom::Camera>::GetAllStaticComponents();
	std::vector<math::Vector3> cameraPositions;
	cameraPositions.reserve(spawnedCameraList.size());

	for(size_t cameraIndex = 0 ; cameraIndex < spawnedCameraList.size() ; cameraIndex++)
	{
		cameraPositions.push_back(spawnedCameraList[cameraIndex]->GetTransform()->GetPosition());
	}

	for (size_t layerIndex = 0; layerIndex < MAX_LAYER_COUNT; layerIndex++)
	{
		doom::graphics::SortFrontToBackSolver::CacheDistanceFromRenderersToCamera(
			doom::RendererComponentStaticIterator::GetWorkingRendererInLayer(0, layerIndex),
			cameraPositions
		);
	}
}
*/
