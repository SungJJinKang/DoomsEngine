#pragma once

#include <vector>

#include <Vector3.h>

namespace dooms
{
	class Renderer;
	class Camera;
	namespace graphics
	{
		namespace SortFrontToBackSolver
		{
			void SortRenderer(std::vector<dooms::Renderer*>& rendereres, const size_t cameraIndex);
			//void CacheDistanceFromRenderersToCamera(std::vector<Renderer*>& rendereres, const std::vector<math::Vector3>& cameraPositions);

			void SortRenderer(const size_t cameraIndex);
			inline auto GetSortRendererLambda(const size_t cameraIndex)
			{
				return [cameraIndex] { dooms::graphics::SortFrontToBackSolver::SortRenderer(cameraIndex); };
			}

			//void CacheDistanceFromRenderersToSpawnedCameras();
		}
	}
}

