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

		int mModelMatrixUniformLocation;

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
		void Draw() noexcept override
		{
			this->BindMaterial();

			if (this->mModelMatrixUniformLocation == -1)
			{
				this->mModelMatrixUniformLocation = this->mTargetMaterial->GetUniformLocation("model");
			}

			this->mTargetMaterial->SetMatrix4x4(this->mModelMatrixUniformLocation, this->GetTransform()->GetModelMatrix());
			this->mTargetMesh->Draw();
		}

		void SetMesh(graphics::Mesh* mesh);
		void SetMesh(graphics::Mesh& mesh);
		
		

	};
}
