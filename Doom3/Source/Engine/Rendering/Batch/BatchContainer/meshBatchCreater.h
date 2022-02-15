#pragma once

#include <vector>

namespace dooms
{
	class Renderer;
	namespace graphics
	{
		class Mesh;
		namespace meshBatchCreater
		{
			//Batched Mesh is a Entity with Renderer component
			dooms::graphics::Mesh* CreateStaticBatchedMesh(const std::vector<dooms::Renderer*>& staticRendererList);

		};
	}

}
