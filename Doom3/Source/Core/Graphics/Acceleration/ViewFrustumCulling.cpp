#include "ViewFrustumCulling.h"

#include <Rendering/Renderer/Renderer.h>

void doom::graphics::ViewFrustumCulling::SetCamera(float fovInRadian, float ratio, float nearDistance, float farDistance)
{
	this->mNearDistance = nearDistance;
	this->mFarDistance = farDistance;

	this->mRatio = ratio;
	this->mTan = math::tan(fovInRadian * 0.5f);
	this->mTanHalf = math::tan(fovInRadian);
	this->mNearHeight = this->mTan * nearDistance * 2;
	this->mNearWidth = this->mNearHeight * ratio;

	this->mSphereFactorY = 1.0f / math::cos(fovInRadian);

	float angleX = math::atan(this->mTanHalf * ratio);
	this->mSphereFactorX = 1.0f / math::cos(angleX);
}

void doom::graphics::ViewFrustumCulling::UpdateLookAt(const math::Vector3& cameraPosition, const math::Vector3& forwardDirection, const math::Vector3& updirection)
{
	this->mCameraPosition = cameraPosition;

	//D_ASSERT(math::abs(forwardDirection.magnitude() - 1.0f) <= math::epsilon());
	//D_ASSERT(math::abs(updirection.magnitude() - 1.0f) <= math::epsilon());
	
	this->mUpDirection = updirection;
	this->mRightDirection = math::cross(forwardDirection, updirection);
	this->mForwardDirection = forwardDirection;
}

bool doom::graphics::ViewFrustumCulling::IsInFrustum(const physics::AABB3D& aabb3D)
{
	return true;
}

bool doom::graphics::ViewFrustumCulling::IsInFrustum(const physics::Sphere& sphere)
{
	float d;
	float az, ax, ay;

	bool result{ false };

	math::Vector3 vecToSphereCenter = sphere.mCenter - this->mCameraPosition;

	az = math::dot(vecToSphereCenter, this->mForwardDirection);
	if (az > this->mFarDistance + sphere.mRadius || az < this->mNearDistance - sphere.mRadius)
	{
		return false;
	}
// 	if (az > this->mFarDistance - sphere.mRadius || az < this->mNearDistance + sphere.mRadius)
// 	{
// 		result = true;
// 	}

	ay = math::dot(vecToSphereCenter, this->mUpDirection);
	d = this->mSphereFactorY * sphere.mRadius;
	az *= this->mTanHalf;
	if (ay > az + d || ay < -az - d)
	{
		return false;
	}
// 	if (ay > az - d || ay < -az + d)
// 	{
// 		result = true;
// 	}
	
	ax = math::dot(vecToSphereCenter, this->mRightDirection);
	az *= this->mRatio;
	d = this->mSphereFactorX * sphere.mRadius;
	if (ax > az + d || ax < -az - d)
	{
		return false;
	}
// 	if (ax > az - d || ax < -az + d)
// 	{
// 		result = true;
// 	}

	return true;
}

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

/// <summary>
/// https://cgvr.informatik.uni-bremen.de/teaching/cg_literatur/lighthouse3d_view_frustum_culling/index.html
/// </summary>
/// <param name="point"></param>
/// <returns></returns>
bool doom::graphics::ViewFrustumCulling::IsInFrustum(const math::Vector3& point)
{
	float pcz, pcx, pcy, aux;

	math::Vector3 vecToPoint = point - this->mCameraPosition;
	pcz = math::dot(this->mForwardDirection, vecToPoint);
	if (pcz > this->mFarDistance || pcz < this->mNearDistance)
	{
		return false;
	}

	// compute and test the Y coordinate
	pcy = math::dot(this->mUpDirection, vecToPoint);
	aux = pcz * this->mTan;
	if (pcy > aux || pcy < -aux)
	{
		return false;
	}

	// compute and test the X coordinate
	pcx = math::dot(this->mRightDirection, vecToPoint);
	aux = aux * this->mRatio;
	if (pcx > aux || pcx < -aux)
	{
		return false;
	}

	return true;
}

bool doom::graphics::ViewFrustumCulling::IsVisible(Renderer* renderer)
{
	return this->IsInFrustum(renderer->BVH_Sphere_Node_Object::GetWorldBVhColliderCacheByReference());
}
