#ifdef DEBUG_MODE

#include "BVH_TestRoom.h"

#include <Random.h>
#include <UserInput_Server.h>
#include <Vector2.h>

#include <vector>
#include <unordered_set>
#include <vector_erase_move_lastelement/vector_swap_popback.h>

#include "../../Graphics/DebugGraphics.h"
#include "Graphics/Graphics_Server.h"
#include "Graphics/GraphicsAPI.h"
#include "Game/AssetManager/AssetManager.h"
#include "Graphics/Material.h"

#include "../BVH_Node_View.h"

void doom::BVH_TestRoom::AddNewRandomLeafNode()
{
	math::Vector3 newLower{ doom::random::Random::RandomFloatNumber(-1, 1), doom::random::Random::RandomFloatNumber(-1, 1) , doom::random::Random::RandomFloatNumber(-1, 1) };
	math::Vector3 newUpper{ doom::random::Random::RandomFloatNumber(-1, 1), doom::random::Random::RandomFloatNumber(-1, 1) , doom::random::Random::RandomFloatNumber(-1, 1) };


	doom::physics::AABB3D newAABB{ math::Min(newLower, newUpper), math::Max(newLower, newUpper) };
	auto newNode = mBVH->InsertLeaf(newAABB, nullptr);
	recentAddedLeaf.push(newNode.GetNodeIndex());
}


math::Vector2 leftPos{};
math::Vector2 rightPos{};


void doom::BVH_TestRoom::AddNewRandomLeafNodeWithMouse()
{
	bool leftClick = userinput::UserInput_Server::GetMouseButtonRelease(userinput::eMouse_Button_Type::MOUST_BUTTON_LEFT);
	bool rightClick = userinput::UserInput_Server::GetMouseButtonRelease(userinput::eMouse_Button_Type::MOUST_BUTTON_RIGHT);
	bool middleClick = userinput::UserInput_Server::GetMouseButtonRelease(userinput::eMouse_Button_Type::MOUST_BUTTON_MIDDLE);

	if (leftClick || rightClick)
	{
		math::Vector2 ndcPoint = userinput::UserInput_Server::GetCurrentMouseNDCPosition();
		if (leftClick)
		{
			leftPos = ndcPoint;
			D_DEBUG_LOG({ "Set BVH Left NDC Pos : ", leftPos.toString() }, eLogType::D_ALWAYS);
		}
		else
		{
			rightPos = ndcPoint;
			D_DEBUG_LOG({ "Set BVH Right NDC Pos : ", rightPos.toString() }, eLogType::D_ALWAYS);
		}
	}

	if (middleClick)
	{
		physics::AABB3D aabb{ leftPos, rightPos };
		auto newNode = mBVH->InsertLeaf(aabb, nullptr);
		recentAddedLeaf.push(newNode.GetNodeIndex());
		D_DEBUG_LOG("Create New LeafNode ", eLogType::D_ALWAYS);
	}
	
}

void doom::BVH_TestRoom::RemoveRecentAddedLeafNode()
{
	if (recentAddedLeaf.empty() == true)
	{
		return;
	}

	int nodeIndex = recentAddedLeaf.top();
	mBVH->RemoveLeafNode(nodeIndex);

	recentAddedLeaf.pop();
}

void doom::BVH_TestRoom::BalanceRecentAddedLeafNode()
{
	if (recentAddedLeaf.empty() == true)
	{
		return;
	}

	mBVH->Balance(recentAddedLeaf.top());
}

void doom::BVH_TestRoom::SetBVH3D(BVHAABB3D* bvh3D)
{
	mBVH = std::unique_ptr<BVHAABB3D>(bvh3D);
}

void doom::BVH_TestRoom::Update()
{
	if (static_cast<bool>(mBVH) == false)
	{
		return;
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F6))
	{
		D_DEBUG_LOG(std::to_string(mBVH->mCurrentActiveNodeCount), eLogType::D_ALWAYS);
		D_DEBUG_LOG(std::to_string(mBVH->GetLeafNodeCount()), eLogType::D_ALWAYS);
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F7))
	{
		RemoveRecentAddedLeafNode();
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
		TreeDebug();
	}

	if (doom::userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F10))
	{
		AABBDebug();
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F11))
	{
		AddNewRandomLeafNode();
	}

	AddNewRandomLeafNodeWithMouse();
}

#define DebugBVHTreeOffsetX 0.1f
#define DebugBVHTreeOffsetY 0.1f


