#pragma once
#include "Renderer.h"

#include "../Core/Graphics/Material/Material.h"
#include "../Core/Graphics/Buffer/Mesh.h"
#include "Transform.h"

namespace doom
{
	class MeshRenderer : public Renderer
	{
	private:
		const graphics::Mesh* mTargetMesh;


		MeshRenderer(const MeshRenderer&) = delete;
		MeshRenderer(MeshRenderer&&) noexcept = delete;
		MeshRenderer& operator=(const MeshRenderer&) = delete;
		MeshRenderer& operator=(MeshRenderer&&) noexcept = delete;

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

		

	public:
		MeshRenderer();
		virtual ~MeshRenderer(){}
		FORCE_INLINE void Draw() const override
		{
			BindMaterial();

			if (mTargetMaterial != nullptr)
			{
				graphics::Material::SetMatrix4x4(graphics::eUniformLocation::ModelMatrix, GetTransform()->GetModelMatrix());
			}
			if (mTargetMesh != nullptr)
			{
				mTargetMesh->Draw();
			}
		}

		void SetMesh(const graphics::Mesh* const mesh);
		
		virtual physics::AABB3D GetLocalAABBBound() const final;

	};
}
