#include "BVH_TestRoom.h"

#include <Random.h>
#include <UserInput_Server.h>
void doom::physics::BVH_TestRoom::AddNewRandomLeafNode()
{
	math::Vector3 newLower{ doom::random::Random::RandomFloatNumber(-1, 1), doom::random::Random::RandomFloatNumber(-1, 1) , doom::random::Random::RandomFloatNumber(-1, 1) };
	math::Vector3 newUpper{ doom::random::Random::RandomFloatNumber(-1, 1), doom::random::Random::RandomFloatNumber(-1, 1) , doom::random::Random::RandomFloatNumber(-1, 1) };


	doom::physics::AABB2D newAABB{ math::Min(newLower, newUpper), math::Max(newLower, newUpper) };
	this->mBVH.InsertLeaf(newAABB, nullptr);

}

void doom::physics::BVH_TestRoom::RemoveRecentAddedLeafNode()
{
	auto node = this->mBVH.GetNode(this->mBVH.recentAddedLeaf);
	this->mBVH.RemoveLeafNode(*node);
}

void doom::physics::BVH_TestRoom::BalanceRecentAddedLeafNode()
{
	this->mBVH.Balance(this->mBVH.recentAddedLeaf);
}

void doom::physics::BVH_TestRoom::Update()
{
	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F6))
	{
		D_DEBUG_LOG(std::to_string(this->mBVH.mTree.mCurrentActiveNodeCount), eLogType::D_TEMP);
		D_DEBUG_LOG(std::to_string(this->mBVH.GetLeafNodeCount()), eLogType::D_TEMP);
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F7))
	{
		this->BalanceRecentAddedLeafNode();
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F8))
	{
		this->mBVH.ValidCheck();
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F9))
	{
		this->mBVH.InitializeDebugging();
	}

	if (doom::userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F9))
	{
		this->mBVH.TreeDebug();
	}

	if (doom::userinput::UserInput_Server::GetKeyToggle(eKEY_CODE::KEY_F10))
	{
		this->mBVH.AABBDebug(this->mBVH.recentAddedLeaf);
	}

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F11))
	{
		this->AddNewRandomLeafNode();
	}
}
