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
			SIZE_T mNumOfMeshes;

			std::unique_ptr<MeshNode[]> mChilds;
			SIZE_T mNumOfChilds;
		};
	}
}