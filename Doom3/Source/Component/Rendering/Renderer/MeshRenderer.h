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



		virtual void InitComponent() final
		{
			Renderer::InitComponent();
		}
		FORCE_INLINE virtual void UpdateComponent() final
		{
			Renderer::UpdateComponent();
		}

		FORCE_INLINE virtual void OnEndOfFrame_Component() final
		{
			Renderer::OnEndOfFrame_Component();
		}

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

		FORCE_INLINE void Draw() override
		{
			BindMaterial();

			D_ASSERT(mTargetMaterial);
			if (IsValid(mTargetMaterial))
			{
				GetMaterial()->GetUniformBufferObjectViewFromUBOName("ModelData")->SetMat4x4(graphics::eUniformLocation::ModelMatrix, GetTransform()->GetModelMatrix());
			}
			D_ASSERT(IsValid(mTargetMesh));
			if (IsValid(mTargetMesh))
			{
				mTargetMesh->Draw();
			}
		}

		void SetMesh(const graphics::Mesh* const mesh);
		const graphics::Mesh* GetMesh() const;
		virtual physics::AABB3D GetLocalAABBBound() const final;

	};
}
