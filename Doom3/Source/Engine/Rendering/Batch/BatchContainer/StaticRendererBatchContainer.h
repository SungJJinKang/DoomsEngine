#pragma once

#include <Core.h>

#include <vector>

#include "RendererBatchContainer.h"

#include "StaticRendererBatchContainer.reflection.h"
namespace dooms
{
	class MeshRenderer;
	namespace graphics
	{
		class Material;
		class D_CLASS StaticRendererBatchContainer : public RendererBatchContainer
		{
			GENERATE_BODY()

		private:
						
			D_PROPERTY()
			Material* mBatchRenderingMaterial;
			
			void InitializeBatchRenderingMaterial(Material* const targetMaterial);

		public:

			StaticRendererBatchContainer() = delete;
			explicit StaticRendererBatchContainer(Material* const targetMaterial);

			void BakeBatchedMesh() final;
			eBatchRenderingType GetBatchRenderingType() const override;
			void BatchedDraw() const override;

			static bool CheckMaterialAcceptable(Material* const material);
			eRendererBatchContainerState CheckRendererAcceptable(Renderer* const renderer) const override;
		};
	}
}

