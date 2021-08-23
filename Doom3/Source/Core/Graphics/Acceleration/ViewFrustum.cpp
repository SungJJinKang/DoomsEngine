/*
#include "ViewFrustum.h"

#include "Physics/Collider/AABB.h"
#include "Physics/Collider/Sphere.h"

#include "Rendering/Renderer/Renderer.h"


void doom::graphics::ViewFrustum::SetCamera(float fovInRadian, float ratio, float nearDistance, float farDistance)
{
	mNearDistance = nearDistance;
	mFarDistance = farDistance;

	mRatio = ratio;
	mTan = math::tan(fovInRadian * 0.5f);
	mTanHalf = math::tan(fovInRadian);
	mNearHeight = mTan * nearDistance * 2;
	mNearWidth = mNearHeight * ratio;

	mSphereFactorY = 1.0f / math::cos(fovInRadian);

	float angleX = math::atan(mTanHalf * ratio);
	mSphereFactorX = 1.0f / math::cos(angleX);
}

void doom::graphics::ViewFrustum::UpdateLookAt(const math::Vector3& cameraPosition, const math::Vector3& forwardDirection, const math::Vector3& updirection)
{
	mCameraPosition = cameraPosition;

	//D_ASSERT(math::abs(forwardDirection.magnitude() - 1.0f) <= math::epsilon());
	//D_ASSERT(math::abs(updirection.magnitude() - 1.0f) <= math::epsilon());

	mUpDirection = updirection;
	mRightDirection = math::cross(forwardDirection, updirection);
	mForwardDirection = forwardDirection;
}


bool doom::graphics::ViewFrustum::IsInFrustum(const doom::physics::AABB3D& aabb3D)
{
	return true;
}




/* Too slow, We use upper way For SIMD computation
bool doom::graphics::ViewFrustum::IsInFrustum(const doom::physics::Sphere& sphere)
{
	bool result{ false };

	math::Vector3 vecToSphereCenter = sphere.mCenter - mCameraPosition;

	float az = math::dot(vecToSphereCenter, mForwardDirection);
	if (az > mFarDistance + sphere.mRadius || az < mNearDistance - sphere.mRadius)
	{
		return false;
	}
	// 	if (az > mFarDistance - sphere.mRadius || az < mNearDistance + sphere.mRadius)
	// 	{
	// 		result = true;
	// 	}

	float ay = math::dot(vecToSphereCenter, mUpDirection);
	float d = mSphereFactorY * sphere.mRadius;
	az *= mTanHalf;
	if (ay > az + d || ay < -az - d)
	{
		return false;
	}
	// 	if (ay > az - d || ay < -az + d)
	// 	{
	// 		result = true;
	// 	}

	float ax = math::dot(vecToSphereCenter, mRightDirection);
	az *= mRatio;
	d = mSphereFactorX * sphere.mRadius;
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

	math::Vector3 vecToPoint = point - mCameraPosition;
	pcz = math::dot(mForwardDirection, vecToPoint);
	if (pcz > mFarDistance || pcz < mNearDistance)
	{
		return false;
	}

	// compute and test the Y coordinate
	pcy = math::dot(mUpDirection, vecToPoint);
	aux = pcz * mTan;
	if (pcy > aux || pcy < -aux)
	{
		return false;
	}

	// compute and test the X coordinate
	pcx = math::dot(mRightDirection, vecToPoint);
	aux = aux * mRatio;
	if (pcx > aux || pcx < -aux)
	{
		return false;
	}

	return true;
}


bool doom::graphics::ViewFrustum::IsSphereVisible(Renderer* renderer)
{
	return IsInFrustum(renderer->BVH_Sphere_Node_Object::GetWorldBVhColliderCacheByReference());
}

bool doom::graphics::ViewFrustum::IsAABBVisible(Renderer* renderer)
{
	return IsInFrustum(renderer->BVH_AABB3D_Node_Object::GetWorldBVhColliderCacheByReference());
}
*/