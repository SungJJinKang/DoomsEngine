#pragma once

#include <Core.h>

#include "MeshNode.reflection.h"
namespace dooms
{
	namespace graphics
	{
		class Mesh;
		class DOOM_API D_CLASS MeshNode : public DObject
		{
			GENERATE_BODY()

		public:

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