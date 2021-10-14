#pragma once

#ifdef DEBUG_MODE

#include <memory>
#include <stack>
#include <vector>
#include "Graphics/FrameBuffer/utility/PicktureInPickture.h"

#include "../BVH.h"

#include "../../ITester.h"

namespace doom
{
	class BVH_TestRoom : public ITester
	{
	private:
		std::unique_ptr<BVHAABB3D> mBVH;


		std::unique_ptr<graphics::PicktureInPickture> mPIPForDebug{};
		std::unique_ptr<graphics::Material> mBVHDebugMaterial{};
		static inline std::stack<INT32> recentAddedLeaf{};


		void AddNewRandomLeafNode();
		void AddNewRandomLeafNodeWithMouse();
		void RemoveRecentAddedLeafNode();
		void BalanceRecentAddedLeafNode();

		void DebugBVHTree(doom::BVHAABB3D::node_type* node, FLOAT32 x, FLOAT32 y, INT32 depth = 0);
	
		void TreeDebug();
		void AABBDebug(INT32 targetNode);
		void AABBDebug();

		void CheckActiveNode(doom::BVHAABB3D::node_type* node, std::vector<INT32>& activeNodeList);

	public:

		void SetBVH3D(BVHAABB3D* bvh3D);

		virtual void Init() final;
		virtual void Update() final;

		/// <summary>
		/// Check all active nodes can be traversed from rootNodeIndex
		/// </summary>
		void ValidCheck();
	};

}


#endif