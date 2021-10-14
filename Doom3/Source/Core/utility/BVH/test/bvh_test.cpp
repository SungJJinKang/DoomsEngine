#include "../BVH.h"

INT32 main()
{
	doom::physics::BVH<doom::physics::AABB3D> bvh{};

	doom::physics::AABB3D a{ math::Vector3(0.0f), math::Vector3(1.0f) };
	doom::physics::AABB3D b{ math::Vector3(2.0f), math::Vector3(4.0f) };
	doom::physics::AABB3D c{ math::Vector3(5.0f), math::Vector3(10.0f) };

	bvh.InsertLeaf(a, nullptr);
	bvh.InsertLeaf(b, nullptr);
	bvh.InsertLeaf(c, nullptr);
}