#pragma once

#include <Core.h>

#include <vector>
#include "../Buffer/Mesh.h"
#include "Entity.h"

namespace doom
{
	namespace graphics
	{
		namespace MeshBatchCreater
		{
			//Batched Mesh is a Entity with Renderer component
			doom::Entity* CreateStaticBatchedMesh(const std::vector<doom::graphics::Mesh*>& batchedMeshList);

		};
	}
}
