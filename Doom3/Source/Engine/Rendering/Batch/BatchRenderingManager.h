#pragma once

#include <Core.h>

#include <unordered_map>

#include <Simple_SingleTon/Singleton.h>
#include "eBatchRenderingType.h"

#include "BatchRenderingManager.reflection.h"
namespace dooms
{
	class Renderer;
	namespace graphics
	{
		class RendererBatchContainer;
		class Material;
		class D_CLASS BatchRenderingManager : public DObject, public ISingleton<BatchRenderingManager>
		{
			GENERATE_BODY()

		private:

			D_PROPERTY()
			std::unordered_map<UINT64 /* Hash value of TargetMaterial */, std::vector<RendererBatchContainer*>> mBatchedRendererContainers;

			RendererBatchContainer* CreateBatchedRendererContainer(Material* const material, const eBatchRenderingType batchRenderingType);
			RendererBatchContainer* FindBatchedRendererContainer(Renderer* const renderer) const;

			bool bPauseBakeBatchMesh;
			/**
			 * \brief Relocate renderer based on world position. Relocate adjecent object into same container.
			 */
			void RelocateRendererBasedOnWorldPosition(std::vector<RendererBatchContainer*>& rendererBatchContainers);
			void RelocateRendererBasedOnWorldPosition();

		public:

			BatchRenderingManager();

			bool AddRendererToBatchRendering(Renderer* const renderer, const eBatchRenderingType batchRenderingType);
			bool RemoveRendererFromBatchRendering(Renderer* const renderer);

			void DrawAllBatchedRendererContainers() const;

			void SetPauseBakeBatchMesh(const bool pauseBakeBatchMesh);
			void BakeAllRendererBatchContainer();
		};
	}
}

