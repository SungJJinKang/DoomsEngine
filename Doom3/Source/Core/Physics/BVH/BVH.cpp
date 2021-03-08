#include "BVH.h"

#include "../Collider/Collider.h"
#include "../Collider/Ray.h"
#include "../Collider/PhysicsGeneric.h"
#include "../Collider/ColliderSolution.h"

bool doom::physics::BVH::TreeRayCast(Tree& tree, Ray & ray)

{
	std::stack<int> stack{};
	stack.push(tree.mRootIndex);
	while (stack.empty() == false)
	{
		int index = stack.top();
		stack.pop();

		
		if (RaycastRayAndAABB3D(ray, tree.mNodes[index].mAABB) == false)
		{// if don't hit with bounding box
			continue;
		}

		if (tree.mNodes[index].mIsLeaf)
		{//if node is world object
			int objectIndex = tree.mNodes[index].mObjectIndex;

			Collider* objectCollider{};
			if (ColliderSolution::CheckIsOverlap(objectCollider, static_cast<Collider*>(&ray)) == true)
			{// check collision with ray and world object collider
				return true;
			}
		}
		else
		{
			stack.push(tree.mNodes[index].mChild1);
			stack.push(tree.mNodes[index].mChild2);
		}
	}
	return false;
}
