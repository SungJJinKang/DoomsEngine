#ifdef DEBUG_MODE

#include "KDTree_TestRoom.h"

#include <Random.h>
#include <UserInput_Server.h>
#include <Vector2.h>

#include <vector>
#include <unordered_set>
#include <utility>
#include <vector_erase_move_lastelement/vector_swap_popback.h>

#include "../../Graphics/DebugGraphics.h"
#include "Graphics/Graphics_Server.h"
#include "Graphics/GraphicsAPI.h"
#include "Game/AssetManager/AssetManager.h"
#include "Graphics/Material.h"

#include "../KDTreeNodeView.h"

void doom::KDTree_TestRoom::AddNewRandomPoint()
{
	math::Vector3 newPoint{ random::Random::RandomFloatNumber(-10,10), random::Random::RandomFloatNumber(-10,10) , random::Random::RandomFloatNumber(-10,10) };
	mKDTree->Insert(newPoint);
}

void doom::KDTree_TestRoom::AddNewPointWithMouse()
{
	bool leftClick = userinput::UserInput_Server::GetMouseButtonRelease(userinput::eMouse_Button_Type::MOUST_BUTTON_LEFT);

	if (leftClick)
	{
		math::Vector2 ndcPoint = userinput::UserInput_Server::GetCurrentMouseNDCPosition();
		auto newNode = mKDTree->Insert(ndcPoint);
		recentAddedLeaf.push(newNode.GetNodeIndex());
		D_DEBUG_LOG("Create New LeafNode ", eLogType::D_ALWAYS);
	}
}

void doom::KDTree_TestRoom::RemoveRecentAddedPoint()
{
	int index = recentAddedLeaf.top();
	recentAddedLeaf.pop();
	
	mKDTree->Delete(mKDTree->mKDTreeNodes[index].mComponentValue);
}

#define DebugBVHTreeOffsetX 0.1f
#define DebugBVHTreeOffsetY 0.1f

void doom::KDTree_TestRoom::DebugBVHTree(KDTree3DPoint::node_type* node, float x, float y, int depth)
{
	if (node == nullptr)
	{
		return;
	}

	float offsetX = static_cast<float>(1.0f / (math::pow(2, depth + 1)));
	if (node->mLeftNode != NULL_NODE_INDEX)
	{
		graphics::DebugDrawer::GetSingleton()->DebugDraw2DLine({ x, y, 0 }, { x - offsetX, y - DebugBVHTreeOffsetY, 0 }, recentAddedLeaf.empty() == false && recentAddedLeaf.top() == node->mLeftNode ? eColor::Red : eColor::Blue, true);
		DebugBVHTree(&(mKDTree->mKDTreeNodes[node->mLeftNode]), x - offsetX, y - DebugBVHTreeOffsetY, depth + 1);
	}
	if (node->mRightNode != NULL_NODE_INDEX)
	{
		graphics::DebugDrawer::GetSingleton()->DebugDraw2DLine({ x, y, 0 }, { x + offsetX, y - DebugBVHTreeOffsetY, 0 }, recentAddedLeaf.empty() == false && recentAddedLeaf.top() == node->mRightNode ? eColor::Red : eColor::Blue, true);
		DebugBVHTree(&(mKDTree->mKDTreeNodes[node->mRightNode]), x + offsetX, y - DebugBVHTreeOffsetY, depth + 1);
	}
}

void doom::KDTree_TestRoom::DrawTree()
{
	if (mKDTree->mRootNodeIndex != NULL_NODE_INDEX)
	{
		/*
		for (int i = 0; i < mBVH->mTree.mNodeCapacity; i++)
		{
			mBVH->mTree.mNodes[i].mBoundingCollider.DrawPhysicsDebug(); // TODO : Draw recursively, don't draw all nodes
		}
		*/

		if (static_cast<bool>(mPIPForDebug))
		{
			mPIPForDebug->StaticBindFrameBuffer();

			graphics::GraphicsAPI::DefaultClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			mPIPForDebug->ClearFrameBuffer();

			graphics::DebugDrawer::GetSingleton()->SetDrawInstantlyMaterial(mBVHDebugMaterial.get());

			DebugBVHTree(&(mKDTree->mKDTreeNodes[mKDTree->mRootNodeIndex]), 0, 1, 0);

			graphics::DebugDrawer::GetSingleton()->SetDrawInstantlyMaterial(nullptr);
			mPIPForDebug->RevertFrameBuffer();
		}
	}
}

