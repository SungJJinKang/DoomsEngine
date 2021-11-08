#pragma once
#include <memory>
namespace dooms
{
	namespace graphics
	{
		class Mesh;
		struct DOOM_API D_STRUCT MeshNode
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