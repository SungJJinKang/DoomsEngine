#pragma once
#include "Renderer.h"

#include <Rendering/Material/Material.h>
#include <Rendering/Buffer/Mesh.h>
#include "Transform.h"

#include "MeshRenderer.reflection.h"
namespace dooms
{
	class DOOM_API D_CLASS MeshRenderer : public Renderer
	{
		GENERATE_BODY()
		

	private:

		D_PROPERTY()
		const graphics::Mesh* mTargetMesh;


		virtual void InitComponent() final;
		virtual void UpdateComponent() final;
		virtual void OnEndOfFrame_Component() final;

	protected:

		virtual void OnDestroy() override;
		
		virtual void UpdateCullingEntityBlockViewer() override;
		virtual graphics::eBatchRenderingType GetCapableBatchRenderingType() const override;
		virtual bool IsBatchable() const override;

	public:

		MeshRenderer();
		virtual ~MeshRenderer();

		MeshRenderer(const MeshRenderer&) = default;
		MeshRenderer(MeshRenderer&&) noexcept = delete;
		MeshRenderer& operator=(const MeshRenderer&) = delete;
		MeshRenderer& operator=(MeshRenderer&&) noexcept = delete;

		void Draw() override;

		void SetMesh(const graphics::Mesh* const mesh);
		const graphics::Mesh* GetMesh() const;
		virtual physics::AABB3D GetLocalAABBBound() const final;

	};
}
