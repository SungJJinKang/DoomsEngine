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

		enum eRendererBatchContainerState
		{
			Acceptable,

			/**
			 * \brief Renderer is unacceptable.
			 */
			Unacceptable,

			/**
			 * \brief Renderer is acceptable, but container is full. Create another container
			 */
			AcceptableButContainerIsFull
		};

		class D_CLASS RendererBatchContainer : public DObject
		{
			GENERATE_BODY()
				
		protected:

			D_PROPERTY()
			bool bmIsRendererListDirty;

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
			bool HasRenderer(Renderer* const renderer) const;

			virtual eRendererBatchContainerState CheckRendererAcceptable(Renderer* const Renderer) const = 0;
			virtual void BakeBatchedMesh() = 0;
			virtual eBatchRenderingType GetBatchRenderingType() const = 0;

			virtual void BatchedDraw() const = 0;

			std::vector<Renderer*>& GetBatchedRenderers();
			size_t GetBatchedRendererCount() const;
			const std::vector<Renderer*>& GetBatchedRenderers() const;
		};
	}
}


