#pragma once
#include "Renderer.h"
#include "../Core/Graphics/Buffer/Mesh.h"

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
		MeshRenderer(graphics::Mesh* targetMesh, graphics::Material* targetMaterial);


		void Draw() override
		{
			this->BindMaterial();
			this->mTargetMesh->Draw();
		}


	
		

	};
}