void doom::KDTree_TestRoom::DrawTopView()
{
}

void doom::KDTree_TestRoom::SetKDTree3D(KDTree3DPoint* kdtree)
{
}

void doom::KDTree_TestRoom::Init()
{
	if (static_cast<bool>(mKDTree) == false)
	{
		mKDTree = std::make_unique<KDTree3DPoint>(10000);
	}

	if (static_cast<bool>(mPIPForDebug) == false)
	{
		mPIPForDebug = std::make_unique<graphics::PicktureInPickture>(1024, 1024, math::Vector2(-1.0f, -1.0f), math::Vector2(1.0f, 1.0f));
		graphics::Graphics_Server::GetSingleton()->AddAutoDrawedPIPs(*(mPIPForDebug.get()));
	}

	if (static_cast<bool>(mBVHDebugMaterial) == false)
	{
		mBVHDebugMaterial = std::make_unique<graphics::Material>(doom::assetimporter::AssetManager::GetAsset<asset::eAssetType::SHADER>("Default2DColorShader.glsl"));
	}

}

void doom::KDTree_TestRoom::Update()
{
	if (static_cast<bool>(mKDTree) == false)
	{
		return;
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F6))
	{
		D_DEBUG_LOG("KDTree mCurrentAllocatedNodeCount : " + std::to_string(mKDTree->mCurrentAllocatedNodeCount), eLogType::D_ALWAYS);
		D_DEBUG_LOG("KDTree mCurrentActiveNodeCount : " + std::to_string(mKDTree->mCurrentActiveNodeCount), eLogType::D_ALWAYS);
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F7))
	{
		AddNewRandomPoint();
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F8))
	{
		ValidCheck();
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F9))
	{
		Init();
	}

	if (doom::userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F9))
	{
		DrawTree();
	}

	if (doom::userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F10))
	{
		DrawTopView();
	}

	AddNewPointWithMouse();
}

void doom::KDTree_TestRoom::CheckActiveNode(KDTree3DPoint::node_type* node, std::vector<int>& activeNodeList)
{
	if (node == nullptr)
	{
		return;
	}

#ifdef DEBUG_MODE
	if (node->bmIsActive == true)
	{
		auto iter = std::vector_find_swap_popback(activeNodeList, node->mIndex);
	}

	if (node->mLeftNode != NULL_NODE_INDEX)
	{
		CheckActiveNode(&(mKDTree->mKDTreeNodes[node->mLeftNode]), activeNodeList);
	}

	if (node->mRightNode != NULL_NODE_INDEX)
	{
		CheckActiveNode(&(mKDTree->mKDTreeNodes[node->mRightNode]), activeNodeList);
	}
#endif
}

