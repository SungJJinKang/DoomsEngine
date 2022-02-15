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

		public:

			StaticRendererBatchContainer() = delete;
			explicit StaticRendererBatchContainer(Material* const targetMaterial);

			void ReBakeBatchedMesh() final;
			eBatchRenderingType GetBatchRenderingType() const override;
		};
	}
}