void doom::BVH_TestRoom::DebugBVHTree(doom::BVHAABB3D::node_type* node, float x, float y, int depth)
{
	if (node == nullptr)
	{
		return;
	}

	float offsetX = static_cast<float>(1.0f / (math::pow(2, depth + 1)));
	if (node->mLeftNode != NULL_NODE_INDEX)
	{
		graphics::DebugDrawer::GetSingleton()->DebugDraw2DLine({ x, y, 0 }, { x - offsetX, y - DebugBVHTreeOffsetY, 0 }, mBVH->mNodes[node->mLeftNode].mIsLeaf == false ? eColor::Black : ((recentAddedLeaf.empty() == false && recentAddedLeaf.top() == node->mLeftNode) ? eColor::Red : eColor::Blue), true);
		DebugBVHTree(&(mBVH->mNodes[node->mLeftNode]), x - offsetX, y - DebugBVHTreeOffsetY, depth + 1);
	}
	if (node->mRightNode != NULL_NODE_INDEX)
	{
		graphics::DebugDrawer::GetSingleton()->DebugDraw2DLine({ x, y, 0 }, { x + offsetX, y - DebugBVHTreeOffsetY, 0 }, mBVH->mNodes[node->mRightNode].mIsLeaf == false ? eColor::Black : ((recentAddedLeaf.empty() == false && recentAddedLeaf.top() == node->mRightNode) ? eColor::Red : eColor::Blue), true);
		DebugBVHTree(&(mBVH->mNodes[node->mRightNode]), x + offsetX, y - DebugBVHTreeOffsetY, depth + 1);
	}
}


void doom::BVH_TestRoom::Init()
{
	if (static_cast<bool>(mBVH) == false)
	{
		mBVH = std::make_unique<BVHAABB3D>(10000);
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


void doom::BVH_TestRoom::TreeDebug()
{
	if (mBVH->mRootNodeIndex != NULL_NODE_INDEX)
	{
		/*
		for (int i = 0; i < mBVH->mNodeCapacity; i++)
		{
			mBVH->mNodes[i].mBoundingCollider.DrawPhysicsDebug(); // TODO : Draw recursively, don't draw all nodes
		}
		*/

		if (static_cast<bool>(mPIPForDebug))
		{
			mPIPForDebug->StaticBindFrameBuffer();

			graphics::GraphicsAPI::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			mPIPForDebug->ClearFrameBuffer();

			graphics::DebugDrawer::GetSingleton()->SetDrawInstantlyMaterial(mBVHDebugMaterial.get());

			DebugBVHTree(&(mBVH->mNodes[mBVH->mRootNodeIndex]), 0, 1, 0);

			graphics::DebugDrawer::GetSingleton()->SetDrawInstantlyMaterial(nullptr);
			mPIPForDebug->RevertFrameBuffer();
		}
	}
}

void doom::BVH_TestRoom::AABBDebug()
{
	if (static_cast<bool>(mPIPForDebug))
	{
		mPIPForDebug->StaticBindFrameBuffer();

		graphics::GraphicsAPI::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		mPIPForDebug->ClearFrameBuffer();

		graphics::DebugDrawer::GetSingleton()->SetDrawInstantlyMaterial(mBVHDebugMaterial.get());


		for (int i = 0; i < mBVH->mCurrentAllocatedNodeCount; i++)
		{
			if (mBVH->mNodes[i].bmIsActive == true)
			{
				if (recentAddedLeaf.empty() == false && i == recentAddedLeaf.top())
				{
					mBVH->mNodes[i].mBoundingCollider.DrawPhysicsDebugColor(eColor::Red, true);
				}
				else if (recentAddedLeaf.empty() == false && mBVH->IsAncesterOf(i, recentAddedLeaf.top()))
				{
					mBVH->mNodes[i].mBoundingCollider.DrawPhysicsDebugColor(eColor::Blue, true);
				}
				else if (mBVH->mNodes[i].mIsLeaf == false)
				{
					mBVH->mNodes[i].mBoundingCollider.DrawPhysicsDebugColor(eColor::Black, true);
				}
				else if (mBVH->mNodes[i].mIsLeaf == true)
				{
					mBVH->mNodes[i].mBoundingCollider.DrawPhysicsDebugColor(eColor::Green, true);
				}

			}
		}


		graphics::DebugDrawer::GetSingleton()->SetDrawInstantlyMaterial(nullptr);
		mPIPForDebug->RevertFrameBuffer();
	}
}

void doom::BVH_TestRoom::AABBDebug(int targetNode)
{
	if (static_cast<bool>(mPIPForDebug))
	{
		mPIPForDebug->StaticBindFrameBuffer();

		graphics::GraphicsAPI::ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		mPIPForDebug->ClearFrameBuffer();

		graphics::DebugDrawer::GetSingleton()->SetDrawInstantlyMaterial(mBVHDebugMaterial.get());

		/*
		for (int i = 0; i < mBVH->mCurrentAllocatedNodeCount; i++)
		{
			if (mBVH->mNodes[i].bmIsActive == true)
			{
				mBVH->mNodes[i].mBoundingCollider.DrawPhysicsDebugColor(eColor::Black, true);
			}
		}
		*/

		int index = targetNode;
		while (index != NULL_NODE_INDEX)
		{
			mBVH->mNodes[index].mBoundingCollider.DrawPhysicsDebugColor(eColor::Red, true);
			index = mBVH->mNodes[index].mParentIndex;
		}


		graphics::DebugDrawer::GetSingleton()->SetDrawInstantlyMaterial(nullptr);
		mPIPForDebug->RevertFrameBuffer();
	}
}

void doom::BVH_TestRoom::CheckActiveNode(doom::BVHAABB3D::node_type* node, std::vector<int>& activeNodeList)
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
		CheckActiveNode(&(mBVH->mNodes[node->mLeftNode]), activeNodeList);
	}

	if (node->mRightNode != NULL_NODE_INDEX)
	{
		CheckActiveNode(&(mBVH->mNodes[node->mRightNode]), activeNodeList);
	}
#endif
}

