#include "AABB.h"


bool doom::physics::AABB2D::IsValid()
{
	return mUpperBound.x > mLowerBound.x && mUpperBound.y > mLowerBound.y;
}

void doom::physics::AABB2D::Validate()
{
	if (mUpperBound.x < mLowerBound.x)
	{
		float temp = mLowerBound.x;
		mLowerBound.x = mUpperBound.x;
		mUpperBound.x = temp;
		D_DEBUG_LOG("AABB bound is worng");
	}

	if (mUpperBound.y < mLowerBound.y)
	{
		float temp = mLowerBound.y;
		mLowerBound.y = mUpperBound.y;
		mUpperBound.y = temp;
		D_DEBUG_LOG("AABB bound is worng");
	}
}

void doom::physics::AABB2D::Render()
{

}

bool doom::physics::AABB3D::IsValid()
{
	return mUpperBound.x > mLowerBound.x && mUpperBound.y > mLowerBound.y && mUpperBound.z > mLowerBound.z;
}

void doom::physics::AABB3D::Validate()
{
	if (mUpperBound.x < mLowerBound.x)
	{
		float temp = mLowerBound.x;
		mLowerBound.x = mUpperBound.x;
		mUpperBound.x = temp;
		D_DEBUG_LOG("AABB bound is worng");
	}

	if (mUpperBound.y < mLowerBound.y)
	{
		float temp = mLowerBound.y;
		mLowerBound.y = mUpperBound.y;
		mUpperBound.y = temp;
		D_DEBUG_LOG("AABB bound is worng");
	}

	if (mUpperBound.z < mLowerBound.z)
	{
		float temp = mLowerBound.z;
		mLowerBound.z = mUpperBound.z;
		mUpperBound.z = temp;
		D_DEBUG_LOG("AABB bound is worng");
	}
}


doom::physics::AABB2D doom::physics::Union(const AABB2D& A, const AABB2D& B)
{
	return AABB2D(math::min(A.mLowerBound, B.mLowerBound), math::max(A.mUpperBound, B.mUpperBound));
}

doom::physics::AABB3D doom::physics::Union(const AABB3D& A, const AABB3D& B)
{
	return AABB3D(math::min(A.mLowerBound, B.mLowerBound), math::max(A.mUpperBound, B.mUpperBound));
}

/// <summary>
/// ºÎÇÇ
/// </summary>
/// <param name="A"></param>
/// <returns></returns>
float doom::physics::Area(const AABB3D& A)
{
	math::Vector3 d = A.mUpperBound - A.mLowerBound;
	return 2.0f * (d.x * d.y + d.y * d.z + d.z * d.x);
}

float doom::physics::Area(const AABB2D& A)
{
	math::Vector2 d = A.mUpperBound - A.mLowerBound;
	return d.x * d.y;
}

bool doom::physics::IsOverlap(const AABB2D& A, const math::Vector2& Point)
{
	return (Point.x >= A.mLowerBound.x && Point.x <= A.mUpperBound.x) &&
		(Point.y >= A.mLowerBound.y && Point.y <= A.mUpperBound.y);
}

bool doom::physics::IsOverlap(const AABB2D& A, const AABB2D& B)
{
	return A.mUpperBound.x > B.mLowerBound.x && A.mLowerBound.x < B.mUpperBound.x&&
		A.mUpperBound.y  > B.mLowerBound.y && A.mLowerBound.y < B.mUpperBound.y;
}

bool doom::physics::IsOverlap(const AABB3D& A, const math::Vector3& Point)
{
	return (Point.x >= A.mLowerBound.x && Point.x <= A.mUpperBound.x) &&
		(Point.y >= A.mLowerBound.y && Point.y <= A.mUpperBound.y) &&
		(Point.z >= A.mLowerBound.z && Point.z <= A.mUpperBound.z);
}

bool doom::physics::IsOverlap(const AABB3D& A, const AABB3D& B)
{
	return (A.mLowerBound.x <= B.mUpperBound.x && A.mUpperBound.x >= B.mLowerBound.x) &&
		(A.mLowerBound.y <= B.mUpperBound.y && A.mUpperBound.y >= B.mLowerBound.y) &&
		(A.mLowerBound.z <= B.mUpperBound.z && A.mUpperBound.z >= B.mLowerBound.z);
}

math::Vector2 doom::physics::ClosestPointToPoint(const AABB2D& A, const math::Vector2& point)
{
	math::Vector2 result{};
	if (A.mLowerBound.x > point.x)
	{
		result.x = A.mLowerBound.x;
	}
	else if (A.mUpperBound.x < point.x)
	{
		result.x = A.mUpperBound.x;
	}
	else
	{
		result.x = point.x;
	}

	if (A.mLowerBound.y > point.y)
	{
		result.y = A.mLowerBound.y;
	}
	else if (A.mUpperBound.y < point.y)
	{
		result.y = A.mUpperBound.y;
	}
	else
	{
		result.y = point.y;
	}

	return result;
}

math::Vector3 doom::physics::ClosestPointToPoint(const AABB3D& A, const math::Vector3& point)
{
	math::Vector3 result{};
	if (A.mLowerBound.x > point.x)
	{
		result.x = A.mLowerBound.x;
	}
	else if (A.mUpperBound.x < point.x)
	{
		result.x = A.mUpperBound.x;
	}
	else
	{
		result.x = point.x;
	}

	if (A.mLowerBound.y > point.y)
	{
		result.y = A.mLowerBound.y;
	}
	else if (A.mUpperBound.y < point.y)
	{
		result.y = A.mUpperBound.y;
	}
	else
	{
		result.y = point.y;
	}


	if (A.mLowerBound.z > point.z)
	{
		result.z = A.mLowerBound.z;
	}
	else if (A.mUpperBound.z < point.z)
	{
		result.z = A.mUpperBound.z;
	}
	else
	{
		result.z = point.z;
	}

	return result;
}

float doom::physics::Raycast(Ray ray, AABB3D aabb) {
	float t1 = (aabb.mLowerBound.x - ray.mPosition.x) / ray.mNormal.x;
	float t2 = (aabb.mUpperBound.x - ray.mPosition.x) / ray.mNormal.x;
	float t3 = (aabb.mLowerBound.y - ray.mPosition.y) / ray.mNormal.y;
	float t4 = (aabb.mUpperBound.y - ray.mPosition.y) / ray.mNormal.y;
	float t5 = (aabb.mLowerBound.z - ray.mPosition.z) / ray.mNormal.z;
	float t6 = (aabb.mUpperBound.z - ray.mPosition.z) / ray.mNormal.z;

	float tmin = math::max(math::max(math::min(t1, t2), math::min(t3, t4)), math::min(t5, t6));
	float tmax = math::min(math::min(math::max(t1, t2), math::max(t3, t4)), math::max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0) {
		return -1;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax) {
		return -1;
	}

	if (tmin < 0.0f) {
		return tmax;
	}
	return tmin;
}
