#pragma once

#include <vector>
namespace dooms
{
	namespace asset
	{
		class ThreeDModelAsset;
	};
	namespace graphics
	{
		class Renderer;
		class Mesh;
		namespace MeshBatchCreater
		{
			//Batched Mesh is a Entity with Renderer component
			dooms::graphics::Mesh* CreateStaticBatchedMesh(const std::vector<dooms::graphics::Renderer*>& staticRendererList);

		};
	}

}