void doom::BVH_TestRoom::ValidCheck()
{
#ifdef DEBUG_MODE
	if (mBVH->mRootNodeIndex != NULL_NODE_INDEX)
	{
		D_DEBUG_LOG("Valid Check : BVH", eLogType::D_ALWAYS);

		//first check : recursively traverse all active nodes from rootIndex, Every active nodes in mBVH->mNodes array should be traversed
		//				every active nodes in mBVH->mNodes should be checked
		//				And call Node::ValidCheck();
		std::vector<int> checkedIndexs{};
		for (int i = 0; i < mBVH->mCurrentAllocatedNodeCount; i++)
		{
			if (mBVH->mNodes[i].bmIsActive == true)
			{
				checkedIndexs.push_back(i);
			}
		}
		D_ASSERT(checkedIndexs.size() == mBVH->mCurrentActiveNodeCount);
		CheckActiveNode(&(mBVH->mNodes[mBVH->mRootNodeIndex]), checkedIndexs);
		D_ASSERT(checkedIndexs.size() == 0);

		//second check : traverse from each Leaf Nodes to RootNode. Check if Traversing arrived at mBVH->rootIndex
		for (int i = 0; i < mBVH->mCurrentAllocatedNodeCount; i++)
		{
			if (mBVH->mNodes[i].bmIsActive == true)//&& mBVH->mNodes[i].mIsLeaf == true)
			{
				int index{ i };
				bool isSuccess{ false };
				while (index != NULL_NODE_INDEX)
				{
					if (index == mBVH->mRootNodeIndex)
					{
						isSuccess = true;
						break;
					}

					index = mBVH->mNodes[index].mParentIndex;
				}

				D_ASSERT(isSuccess == true);
			}
		}


		//third check : check all internal nodes must have 2 child,  all leaf nodes must have no child
		for (int i = 0; i < mBVH->mCurrentAllocatedNodeCount; i++)
		{
			if (mBVH->mNodes[i].bmIsActive == true)
			{
				if (mBVH->mNodes[i].mIsLeaf == false)
				{// leaf node must have 2 child
					D_ASSERT(mBVH->mNodes[i].mLeftNode != NULL_NODE_INDEX && mBVH->mNodes[i].mRightNode != NULL_NODE_INDEX);
				}
				else
				{// leaf node must have no childs
					D_ASSERT(mBVH->mNodes[i].mLeftNode == NULL_NODE_INDEX && mBVH->mNodes[i].mRightNode == NULL_NODE_INDEX);
				}
			}
		}


		//fourth check : check all nodes have unique child id ( all nodes have unique child id )
		//				 checked child id shouldn't be checked again
		std::unordered_set<int> checkedChildIndexs{};
		for (int i = 0; i < mBVH->mCurrentAllocatedNodeCount; i++)
		{
			if (mBVH->mNodes[i].bmIsActive == true && mBVH->mNodes[i].mIsLeaf == false)
			{
				D_ASSERT(checkedChildIndexs.find(mBVH->mNodes[i].mLeftNode) == checkedChildIndexs.end());
				D_ASSERT(checkedChildIndexs.find(mBVH->mNodes[i].mRightNode) == checkedChildIndexs.end());

				checkedChildIndexs.insert(mBVH->mNodes[i].mLeftNode);
				checkedChildIndexs.insert(mBVH->mNodes[i].mRightNode);
			}
		}


		//fifth check : compare one node's parent index and parent index's child index
		for (int i = 0; i < mBVH->mCurrentAllocatedNodeCount; i++)
		{
			if (mBVH->mNodes[i].bmIsActive == true)
			{
				if (mBVH->mNodes[i].mLeftNode != NULL_NODE_INDEX)
				{
					D_ASSERT(mBVH->mNodes[mBVH->mNodes[i].mLeftNode].mParentIndex == i);
				}

				if (mBVH->mNodes[i].mRightNode != NULL_NODE_INDEX)
				{
					D_ASSERT(mBVH->mNodes[mBVH->mNodes[i].mRightNode].mParentIndex == i);
				}

				if (mBVH->mNodes[i].mParentIndex != NULL_NODE_INDEX)
				{
					D_ASSERT(mBVH->mNodes[mBVH->mNodes[i].mParentIndex].mLeftNode == i || mBVH->mNodes[mBVH->mNodes[i].mParentIndex].mRightNode == i);
					D_ASSERT(mBVH->mNodes[mBVH->mNodes[i].mParentIndex].mLeftNode == i != mBVH->mNodes[mBVH->mNodes[i].mParentIndex].mRightNode == i);
				}
			}
		}

	}
	else
	{
		D_DEBUG_LOG("Valid Check Fail : BVH ( There is no RootIndex ) ", eLogType::D_ALWAYS);
	}
#endif


}


#endif