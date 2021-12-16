#pragma once
#include "Renderer.h"

#include "../Core/Graphics/Material/Material.h"
#include "../Core/Graphics/Buffer/Mesh.h"
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

	public:

		MeshRenderer();
		virtual ~MeshRenderer();

		MeshRenderer(const MeshRenderer&) = default;
		MeshRenderer(MeshRenderer&&) noexcept = delete;
		MeshRenderer& operator=(const MeshRenderer&) = delete;
		MeshRenderer& operator=(MeshRenderer&&) noexcept = delete;

		FORCE_INLINE void Draw() const override
		{
			BindMaterial();

			if (IsValid(mTargetMaterial))
			{
				graphics::Material::SetMatrix4x4(graphics::eUniformLocation::ModelMatrix, GetTransform()->GetModelMatrix());
				
			}
			if (IsValid(mTargetMesh))
			{
				mTargetMesh->Draw();
			}
		}

		void SetMesh(const graphics::Mesh* const mesh);
		
		virtual physics::AABB3D GetLocalAABBBound() const final;

	};
}
