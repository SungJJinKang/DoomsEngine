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
			size_t mNumOfMeshes;

			D_PROPERTY()
			std::vector<MeshNode> mChilds;
			D_PROPERTY()
			size_t mNumOfChilds;

			MeshNode()
				:mMeshes(), mChilds(), mParent(nullptr), mNumOfMeshes(0), mNumOfChilds(0)
			{}
		};
	}
}