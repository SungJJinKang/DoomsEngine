#pragma once

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
			Mesh** mMeshes;
			size_t mNumOfMeshes;

			MeshNode* mChilds;
			size_t mNumOfChilds;
		};
	}
}