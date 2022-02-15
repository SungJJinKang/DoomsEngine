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
			std::unordered_map<UINT64 /* Hash value of TargetMaterial */, RendererBatchContainer*> mBatchedRendererContainers;

			RendererBatchContainer* CreateOrFindBatchedRendererContainer(Material* const material, const eBatchRenderingType batchRenderingType);
			RendererBatchContainer* FindBatchedRendererContainer(Material* const material) const;

		public:

			BatchRenderingManager();

			bool AddRendererToBatchRendering(Renderer* const renderer, const eBatchRenderingType batchRenderingType);
			bool RemoveRendererFromBatchRendering(Renderer* const renderer);

			void DrawAllBatchedRendererContainers() const;
		};
	}
}

