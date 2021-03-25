#include "ViewFrustumCulling.h"

#include <Rendering/Renderer/Renderer.h>

bool doom::graphics::ViewFrustumCulling::IsInFrustumWithBVH(const physics::Sphere& sphere)
{
// 	std::stack<int> stack{};
// 	stack.push(this->mBVHSphere.MTmRootNodeIndex);
// 	while (stack.empty() == false)
// 	{
// 		int index = stack.top();
// 		stack.pop();
// 
// 		if constexpr (std::is_same_v<doom::physics::AABB2D, ColliderType> == true)
// 		{
// 			if (doom::physics::IsOverlapRayAndAABB2D(ray, this->mTree.mNodes[index].mBoundingCollider) == false)
// 			{// if don't hit with bounding box
// 				continue;
// 			}
// 		}
// 		else if constexpr (std::is_same_v<doom::physics::AABB3D, ColliderType> == true)
// 		{
// 			if (doom::physics::IsOverlapRayAndAABB3D(ray, this->mTree.mNodes[index].mBoundingCollider) == false)
// 			{// if don't hit with bounding box
// 				continue;
// 			}
// 		}
// 		else if constexpr (std::is_same_v<doom::physics::Sphere, ColliderType> == true)
// 		{
// 			if (doom::physics::IsOverlapRayAndSphere(ray, this->mTree.mNodes[index].mBoundingCollider) == false)
// 			{// if don't hit with bounding box
// 				continue;
// 			}
// 		}
// 		else
// 		{
// 			NEVER_HAPPEN;
// 		}
// 
// 
// 		if (this->mTree.mNodes[index].mIsLeaf)
// 		{//if node is world object
// 
// 			if (physics::ColliderSolution::CheckIsOverlap(this->mTree.mNodes[index].mCollider, static_cast<physics::Collider*>(const_cast<physics::Ray*>(&ray))) == true)
// 			{// check collision with ray and world object collider
// 				return true;
// 			}
// 			else
// 			{
// 				return false;
// 			}
// 		}
// 		else
// 		{
// 			stack.push(this->mTree.mNodes[index].mLeftNode);
// 			stack.push(this->mTree.mNodes[index].mRightNode);
// 		}
// 	}
// 	return false;
	return false;
}

void doom::graphics::ViewFrustumCulling::PreComputeCulling()
{

}
