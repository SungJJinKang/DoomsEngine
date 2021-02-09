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
	public:
		MeshRenderer();
		MeshRenderer(graphics::Mesh* targetMesh, graphics::Material* targetMaterial);


		void Draw() override
		{
			this->BindMaterial();
			this->mTargetMesh->Draw();
		}


	protected:
		virtual void UpdateComponent() final;

	};
}
