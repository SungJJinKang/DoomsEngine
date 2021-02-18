#pragma once
#include <memory>
namespace doom
{
	namespace graphics
	{
		class Mesh;
		struct MeshNode
		{
			MeshNode* mParent;

			/// <summary>
			/// Nodes can reference same mesh
			/// array
			/// </summary>
			std::unique_ptr<Mesh*[]> mMeshes;
			size_t mNumOfMeshes;

			std::unique_ptr<MeshNode[]> mChilds;
			size_t mNumOfChilds;
		};
	}
}