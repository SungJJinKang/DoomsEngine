#pragma once

#ifdef DEBUG_MODE

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
		std::unique_ptr<KDTree3DPoint> mKDTree;

		std::unique_ptr<graphics::PicktureInPickture> mPIPForDebug{};
		std::unique_ptr<graphics::Material> mBVHDebugMaterial{};
		static inline std::stack<INT32> recentAddedLeaf{};


		void AddNewRandomPoint();
		void AddNewPointWithMouse();
		void RemoveRecentAddedPoint();

		void DebugBVHTree(KDTree3DPoint::node_type* node, FLOAT32 x, FLOAT32 y, INT32 depth);
		void DrawTree();
		void DrawTopView();

	public:

		void SetKDTree3D(KDTree3DPoint* kdtree);

		virtual void Init() final;
		virtual void Update() final;

		void CheckActiveNode(KDTree3DPoint::node_type* node, std::vector<INT32>& activeNodeList);
		void ValidCheck();
	};
}


#endif