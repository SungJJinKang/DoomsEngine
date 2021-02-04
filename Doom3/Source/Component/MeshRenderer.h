#pragma once
#include "Renderer.h"
#include "../Core/Graphics/Buffer/Mesh.h"

namespace doom
{
	class MeshRenderer : public Renderer
	{
	private:
		graphics::Mesh* mTargetMesh;

	public:
		MeshRenderer(graphics::Mesh* targetMesh, graphics::Material* targetMaterial);


		void Draw() override
		{
			this->BindMaterial();
			this->mTargetMesh->Draw();
		}


	};
}
