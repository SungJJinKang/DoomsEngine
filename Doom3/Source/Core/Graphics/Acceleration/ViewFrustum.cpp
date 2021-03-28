/*
#include "ViewFrustum.h"

#include "Physics/Collider/AABB.h"
#include "Physics/Collider/Sphere.h"

#include "Rendering/Renderer/Renderer.h"


void doom::graphics::ViewFrustum::SetCamera(float fovInRadian, float ratio, float nearDistance, float farDistance)
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

void doom::graphics::ViewFrustum::UpdateLookAt(const math::Vector3& cameraPosition, const math::Vector3& forwardDirection, const math::Vector3& updirection)
{
	this->mCameraPosition = cameraPosition;

	//D_ASSERT(math::abs(forwardDirection.magnitude() - 1.0f) <= math::epsilon());
	//D_ASSERT(math::abs(updirection.magnitude() - 1.0f) <= math::epsilon());

	this->mUpDirection = updirection;
	this->mRightDirection = math::cross(forwardDirection, updirection);
	this->mForwardDirection = forwardDirection;
}


bool doom::graphics::ViewFrustum::IsInFrustum(const doom::physics::AABB3D& aabb3D)
{
	return true;
}




/* Too slow, We use upper way For SIMD computation
bool doom::graphics::ViewFrustum::IsInFrustum(const doom::physics::Sphere& sphere)
{
	bool result{ false };

	math::Vector3 vecToSphereCenter = sphere.mCenter - this->mCameraPosition;

	float az = math::dot(vecToSphereCenter, this->mForwardDirection);
	if (az > this->mFarDistance + sphere.mRadius || az < this->mNearDistance - sphere.mRadius)
	{
		return false;
	}
	// 	if (az > this->mFarDistance - sphere.mRadius || az < this->mNearDistance + sphere.mRadius)
	// 	{
	// 		result = true;
	// 	}

	float ay = math::dot(vecToSphereCenter, this->mUpDirection);
	float d = this->mSphereFactorY * sphere.mRadius;
	az *= this->mTanHalf;
	if (ay > az + d || ay < -az - d)
	{
		return false;
	}
	// 	if (ay > az - d || ay < -az + d)
	// 	{
	// 		result = true;
	// 	}

	float ax = math::dot(vecToSphereCenter, this->mRightDirection);
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


/// <summary>
/// https://cgvr.informatik.uni-bremen.de/teaching/cg_literatur/lighthouse3d_view_frustum_culling/index.html
/// </summary>
/// <param name="point"></param>
/// <returns></returns>
bool doom::graphics::ViewFrustum::IsInFrustum(const math::Vector3& point)
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


bool doom::graphics::ViewFrustum::IsSphereVisible(Renderer* renderer)
{
	return this->IsInFrustum(renderer->BVH_Sphere_Node_Object::GetWorldBVhColliderCacheByReference());
}

bool doom::graphics::ViewFrustum::IsAABBVisible(Renderer* renderer)
{
	return this->IsInFrustum(renderer->BVH_AABB3D_Node_Object::GetWorldBVhColliderCacheByReference());
}
*/