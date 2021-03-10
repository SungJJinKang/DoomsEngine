#include "BVH_TestRoom.h"

#include <Random.h>
#include <UserInput_Server.h>
void doom::physics::BVH_TestRoom::AddNewRandomLeafNode()
{
	math::Vector3 newLower{ doom::random::Random::RandomFloatNumber(-10, 10), doom::random::Random::RandomFloatNumber(-10, 10) , doom::random::Random::RandomFloatNumber(-10, 10) };
	math::Vector3 newUpper{ doom::random::Random::RandomFloatNumber(-10, 10), doom::random::Random::RandomFloatNumber(-10, 10) , doom::random::Random::RandomFloatNumber(-10, 10) };


	doom::physics::AABB3D newAABB{ math::Min(newLower, newUpper), math::Max(newLower, newUpper) };
	this->mBVH.InsertLeaf(newAABB, nullptr);

}

void doom::physics::BVH_TestRoom::Update()
{
	this->mBVH.SimpleDebug();

	if (doom::userinput::UserInput_Server::GetKeyUp(eKEY_CODE::KEY_F10))
	{
		this->AddNewRandomLeafNode();
	}
}
