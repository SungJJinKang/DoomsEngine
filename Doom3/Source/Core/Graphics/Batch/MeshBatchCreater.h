#pragma once

#include <Core.h>

#include <vector>
namespace doom
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
			doom::graphics::Mesh* CreateStaticBatchedMesh(const std::vector<doom::graphics::Renderer*>& staticRendererList);

		};
	}

}
