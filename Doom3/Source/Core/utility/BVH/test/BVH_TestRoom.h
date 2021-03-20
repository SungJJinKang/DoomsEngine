#pragma once

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
		std::unique_ptr<BVH3D> mBVH;


		std::unique_ptr<graphics::PicktureInPickture> mPIPForDebug{};
		std::unique_ptr<graphics::Material> mBVHDebugMaterial{};
		static inline std::stack<int> recentAddedLeaf{};


		void AddNewRandomLeafNode();
		void AddNewRandomLeafNodeWithMouse();
		void RemoveRecentAddedLeafNode();
		void BalanceRecentAddedLeafNode();

		void DebugBVHTree(doom::BVH3D::node_type* node, float x, float y, int depth = 0);
	
		void TreeDebug();
		void AABBDebug(int targetNode);
		void AABBDebug();

		void CheckActiveNode(doom::BVH3D::node_type* node, std::vector<int>& activeNodeList);

	public:

		void SetBVH3D(BVH3D* bvh3D);

		virtual void Init() final;
		virtual void Update() final;

		/// <summary>
		/// Check all active nodes can be traversed from rootNodeIndex
		/// </summary>
		void ValidCheck();
	};

}
