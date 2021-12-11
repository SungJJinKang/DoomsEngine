#pragma once

#include <Core.h>

#include <memory>

namespace dooms
{
	namespace graphics
	{
		class Mesh;
		struct DOOM_API D_STRUCT MeshNode
		{

			D_PROPERTY()
			MeshNode* mParent;

			/// <summary>
			/// Nodes can reference same mesh
			/// array
			/// </summary>
			D_PROPERTY()
			std::vector<Mesh*> mMeshes;

			D_PROPERTY()
			std::vector<MeshNode> mChilds;

			MeshNode()
				:mMeshes(), mChilds(), mParent(nullptr)
			{}
		};
	}
}