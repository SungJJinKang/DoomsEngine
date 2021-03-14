#pragma once
#include "Renderer.h"

#include "../Core/Graphics/Material.h"
#include "../Core/Graphics/Buffer/Mesh.h"
#include "Transform.h"

namespace doom
{
	class MeshRenderer : public Renderer
	{
	private:
		graphics::Mesh* mTargetMesh;


		MeshRenderer(const MeshRenderer&) = delete;
		MeshRenderer(MeshRenderer&&) noexcept = delete;
		MeshRenderer& operator=(const MeshRenderer&) = delete;
		MeshRenderer& operator=(MeshRenderer&&) noexcept = delete;

		virtual void InitComponent() final
		{
			Renderer::InitComponent();
		}
		virtual void UpdateComponent() final
		{
			Renderer::UpdateComponent();
		}

		virtual void OnEndOfFrame_Component() final
		{
			Renderer::OnEndOfFrame_Component();
		}

	protected:

	public:
		MeshRenderer();
		virtual ~MeshRenderer(){}
		void Draw() override
		{
			this->BindMaterial();

			this->mTargetMaterial->SetMatrix4x4(graphics::eUniformLocation::ModelMatrix, this->GetTransform()->GetModelMatrix());
			this->mTargetMesh->Draw();
		}

		void SetMesh(graphics::Mesh* mesh);
		
		

	};
}
