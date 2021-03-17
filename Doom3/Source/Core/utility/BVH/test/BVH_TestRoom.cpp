#include "BVH_TestRoom.h"

#include <Random.h>
#include <UserInput_Server.h>
#include <Vector2.h>

void doom::physics::BVH_TestRoom::AddNewRandomLeafNode()
{
	math::Vector3 newLower{ doom::random::Random::RandomFloatNumber(-1, 1), doom::random::Random::RandomFloatNumber(-1, 1) , doom::random::Random::RandomFloatNumber(-1, 1) };
	math::Vector3 newUpper{ doom::random::Random::RandomFloatNumber(-1, 1), doom::random::Random::RandomFloatNumber(-1, 1) , doom::random::Random::RandomFloatNumber(-1, 1) };


	doom::physics::AABB3D newAABB{ math::Min(newLower, newUpper), math::Max(newLower, newUpper) };
	this->mBVH->InsertLeaf(newAABB, nullptr);

}


math::Vector2 leftPos{};
math::Vector2 rightPos{};


void doom::physics::BVH_TestRoom::AddNewRandomLeafNodeWithMouse()
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
		this->mBVH->InsertLeaf(aabb, nullptr);
		D_DEBUG_LOG("Create New LeafNode ", eLogType::D_ALWAYS);
	}
	
}

void doom::physics::BVH_TestRoom::RemoveRecentAddedLeafNode()
{
	if (this->mBVH->recentAddedLeaf.empty() == true)
	{
		return;
	}

	int nodeIndex = this->mBVH->recentAddedLeaf.top();
	this->mBVH->RemoveLeafNode(nodeIndex);

	this->mBVH->recentAddedLeaf.pop();
}

void doom::physics::BVH_TestRoom::BalanceRecentAddedLeafNode()
{
	if (this->mBVH->recentAddedLeaf.empty() == true)
	{
		return;
	}

	this->mBVH->Balance(this->mBVH->recentAddedLeaf.top());
}

void doom::physics::BVH_TestRoom::SetBVH3D(BVH3D* bvh3D)
{
	this->mBVH = std::unique_ptr<BVH3D>(bvh3D);
}

void doom::physics::BVH_TestRoom::Update()
{
	if (static_cast<bool>(this->mBVH) == false)
	{
		return;
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F6))
	{
		D_DEBUG_LOG(std::to_string(this->mBVH->mTree.mCurrentActiveNodeCount), eLogType::D_ALWAYS);
		D_DEBUG_LOG(std::to_string(this->mBVH->GetLeafNodeCount()), eLogType::D_ALWAYS);
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F7))
	{
		this->RemoveRecentAddedLeafNode();
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F8))
	{
		this->mBVH->ValidCheck();
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F9))
	{
		this->mBVH->InitializeDebugging();
	}

	if (doom::userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F9))
	{
		this->mBVH->TreeDebug();
	}

	if (doom::userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F10))
	{
		this->mBVH->AABBDebug();
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F11))
	{
		this->AddNewRandomLeafNode();
	}

	this->AddNewRandomLeafNodeWithMouse();
}