void doom::KDTree_TestRoom::ValidCheck()
{
#ifdef DEBUG_MODE

	if (mKDTree->mRootNodeIndex != NULL_NODE_INDEX)
	{
		D_DEBUG_LOG("Valid Check : KDTree", eLogType::D_ALWAYS);

		//first check : recursively traverse all active nodes from rootIndex, Every active nodes in mKDTreeNodes array should be traversed
		//				every active nodes in mKDTreeNodes should be checked
		//				And call Node::ValidCheck();
		std::vector<int> checkedIndexs{};
		for (int i = 0; i < mKDTree->mCurrentAllocatedNodeCount; i++)
		{
			if (mKDTree->mKDTreeNodes[i].bmIsActive == true)
			{
				checkedIndexs.push_back(i);
			}
		}
		D_ASSERT(checkedIndexs.size() == mKDTree->mCurrentActiveNodeCount);
		CheckActiveNode(&(mKDTree->mKDTreeNodes[mKDTree->mRootNodeIndex]), checkedIndexs);
		D_ASSERT(checkedIndexs.size() == 0);

		//second check : traverse from each Leaf Nodes to RootNode. Check if Traversing arrived at rootIndex
		for (int i = 0; i < mKDTree->mCurrentAllocatedNodeCount; i++)
		{
			if (mKDTree->mKDTreeNodes[i].bmIsActive == true)
			{
				int index{ i };
				bool isSuccess{ false };
				while (index != NULL_NODE_INDEX)
				{
					if (index == mKDTree->mRootNodeIndex)
					{
						isSuccess = true;
						break;
					}

					index = mKDTree->mKDTreeNodes[index].mParentIndex;
				}

				D_ASSERT(isSuccess == true);
			}
		}


		//fourth check : check all nodes have unique child id ( all nodes have unique child id )
		//				 checked child id shouldn't be checked again
		std::unordered_set<int> checkedChildIndexs{};
		for (int i = 0; i < mKDTree->mCurrentAllocatedNodeCount; i++)
		{
			if (mKDTree->mKDTreeNodes[i].bmIsActive == true)
			{
				if (mKDTree->mKDTreeNodes[i].mLeftNode != NULL_NODE_INDEX)
				{
					D_ASSERT(checkedChildIndexs.find(mKDTree->mKDTreeNodes[i].mLeftNode) == checkedChildIndexs.end());
				}
				if (mKDTree->mKDTreeNodes[i].mRightNode != NULL_NODE_INDEX)
				{
					D_ASSERT(checkedChildIndexs.find(mKDTree->mKDTreeNodes[i].mRightNode) == checkedChildIndexs.end());
				}

				if (mKDTree->mKDTreeNodes[i].mLeftNode != NULL_NODE_INDEX)
				{
					checkedChildIndexs.insert(mKDTree->mKDTreeNodes[i].mLeftNode);
				}

				if (mKDTree->mKDTreeNodes[i].mRightNode != NULL_NODE_INDEX)
				{
					checkedChildIndexs.insert(mKDTree->mKDTreeNodes[i].mRightNode);
				}
			}
		}


		//fifth check : compare one node's parent index and parent index's child index
		for (int i = 0; i < mKDTree->mCurrentAllocatedNodeCount; i++)
		{
			if (mKDTree->mKDTreeNodes[i].bmIsActive == true)
			{
				if (mKDTree->mKDTreeNodes[i].mLeftNode != NULL_NODE_INDEX)
				{
					D_ASSERT(mKDTree->mKDTreeNodes[mKDTree->mKDTreeNodes[i].mLeftNode].mParentIndex == i);
				}

				if (mKDTree->mKDTreeNodes[i].mRightNode != NULL_NODE_INDEX)
				{
					D_ASSERT(mKDTree->mKDTreeNodes[mKDTree->mKDTreeNodes[i].mRightNode].mParentIndex == i);
				}

				if (mKDTree->mKDTreeNodes[i].mParentIndex != NULL_NODE_INDEX)
				{
					D_ASSERT(mKDTree->mKDTreeNodes[mKDTree->mKDTreeNodes[i].mParentIndex].mLeftNode == i || mKDTree->mKDTreeNodes[mKDTree->mKDTreeNodes[i].mParentIndex].mRightNode == i);
					D_ASSERT(mKDTree->mKDTreeNodes[mKDTree->mKDTreeNodes[i].mParentIndex].mLeftNode == i != mKDTree->mKDTreeNodes[mKDTree->mKDTreeNodes[i].mParentIndex].mRightNode == i);
				}
			}
		}

		//Check if All Nodes have proper mDimension
		{
			int currentNode;
			std::stack<std::pair<int, int>> nodeContainer{}; // nodeIndex, properNodeDimension
			nodeContainer.emplace(currentNode, 0);
			while (nodeContainer.empty() == false)
			{
				auto top = nodeContainer.top();
				nodeContainer.pop();

				D_ASSERT(mKDTree->mKDTreeNodes[top.first].mDimension == top.second);

				int nextDimension = (top.second + 1) % 3;
				if (mKDTree->mKDTreeNodes[top.first].mLeftNode != NULL_NODE_INDEX)
				{
					nodeContainer.emplace(mKDTree->mKDTreeNodes[top.first].mLeftNode, nextDimension);
				}
				if (mKDTree->mKDTreeNodes[top.first].mRightNode != NULL_NODE_INDEX)
				{
					nodeContainer.emplace(mKDTree->mKDTreeNodes[top.first].mRightNode, nextDimension);
				}
			}
		}

	}
	else
	{
		D_DEBUG_LOG("Valid Check Fail : KDTree ( There is no RootIndex ) ", eLogType::D_ALWAYS);
	}

#endif
}



#endif