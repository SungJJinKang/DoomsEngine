#pragma once

#include <Core.h>

#include <vector>
#include "../eBatchRenderingType.h"

#include "RendererBatchContainer.reflection.h"
namespace dooms
{
	class Renderer;
	class Renderer;
	namespace graphics
	{
		class Material;
		class Mesh;
		class D_CLASS RendererBatchContainer : public DObject
		{
			GENERATE_BODY()

		protected:

			D_PROPERTY()
			Mesh* mBatchedMesh;

			D_PROPERTY()
			Material* const mTargetMaterial;
			
			D_PROPERTY()
			std::vector<Renderer*> mBatchedRenderers;

		public:

			RendererBatchContainer() = delete;
			RendererBatchContainer(Material* const targetMaterial);
			RendererBatchContainer& operator=(const RendererBatchContainer&) = delete;
			RendererBatchContainer& operator=(RendererBatchContainer&&) noexcept = delete;


			bool AddRenderer(Renderer* const renderer, const bool bakeBatchedMesh = true);
			void AddRenderer(const std::vector<Renderer*>& renderers, const bool bakeBatchedMesh = true);
			bool RemoveRenderer(Renderer* const renderer, const bool bakeBatchedMesh = true);

			virtual void ReBakeBatchedMesh() = 0;
			virtual eBatchRenderingType GetBatchRenderingType() const = 0;
		};
	}
}


