#pragma once

#include <memory>
#include <stack>
#include <vector>
#include "Graphics/FrameBuffer/utility/PicktureInPickture.h"

#include "../KDTree.h"

#include "../../ITester.h"

namespace doom
{
	class KDTree_TestRoom : public ITester
	{
	private:
		std::unique_ptr<KDTree3D> mKDTree;

		std::unique_ptr<graphics::PicktureInPickture> mPIPForDebug{};
		std::unique_ptr<graphics::Material> mBVHDebugMaterial{};
		static inline std::stack<int> recentAddedLeaf{};


		void AddNewRandomPoint();
		void AddNewPointWithMouse();
		void RemoveRecentAddedPoint();

		void DebugBVHTree(KDTree3D::node_type* node, float x, float y, int depth);
		void DrawTree();
		void DrawTopView();

	public:

		void SetKDTree3D(KDTree3D* kdtree);

		virtual void Init() final;
		virtual void Update() final;

		void CheckActiveNode(KDTree3D::node_type* node, std::vector<int>& activeNodeList);
		void ValidCheck();
	};
}


